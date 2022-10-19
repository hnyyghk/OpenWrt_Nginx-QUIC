#ifndef _PX5G_OPENSSL_HPP
#define _PX5G_OPENSSL_HPP

// #define OPENSSL_API_COMPAT 0x10102000L
#include <fcntl.h>
#include <memory>
#include <openssl/bn.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <string>
#include <unistd.h>

static constexpr auto rsa_min_modulus_bits = 512;

using EVP_PKEY_ptr = std::unique_ptr<EVP_PKEY, decltype(&::EVP_PKEY_free)>;

using X509_NAME_ptr = std::unique_ptr<X509_NAME, decltype(&::X509_NAME_free)>;


auto checkend(const std::string & crtpath,
              time_t seconds=0, bool use_pem=true) -> bool;


auto gen_eckey(int curve) -> EVP_PKEY_ptr;


auto gen_rsakey(int keysize, BN_ULONG exponent=RSA_F4) -> EVP_PKEY_ptr;


void write_key(const EVP_PKEY_ptr & pkey,
               const std::string & keypath="", bool use_pem=true);


auto subject2name(const std::string & subject) -> X509_NAME_ptr;


void selfsigned(const EVP_PKEY_ptr & pkey, int days,
                const std::string & subject="", const std::string & crtpath="",
                bool use_pem=true);



// ------------------------- implementation: ----------------------------------


inline auto print_error(const char * str, const size_t  /*len*/, void * errmsg)
    -> int
{
    *static_cast<std::string *>(errmsg) += str;
    return 0;
}


auto checkend(const std::string & crtpath,
              const time_t seconds, const bool use_pem) -> bool
{
    BIO * bio = crtpath.empty() ?
        BIO_new_fp(stdin, BIO_NOCLOSE | (use_pem ? BIO_FP_TEXT : 0)) :
        BIO_new_file(crtpath.c_str(), (use_pem ? "r" : "rb"));

    X509 * x509 = nullptr;

    if (bio != nullptr) {
        x509 = use_pem ?
            PEM_read_bio_X509_AUX(bio, nullptr, nullptr, nullptr) :
            d2i_X509_bio(bio, nullptr);
        BIO_free(bio);
    }

    if (x509==nullptr) {
        std::string errmsg{"checkend error: unable to load certificate\n"};
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    }

    time_t checktime = time(nullptr) + seconds;
    auto cmp = X509_cmp_time(X509_get0_notAfter(x509), &checktime);

    X509_free(x509);

    return (cmp >= 0);
}


auto gen_eckey(const int curve) -> EVP_PKEY_ptr
{
    EC_GROUP * group = curve!=0 ? EC_GROUP_new_by_curve_name(curve) : nullptr;

    if (group == nullptr) {
        std::string errmsg{"gen_eckey error: cannot build group for curve id "};
        errmsg += std::to_string(curve) + "\n";
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    }

    EC_GROUP_set_asn1_flag(group, OPENSSL_EC_NAMED_CURVE);

    EC_GROUP_set_point_conversion_form(group, POINT_CONVERSION_UNCOMPRESSED);

    auto eckey = EC_KEY_new();

    if (eckey != nullptr) {
        if ( (EC_KEY_set_group(eckey, group) == 0) ||
            (EC_KEY_generate_key(eckey) == 0) )
        {
            EC_KEY_free(eckey);
            eckey = nullptr;
        }
    }

    EC_GROUP_free(group);

    if (eckey == nullptr) {
        std::string errmsg{"gen_eckey error: cannot build key with curve id "};
        errmsg += std::to_string(curve) + "\n";
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    }

    EVP_PKEY_ptr pkey{EVP_PKEY_new(), ::EVP_PKEY_free};

    auto tmp = static_cast<char *>(static_cast<void *>(eckey));

    if (!EVP_PKEY_assign_EC_KEY(pkey.get(), tmp)) {
        EC_KEY_free(eckey);
        std::string errmsg{"gen_eckey error: cannot assign EC key to EVP\n"};
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    }

    return pkey;
}


auto gen_rsakey(const int keysize, const BN_ULONG exponent) -> EVP_PKEY_ptr
{
    if (keysize<rsa_min_modulus_bits || keysize>OPENSSL_RSA_MAX_MODULUS_BITS) {
        std::string errmsg{"gen_rsakey error: RSA keysize ("};
        errmsg += std::to_string(keysize) + ") out of range [512..";
        errmsg += std::to_string(OPENSSL_RSA_MAX_MODULUS_BITS) + "]";
        throw std::runtime_error(errmsg.c_str());
    }
    auto bignum = BN_new();

    if (bignum == nullptr) {
        std::string errmsg{"gen_rsakey error: cannot get big number struct\n"};
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    }

    auto rsa = RSA_new();

    if (rsa != nullptr) {
        if ((BN_set_word(bignum, exponent) == 0) ||
            (RSA_generate_key_ex(rsa, keysize, bignum, nullptr) == 0))
        {
            RSA_free(rsa);
            rsa = nullptr;
        }
    }

    BN_free(bignum);

    if (rsa == nullptr) {
        std::string errmsg{"gen_rsakey error: cannot create RSA key with size"};
        errmsg += std::to_string(keysize) + " and exponent ";
        errmsg += std::to_string(exponent) + "\n";
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    }

    EVP_PKEY_ptr pkey{EVP_PKEY_new(), ::EVP_PKEY_free};

    auto tmp = static_cast<char *>(static_cast<void *>(rsa));

    if (!EVP_PKEY_assign_RSA(pkey.get(), tmp)) {
        RSA_free(rsa);
        std::string errmsg{"gen_rsakey error: cannot assign RSA key to EVP\n"};
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    }

    return pkey;
}


void write_key(const EVP_PKEY_ptr & pkey,
               const std::string & keypath, const bool use_pem)
{
    BIO * bio = nullptr;

    if (keypath.empty()) {
        bio = BIO_new_fp( stdout, BIO_NOCLOSE | (use_pem ? BIO_FP_TEXT : 0) );

    } else { // BIO_new_file(keypath.c_str(), (use_pem ? "w" : "wb") );

        static constexpr auto mask = 0600;
        // auto fd = open(keypath.c_str(), O_WRONLY | O_CREAT | O_TRUNC, mask);
        auto fd = creat(keypath.c_str(), mask); // the same without va_args.

        if (fd >= 0) {
            auto fp = fdopen(fd, (use_pem ? "w" : "wb") );

            if (fp != nullptr) {
                bio = BIO_new_fp(fp, BIO_CLOSE | (use_pem ? BIO_FP_TEXT : 0));
                if (bio == nullptr) { fclose(fp); } // (fp owns fd)
            }
            else { close(fd); }
        }

    }

    if (bio == nullptr) {
        std::string errmsg{"write_key error: cannot open "};
        errmsg += keypath.empty() ? "stdout" : keypath;
        errmsg += "\n";
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    }

    int len = 0;

    auto key = pkey.get();
    switch (EVP_PKEY_base_id(key)) { // use same format as px5g:
        case EVP_PKEY_EC:
            len = use_pem ?
                PEM_write_bio_ECPrivateKey(bio, EVP_PKEY_get0_EC_KEY(key),
                                        nullptr, nullptr, 0, nullptr, nullptr) :
                i2d_ECPrivateKey_bio(bio, EVP_PKEY_get0_EC_KEY(key));
            break;
        case EVP_PKEY_RSA:
            len = use_pem ?
                PEM_write_bio_RSAPrivateKey(bio, EVP_PKEY_get0_RSA(key),
                                        nullptr, nullptr, 0, nullptr, nullptr) :
                i2d_RSAPrivateKey_bio(bio, EVP_PKEY_get0_RSA(key));
            break;
        default:
            len = use_pem ?
                PEM_write_bio_PrivateKey(bio, key,
                                        nullptr, nullptr, 0, nullptr, nullptr) :
                i2d_PrivateKey_bio(bio, key);
    }

    BIO_free_all(bio);

    if (len==0) {
        std::string errmsg{"write_key error: cannot write EVP pkey to "};
        errmsg += keypath.empty() ? "stdout" : keypath;
        errmsg += "\n";
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    }
}


auto subject2name(const std::string & subject) -> X509_NAME_ptr
{
    if (!subject.empty() && subject[0]!='/') {
        throw std::runtime_error("subject2name errror: not starting with /");
    }

    X509_NAME_ptr name = {X509_NAME_new(), ::X509_NAME_free};

    if (!name) {
        std::string errmsg{"subject2name error: cannot create X509 name \n"};
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    }

    if (subject.empty()) { return name; }

    size_t prev = 1;
    std::string type{};
    char chr = '=';
    for (size_t i=0; subject[i] != 0; ) {
        ++i;
        if (subject[i]=='\\' && subject[++i]=='\0') {
            throw std::runtime_error("subject2name errror: escape at the end");
        }
        if (subject[i]!=chr && subject[i]!='\0') { continue; }
        if (chr == '=') {
            type = subject.substr(prev, i-prev);
            chr = '/';
        } else {
            auto nid = OBJ_txt2nid(type.c_str());
            if (nid == NID_undef) {
                // skip unknown entries (silently?).
            } else {
                auto val = static_cast<const unsigned char *>(
                                static_cast<const void *>(&subject[prev]) );

                auto len = i - prev;

                if ( X509_NAME_add_entry_by_NID(name.get(), nid, MBSTRING_ASC,
                                                  val, len, -1, 0)
                    == 0 )
                {
                    std::string errmsg{"subject2name error: cannot add "};
                    errmsg += "/" + type +"="+ subject.substr(prev, len) +"\n";
                    ERR_print_errors_cb(print_error, &errmsg);
                    throw std::runtime_error(errmsg.c_str());
                }
            }
            chr = '=';
        }
        prev = i+1;
    }

    return name;
}


void selfsigned(const EVP_PKEY_ptr & pkey, const int days,
                const std::string & subject, const std::string & crtpath,
                const bool use_pem)
{
    auto x509 = X509_new();

    if (x509 == nullptr) {
        std::string errmsg{"selfsigned error: cannot create X509 structure\n"};
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    }

    auto freeX509_and_throw = [&x509](const std::string & what)
    {
        X509_free(x509);
        std::string errmsg{"selfsigned error: cannot set "};
        errmsg += what + " in X509 certificate\n";
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    };

    if (X509_set_version(x509, 2) == 0) { freeX509_and_throw("version"); }

    if (X509_set_pubkey(x509, pkey.get()) == 0) { freeX509_and_throw("pubkey");}

    if ((X509_gmtime_adj(X509_getm_notBefore(x509), 0) == nullptr) ||
        (X509_time_adj_ex(X509_getm_notAfter(x509), days,0,nullptr) == nullptr))
    {
        freeX509_and_throw("times");
    }

    X509_NAME_ptr name{nullptr, ::X509_NAME_free};

    try { name = subject2name(subject); }
    catch (...) {
        X509_free(x509);
        throw;
    }

    if (X509_set_subject_name(x509, name.get()) == 0) {
        freeX509_and_throw("subject");
    }

    if (X509_set_issuer_name(x509, name.get()) == 0) {
        freeX509_and_throw("issuer");
    }

    auto bignum = BN_new();

    if (bignum == nullptr) { freeX509_and_throw("serial (creating big number struct)"); }

    static const auto BITS = 159;
    if (BN_rand(bignum, BITS, BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY) == 0) {
        BN_free(bignum);
        freeX509_and_throw("serial (creating random number)");
    }

    if (BN_to_ASN1_INTEGER(bignum, X509_get_serialNumber(x509)) == nullptr) {
        BN_free(bignum);
        freeX509_and_throw("random serial");
    }

    BN_free(bignum);

    if (X509_sign(x509, pkey.get(), EVP_sha256()) == 0) {
        freeX509_and_throw("signing digest");
    }

    BIO * bio = crtpath.empty() ?
        BIO_new_fp(stdout, BIO_NOCLOSE | (use_pem ? BIO_FP_TEXT : 0)) :
        BIO_new_file(crtpath.c_str(), (use_pem ? "w" : "wb"));

    int len = 0;

    if (bio != nullptr) {
        len = use_pem ?
            PEM_write_bio_X509(bio, x509) :
            i2d_X509_bio(bio, x509);
        BIO_free_all(bio);
    }

    X509_free(x509);

    if (len==0) {
        std::string errmsg{"selfsigned error: cannot write certificate to "};
        errmsg += crtpath.empty() ? "stdout" : crtpath;
        errmsg += "\n";
        ERR_print_errors_cb(print_error, &errmsg);
        throw std::runtime_error(errmsg.c_str());
    }
}


#endif
