#
# Copyright (C) 2012-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=nginx
PKG_VERSION:=1.23.3
PKG_RELEASE:=1

PKG_SOURCE:=91ad1abfb285.tar.gz
PKG_SOURCE_URL:=https://hg.nginx.org/nginx-quic/archive/
PKG_HASH:=skip

PKG_MAINTAINER:=Thomas Heil <heil@terminal-consulting.de> \
				Ansuel Smith <ansuelsmth@gmail.com>
PKG_LICENSE:=2-clause BSD-like license
PKG_CPE_ID:=cpe:/a:nginx:nginx

PKG_FIXUP:=autoreconf
PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1

PKG_CONFIG_DEPENDS := \
	CONFIG_NGINX_DAV \
	CONFIG_NGINX_FLV \
	CONFIG_NGINX_MP4 \
	CONFIG_NGINX_STUB_STATUS \
	CONFIG_NGINX_HTTP_CHARSET \
	CONFIG_NGINX_HTTP_GZIP \
	CONFIG_NGINX_HTTP_GZIP_STATIC \
	CONFIG_NGINX_HTTP_SSI \
	CONFIG_NGINX_HTTP_USERID \
	CONFIG_NGINX_HTTP_ACCESS \
	CONFIG_NGINX_HTTP_AUTH_BASIC \
	CONFIG_NGINX_HTTP_AUTH_REQUEST \
	CONFIG_NGINX_HTTP_AUTOINDEX \
	CONFIG_NGINX_HTTP_GEO \
	CONFIG_NGINX_HTTP_MAP \
	CONFIG_NGINX_HTTP_SPLIT_CLIENTS \
	CONFIG_NGINX_HTTP_REFERER \
	CONFIG_NGINX_HTTP_REWRITE \
	CONFIG_NGINX_HTTP_PROXY \
	CONFIG_NGINX_HTTP_FASTCGI \
	CONFIG_NGINX_HTTP_UWSGI \
	CONFIG_NGINX_HTTP_SCGI \
	CONFIG_NGINX_HTTP_MEMCACHED \
	CONFIG_NGINX_HTTP_LIMIT_CONN \
	CONFIG_NGINX_HTTP_LIMIT_REQ \
	CONFIG_NGINX_HTTP_EMPTY_GIF \
	CONFIG_NGINX_HTTP_BROWSER \
	CONFIG_NGINX_HTTP_UPSTREAM_HASH \
	CONFIG_NGINX_HTTP_UPSTREAM_IP_HASH \
	CONFIG_NGINX_HTTP_UPSTREAM_LEAST_CONN \
	CONFIG_NGINX_HTTP_UPSTREAM_KEEPALIVE \
	CONFIG_NGINX_HTTP_UPSTREAM_ZONE \
	CONFIG_NGINX_HTTP_CACHE \
	CONFIG_NGINX_HTTP_V2 \
	CONFIG_NGINX_HTTP_V3 \
	CONFIG_NGINX_PCRE \
	CONFIG_NGINX_HTTP_REAL_IP \
	CONFIG_NGINX_HTTP_SECURE_LINK \
	CONFIG_NGINX_HTTP_SUB \
	CONFIG_NGINX_STREAM_SSL_MODULE \
	CONFIG_NGINX_STREAM_SSL_PREREAD_MODULE \
	CONFIG_NGINX_STREAM_QUIC_MODULE \
	CONFIG_NGINX_STREAM_CORE_MODULE \
	CONFIG_NGINX_GEOIP2_MODULE \
	CONFIG_NGINX_UBUS \
	CONFIG_NGINX_NAXSI \
	CONFIG_NGINX_LUA \
	CONFIG_NGINX_DAV_EXT \
	CONFIG_NGINX_HEADERS_MORE \
	CONFIG_NGINX_HTTP_BROTLI \
	CONFIG_NGINX_RTMP_MODULE \
	CONFIG_NGINX_TS_MODULE \
	CONFIG_NGINX_HTTP_AUTH_DIGEST \
	CONFIG_OPENSSL_ENGINE \
	CONFIG_OPENSSL_WITH_NPN

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/nginx/Default
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=Nginx web server
  URL:=http://nginx.org/
  DEPENDS:=+libopenssl +libpthread \
	+NGINX_DAV:libxml2 \
	+NGINX_HTTP_GZIP:zlib \
	+NGINX_PCRE:libpcre +NGINX_PCRE:nginx-ssl-util +!NGINX_PCRE:nginx-ssl-util-nopcre \
	+NGINX_STREAM_CORE_MODULE:nginx-mod-stream \
	+NGINX_GEOIP2_MODULE:nginx-mod-geoip2 \
	+NGINX_UBUS:nginx-mod-ubus \
	+NGINX_NAXSI:nginx-mod-naxsi \
	+NGINX_LUA:nginx-mod-lua \
	+NGINX_DAV_EXT:nginx-mod-dav-ext \
	+NGINX_HEADERS_MORE:nginx-mod-headers-more \
	+NGINX_HTTP_BROTLI:nginx-mod-brotli \
	+NGINX_RTMP_MODULE:nginx-mod-rtmp \
	+NGINX_TS_MODULE:nginx-mod-ts \
	+NGINX_HTTP_AUTH_DIGEST:nginx-mod-auth-digest
endef

define Package/nginx/description
 nginx is an HTTP and reverse proxy server, as well as a mail proxy server, \
 written by Igor Sysoev.
endef

define Package/nginx-ssl
  $(Package/nginx/Default)
  TITLE += with SSL support
  VARIANT:=ssl
  CONFLICTS:=nginx-all-module
  PROVIDES:=nginx
endef

Package/nginx-ssl/description = $(Package/nginx/description) \
  This variant is compiled with SSL support enabled. To enable additional module \
  select them in the nginx default configuration menu.

define Package/nginx-all-module
  $(Package/nginx/Default)
  TITLE += with ALL module selected
  VARIANT:=all-module
  DEPENDS += +@NGINX_DAV \
	+@NGINX_FLV \
	+@NGINX_MP4 \
	+@NGINX_STUB_STATUS \
	+@NGINX_HTTP_CHARSET \
	+@NGINX_HTTP_GZIP \
	+@NGINX_HTTP_GZIP_STATIC \
	+@NGINX_HTTP_SSI \
	+@NGINX_HTTP_USERID \
	+@NGINX_HTTP_ACCESS \
	+@NGINX_HTTP_AUTH_BASIC \
	+@NGINX_HTTP_AUTH_REQUEST \
	+@NGINX_HTTP_AUTOINDEX \
	+@NGINX_HTTP_GEO \
	+@NGINX_HTTP_MAP \
	+@NGINX_HTTP_SPLIT_CLIENTS \
	+@NGINX_HTTP_REFERER \
	+@NGINX_HTTP_REWRITE \
	+@NGINX_HTTP_PROXY \
	+@NGINX_HTTP_FASTCGI \
	+@NGINX_HTTP_UWSGI \
	+@NGINX_HTTP_SCGI \
	+@NGINX_HTTP_MEMCACHED \
	+@NGINX_HTTP_LIMIT_CONN \
	+@NGINX_HTTP_LIMIT_REQ \
	+@NGINX_HTTP_EMPTY_GIF \
	+@NGINX_HTTP_BROWSER \
	+@NGINX_HTTP_UPSTREAM_HASH \
	+@NGINX_HTTP_UPSTREAM_IP_HASH \
	+@NGINX_HTTP_UPSTREAM_LEAST_CONN \
	+@NGINX_HTTP_UPSTREAM_KEEPALIVE \
	+@NGINX_HTTP_UPSTREAM_ZONE \
	+@NGINX_HTTP_CACHE \
	+@NGINX_HTTP_V2 \
	+@NGINX_HTTP_V3 \
	+@NGINX_PCRE \
	+@NGINX_HTTP_REAL_IP \
	+@NGINX_HTTP_SECURE_LINK \
	+@NGINX_HTTP_SUB \
	+@NGINX_STREAM_SSL_MODULE \
	+@NGINX_STREAM_SSL_PREREAD_MODULE \
	+@NGINX_STREAM_QUIC_MODULE \
	+@NGINX_STREAM_CORE_MODULE \
	+@NGINX_GEOIP2_MODULE \
	+@NGINX_UBUS \
	+@NGINX_NAXSI \
	+@NGINX_LUA \
	+@NGINX_DAV_EXT \
	+@NGINX_HEADERS_MORE \
	+@NGINX_HTTP_BROTLI \
	+@NGINX_RTMP_MODULE \
	+@NGINX_TS_MODULE \
	+@NGINX_HTTP_AUTH_DIGEST
  PROVIDES:=nginx nginx-ssl
endef

Package/nginx-all-module/description = $(Package/nginx/description) \
  This variant is compiled with ALL module selected.

define Package/nginx-ssl/config
  source "$(SOURCE)/Config_ssl.in"
endef

define Package/nginx/conffiles
/etc/nginx/
endef

Package/nginx-ssl/conffiles = $(Package/nginx/conffiles)
Package/nginx-all-module/conffiles = $(Package/nginx/conffiles)

ADDITIONAL_MODULES:= --with-compat --with-http_ssl_module
config_files=mime.types

ifeq ($(CONFIG_IPV6),y)
  ADDITIONAL_MODULES += --with-ipv6
endif
ifeq ($(CONFIG_NGINX_DAV),y)
  ADDITIONAL_MODULES += --with-http_dav_module
endif
ifeq ($(CONFIG_NGINX_FLV),y)
  ADDITIONAL_MODULES += --with-http_flv_module
endif
ifeq ($(CONFIG_NGINX_MP4),y)
  ADDITIONAL_MODULES += --with-http_mp4_module
endif
ifeq ($(CONFIG_NGINX_STUB_STATUS),y)
  ADDITIONAL_MODULES += --with-http_stub_status_module
endif
ifneq ($(CONFIG_NGINX_HTTP_CHARSET),y)
  ADDITIONAL_MODULES += --without-http_charset_module
else
  config_files += koi-utf koi-win win-utf
endif
ifneq ($(CONFIG_NGINX_HTTP_GZIP),y)
  ADDITIONAL_MODULES += --without-http_gzip_module
endif
ifeq ($(CONFIG_NGINX_HTTP_GZIP_STATIC),y)
  ADDITIONAL_MODULES += --with-http_gzip_static_module
endif
ifneq ($(CONFIG_NGINX_HTTP_SSI),y)
  ADDITIONAL_MODULES += --without-http_ssi_module
endif
ifneq ($(CONFIG_NGINX_HTTP_USERID),y)
  ADDITIONAL_MODULES += --without-http_userid_module
endif
ifneq ($(CONFIG_NGINX_HTTP_ACCESS),y)
  ADDITIONAL_MODULES += --without-http_access_module
endif
ifneq ($(CONFIG_NGINX_HTTP_AUTH_BASIC),y)
  ADDITIONAL_MODULES += --without-http_auth_basic_module
endif
ifeq ($(CONFIG_NGINX_HTTP_AUTH_REQUEST),y)
  ADDITIONAL_MODULES += --with-http_auth_request_module
endif
ifneq ($(CONFIG_NGINX_HTTP_AUTOINDEX),y)
  ADDITIONAL_MODULES += --without-http_autoindex_module
endif
ifneq ($(CONFIG_NGINX_HTTP_GEO),y)
  ADDITIONAL_MODULES += --without-http_geo_module
endif
ifneq ($(CONFIG_NGINX_HTTP_MAP),y)
  ADDITIONAL_MODULES += --without-http_map_module
endif
ifneq ($(CONFIG_NGINX_HTTP_SPLIT_CLIENTS),y)
  ADDITIONAL_MODULES += --without-http_split_clients_module
endif
ifneq ($(CONFIG_NGINX_HTTP_REFERER),y)
  ADDITIONAL_MODULES += --without-http_referer_module
endif
ifneq ($(CONFIG_NGINX_HTTP_REWRITE),y)
  ADDITIONAL_MODULES += --without-http_rewrite_module
endif
ifneq ($(CONFIG_NGINX_HTTP_PROXY),y)
  ADDITIONAL_MODULES += --without-http_proxy_module
endif
ifneq ($(CONFIG_NGINX_HTTP_FASTCGI),y)
  ADDITIONAL_MODULES += --without-http_fastcgi_module
else
  config_files += fastcgi_params
endif
ifneq ($(CONFIG_NGINX_HTTP_UWSGI),y)
  ADDITIONAL_MODULES += --without-http_uwsgi_module
else
  config_files += uwsgi_params
endif
ifneq ($(CONFIG_NGINX_HTTP_SCGI),y)
  ADDITIONAL_MODULES += --without-http_scgi_module
else
  config_files += scgi_params
endif
ifneq ($(CONFIG_NGINX_HTTP_MEMCACHED),y)
  ADDITIONAL_MODULES += --without-http_memcached_module
endif
ifneq ($(CONFIG_NGINX_HTTP_LIMIT_CONN),y)
  ADDITIONAL_MODULES += --without-http_limit_conn_module
endif
ifneq ($(CONFIG_NGINX_HTTP_LIMIT_REQ),y)
  ADDITIONAL_MODULES += --without-http_limit_req_module
endif
ifneq ($(CONFIG_NGINX_HTTP_EMPTY_GIF),y)
  ADDITIONAL_MODULES += --without-http_empty_gif_module
endif
ifneq ($(CONFIG_NGINX_HTTP_BROWSER),y)
  ADDITIONAL_MODULES += --without-http_browser_module
endif
ifneq ($(CONFIG_NGINX_HTTP_UPSTREAM_HASH),y)
  ADDITIONAL_MODULES += --without-http_upstream_hash_module
endif
ifneq ($(CONFIG_NGINX_HTTP_UPSTREAM_IP_HASH),y)
  ADDITIONAL_MODULES += --without-http_upstream_ip_hash_module
endif
ifneq ($(CONFIG_NGINX_HTTP_UPSTREAM_LEAST_CONN),y)
  ADDITIONAL_MODULES += --without-http_upstream_least_conn_module
endif
ifneq ($(CONFIG_NGINX_HTTP_UPSTREAM_KEEPALIVE),y)
  ADDITIONAL_MODULES += --without-http_upstream_keepalive_module
endif
ifneq ($(CONFIG_NGINX_HTTP_UPSTREAM_ZONE),y)
  ADDITIONAL_MODULES += --without-http_upstream_zone_module
endif
ifneq ($(CONFIG_NGINX_HTTP_CACHE),y)
  ADDITIONAL_MODULES += --without-http-cache
endif
ifeq ($(CONFIG_NGINX_HTTP_V2),y)
  ADDITIONAL_MODULES += --with-http_v2_module
endif
ifeq ($(CONFIG_NGINX_HTTP_V3),y)
  ADDITIONAL_MODULES += --with-http_v3_module
endif
ifneq ($(CONFIG_NGINX_PCRE),y)
  ADDITIONAL_MODULES += --without-pcre
endif
ifeq ($(CONFIG_NGINX_HTTP_REAL_IP),y)
  ADDITIONAL_MODULES += --with-http_realip_module
endif
ifeq ($(CONFIG_NGINX_HTTP_SECURE_LINK),y)
  ADDITIONAL_MODULES += --with-http_secure_link_module
endif
ifeq ($(CONFIG_NGINX_HTTP_SUB),y)
  ADDITIONAL_MODULES += --with-http_sub_module
endif
ifeq ($(CONFIG_NGINX_STREAM_SSL_MODULE),y)
  ADDITIONAL_MODULES += --with-stream_ssl_module
endif
ifeq ($(CONFIG_NGINX_STREAM_SSL_PREREAD_MODULE),y)
  ADDITIONAL_MODULES += --with-stream_ssl_preread_module
endif
ifeq ($(CONFIG_NGINX_STREAM_QUIC_MODULE),y)
  ADDITIONAL_MODULES += --with-stream_quic_module
endif
ifeq ($(CONFIG_NGINX_STREAM_CORE_MODULE),y)
  ADDITIONAL_MODULES += --with-stream=dynamic
endif
ifeq ($(CONFIG_NGINX_GEOIP2_MODULE),y)
  ADDITIONAL_MODULES += --add-dynamic-module=$(PKG_BUILD_DIR)/nginx-geoip2-module
endif
ifeq ($(CONFIG_NGINX_UBUS),y)
  ADDITIONAL_MODULES += --add-dynamic-module=$(PKG_BUILD_DIR)/nginx-ubus-module
endif
ifeq ($(CONFIG_NGINX_NAXSI),y)
  ADDITIONAL_MODULES += --add-dynamic-module=$(PKG_BUILD_DIR)/nginx-naxsi/naxsi_src
endif
ifeq ($(CONFIG_NGINX_LUA),y)
  ADDITIONAL_MODULES += --add-dynamic-module=$(PKG_BUILD_DIR)/lua-nginx
endif
ifeq ($(CONFIG_NGINX_DAV_EXT),y)
  ADDITIONAL_MODULES += --add-dynamic-module=$(PKG_BUILD_DIR)/nginx-dav-ext-module
endif
ifeq ($(CONFIG_NGINX_HEADERS_MORE),y)
  ADDITIONAL_MODULES += --add-dynamic-module=$(PKG_BUILD_DIR)/nginx-headers-more
endif
ifeq ($(CONFIG_NGINX_HTTP_BROTLI),y)
  ADDITIONAL_MODULES += --add-dynamic-module=$(PKG_BUILD_DIR)/nginx-brotli
endif
ifeq ($(CONFIG_NGINX_RTMP_MODULE),y)
  ADDITIONAL_MODULES += --add-dynamic-module=$(PKG_BUILD_DIR)/nginx-rtmp
endif
ifeq ($(CONFIG_NGINX_TS_MODULE),y)
  ADDITIONAL_MODULES += --add-dynamic-module=$(PKG_BUILD_DIR)/nginx-ts
endif
ifeq ($(CONFIG_NGINX_HTTP_AUTH_DIGEST),y)
  ADDITIONAL_MODULES += --add-dynamic-module=$(PKG_BUILD_DIR)/nginx-auth-digest
endif

define Package/nginx-mod-luci
  TITLE:=Nginx on LuCI
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=Support file for Nginx
  URL:=http://nginx.org/
  DEPENDS:=+uwsgi +uwsgi-luci-support +nginx +nginx-mod-ubus
  PROVIDES:=nginx-mod-luci-ssl
endef

define Package/nginx-mod-luci/description
 Support file for LuCI in nginx. Include custom nginx configuration, autostart script for uwsgi.
endef

TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS) --strip-components 1
CONFIGURE_CMD = ./auto/configure

TARGET_CFLAGS += -fvisibility=hidden -ffunction-sections -fdata-sections -DNGX_LUA_NO_BY_LUA_BLOCK
TARGET_LDFLAGS += -Wl,--gc-sections

ifeq ($(CONFIG_NGINX_LUA),y)
  CONFIGURE_VARS += LUAJIT_INC=$(STAGING_DIR)/usr/include/luajit-2.1 \
					LUAJIT_LIB=$(STAGING_DIR)/usr/lib
endif

CONFIGURE_VARS += CONFIG_BIG_ENDIAN=$(CONFIG_BIG_ENDIAN)

CONFIGURE_ARGS += \
			--crossbuild=Linux::$(ARCH) \
			--prefix=/usr \
			--conf-path=/etc/nginx/nginx.conf \
			$(ADDITIONAL_MODULES) \
			--error-log-path=stderr \
			--pid-path=/var/run/nginx.pid \
			--lock-path=/var/lock/nginx.lock \
			--http-log-path=/var/log/nginx/access.log \
			--http-client-body-temp-path=/var/lib/nginx/body \
			--http-proxy-temp-path=/var/lib/nginx/proxy \
			--http-fastcgi-temp-path=/var/lib/nginx/fastcgi \
			--with-cc="$(TARGET_CC)" \
			--with-cc-opt="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS)" \
			--without-pcre2 --with-ld-opt="$(TARGET_LDFLAGS)"

define Package/nginx-mod-luci/install
	$(INSTALL_DIR) $(1)/etc/nginx/conf.d
	$(INSTALL_CONF) ./files-luci-support/luci.locations $(1)/etc/nginx/conf.d/
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) ./files-luci-support/60_nginx-luci-support $(1)/etc/uci-defaults/60_nginx-luci-support
endef

define Package/nginx-ssl/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/nginx $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/nginx/conf.d
	$(INSTALL_DATA) $(addprefix $(PKG_INSTALL_DIR)/etc/nginx/,$(config_files)) $(1)/etc/nginx/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/nginx.init $(1)/etc/init.d/nginx
ifeq ($(CONFIG_NGINX_NAXSI),y)
	$(INSTALL_DIR) $(1)/etc/nginx
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/nginx-naxsi/naxsi_config/naxsi_core.rules $(1)/etc/nginx
	chmod 0640 $(1)/etc/nginx/naxsi_core.rules
endif
	$(if $(CONFIG_NGINX_NAXSI),$($(INSTALL_BIN) $(PKG_BUILD_DIR)/nginx-naxsi/naxsi_config/naxsi_core.rules $(1)/etc/nginx))
	$(if $(CONFIG_NGINX_NAXSI),$(chmod 0640 $(1)/etc/nginx/naxsi_core.rules))
endef

Package/nginx-all-module/install = $(Package/nginx-ssl/install)

define Package/nginx-ssl/prerm
#!/bin/sh
[ -z "$${IPKG_INSTROOT}" ] || exit 0
[ "$${PKG_UPGRADE}" = "1" ] && exit 0
eval $$(/usr/bin/nginx-util get_env)
[ "$$(uci get "nginx.$${LAN_NAME}.$${MANAGE_SSL}")" = "self-signed" ] || exit 0
rm -f "$$(uci get "nginx.$${LAN_NAME}.ssl_certificate")"
rm -f "$$(uci get "nginx.$${LAN_NAME}.ssl_certificate_key")"
exit 0
endef

Package/nginx-all-module/prerm = $(Package/nginx-ssl/prerm)

define Download/nginx-geoip2-module
  VERSION:=cbaa35461c62a99d2577e6bae3273492502d8769
  SUBDIR:=nginx-geoip2-module
  FILE:=nginx-geoip2-module-$$(VERSION).tar.xz
  URL:=https://github.com/leev/ngx_http_geoip2_module.git
  MIRROR_HASH:=skip
  PROTO:=git
endef

define Prepare/nginx-geoip2-module
	$(eval $(Download/nginx-geoip2-module))
	xzcat $(DL_DIR)/$(FILE) | tar -C $(PKG_BUILD_DIR) $(TAR_OPTIONS)
endef

define Download/nginx-ubus-module
  VERSION:=b2d7260dcb428b2fb65540edb28d7538602b4a26
  SUBDIR:=nginx-ubus-module
  FILE:=nginx-ubus-module-$$(VERSION).tar.xz
  URL:=https://github.com/Ansuel/nginx-ubus-module.git
  MIRROR_HASH:=472cef416d25effcac66c85417ab6596e634a7a64d45b709bb090892d567553c
  PROTO:=git
endef

define Prepare/nginx-ubus-module
	$(eval $(Download/nginx-ubus-module))
	xzcat $(DL_DIR)/$(FILE) | tar -C $(PKG_BUILD_DIR) $(TAR_OPTIONS)
endef

define Download/nginx-naxsi
  VERSION:=951123ad456bdf5ac94e8d8819342fe3d49bc002
  SUBDIR:=nginx-naxsi
  FILE:=nginx-naxsi-module-$$(VERSION).tar.xz
  URL:=https://github.com/nbs-system/naxsi.git
  MIRROR_HASH:=c734cae19a596affadd62a2df1b58d3df8d1364093a4e80a7cd1ab4555963535
  PROTO:=git
endef

define Prepare/nginx-naxsi
	$(eval $(Download/nginx-naxsi))
	xzcat $(DL_DIR)/$(FILE) | tar -C $(PKG_BUILD_DIR) $(TAR_OPTIONS)
endef

define Download/lua-nginx
  VERSION:=28cf5ce3b6ec8e7ab44eadac9cc1c3b6f5c387ba
  SUBDIR:=lua-nginx
  FILE:=lua-nginx-module-$$(VERSION).tar.xz
  URL:=https://github.com/openresty/lua-nginx-module.git
  MIRROR_HASH:=skip
  PROTO:=git
endef

define Prepare/lua-nginx
	$(eval $(Download/lua-nginx))
	xzcat $(DL_DIR)/$(FILE) | tar -C $(PKG_BUILD_DIR) $(TAR_OPTIONS)
endef

define Download/nginx-dav-ext-module
  VERSION:=f5e30888a256136d9c550bf1ada77d6ea78a48af
  SUBDIR:=nginx-dav-ext-module
  FILE:=nginx-dav-ext-module-$$(VERSION).tar.xz
  URL:=https://github.com/arut/nginx-dav-ext-module.git
  MIRROR_HASH:=70bb4c3907f4b783605500ba494e907aede11f8505702e370012abb3c177dc5b
  PROTO:=git
endef

define Prepare/nginx-dav-ext-module
	$(eval $(Download/nginx-dav-ext-module))
	xzcat $(DL_DIR)/$(FILE) | tar -C $(PKG_BUILD_DIR) $(TAR_OPTIONS)
endef

define Download/nginx-headers-more
  VERSION:=bea1be3bbf6af28f6aa8cf0c01c07ee1637e2bd0
  SUBDIR:=nginx-headers-more
  FILE:=headers-more-nginx-module-$$(VERSION).tar.xz
  URL:=https://github.com/openresty/headers-more-nginx-module.git
  MIRROR_HASH:=skip
  PROTO:=git
endef

define Prepare/nginx-headers-more
	$(eval $(Download/nginx-headers-more))
	xzcat $(DL_DIR)/$(FILE) | tar -C $(PKG_BUILD_DIR) $(TAR_OPTIONS)
endef

define Download/nginx-brotli
  VERSION:=e505dce68acc190cc5a1e780a3b0275e39f160ca
  SUBDIR:=nginx-brotli
  FILE:=ngx-brotli-module-$$(VERSION).tar.xz
  URL:=https://github.com/google/ngx_brotli.git
  MIRROR_HASH:=04847f11ef808fed50f44b2af0ef3abf59ff0ffc06dfc7394d9ab51d53fef31f
  PROTO:=git
endef

define Prepare/nginx-brotli
	$(eval $(Download/nginx-brotli))
	xzcat $(DL_DIR)/$(FILE) | tar -C $(PKG_BUILD_DIR) $(TAR_OPTIONS)
endef

define Download/nginx-rtmp
  VERSION:=f0ea62342a4eca504b311cd5df910d026c3ea4cf
  SUBDIR:=nginx-rtmp
  FILE:=ngx-rtmp-module-$$(VERSION).tar.xz
  URL:=https://github.com/ut0mt8/nginx-rtmp-module.git
  MIRROR_HASH:=d3f58066f0f858ed79f7f2b0c9b89de2ccc512c94ab3d0625f6dcff3df0b72c1
  PROTO:=git
endef

define Prepare/nginx-rtmp
	$(eval $(Download/nginx-rtmp))
	xzcat $(DL_DIR)/$(FILE) | tar -C $(PKG_BUILD_DIR) $(TAR_OPTIONS)
endef

define Download/nginx-ts
  VERSION:=ef2f874d95cc75747eb625a292524a702aefb0fd
  SUBDIR:=nginx-ts
  FILE:=ngx-ts-module-$$(VERSION).tar.xz
  URL:=https://github.com/arut/nginx-ts-module.git
  MIRROR_HASH:=73938950bb286d40d9e54b0994d1a63827340c1156c72eb04d7041b25b20ec18
  PROTO:=git
endef

define Prepare/nginx-ts
	$(eval $(Download/nginx-ts))
	xzcat $(DL_DIR)/$(FILE) | tar -C $(PKG_BUILD_DIR) $(TAR_OPTIONS)
endef

define Download/nginx-auth-digest
  VERSION:=b3073ef3624ec0e590671399e7b8f31458218d2a
  SUBDIR:=nginx-auth-digest
  FILE:=nginx-http-auth-digest-$$(VERSION).tar.xz
  URL:=https://github.com/atomx/nginx-http-auth-digest.git
  MIRROR_HASH:=24511f8c0867ce3e0961766f33d2a4020aeeda19325ab4400c8abf545c999b93
  PROTO:=git
endef

define Prepare/nginx-auth-digest
	$(eval $(Download/nginx-auth-digest))
	xzcat $(DL_DIR)/$(FILE) | tar -C $(PKG_BUILD_DIR) $(TAR_OPTIONS)
endef

define Build/Patch
	$(if $(QUILT),rm -rf $(PKG_BUILD_DIR)/patches; mkdir -p $(PKG_BUILD_DIR)/patches)
	$(call PatchDir,$(PKG_BUILD_DIR),$(PATCH_DIR)/nginx,nginx/)
ifneq "$(or $(CONFIG_NGINX_DAV_EXT),$(QUILT))" ""
	$(call PatchDir,$(PKG_BUILD_DIR),$(PATCH_DIR)/dav-nginx,dav-nginx/)
endif
ifneq "$(or $(CONFIG_NGINX_LUA),$(QUILT))" ""
	$(call PatchDir,$(PKG_BUILD_DIR),$(PATCH_DIR)/lua-nginx,lua-nginx/)
endif
ifneq "$(or $(CONFIG_NGINX_RTMP_MODULE),$(QUILT))" ""
	$(call PatchDir,$(PKG_BUILD_DIR),$(PATCH_DIR)/rtmp-nginx,rtmp-nginx/)
endif
	$(if $(QUILT),touch $(PKG_BUILD_DIR)/.quilt_used)
endef

define Quilt/Refresh/Package
	$(call Quilt/RefreshDir,$(PKG_BUILD_DIR),$(PATCH_DIR)/nginx,nginx/)
	$(call Quilt/RefreshDir,$(PKG_BUILD_DIR),$(PATCH_DIR)/dav-nginx,dav-nginx/)
	$(call Quilt/RefreshDir,$(PKG_BUILD_DIR),$(PATCH_DIR)/lua-nginx,lua-nginx/)
	$(call Quilt/RefreshDir,$(PKG_BUILD_DIR),$(PATCH_DIR)/rtmp-nginx,rtmp-nginx/)
endef

define Build/Prepare
	rm -rf $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR)
	$(PKG_UNPACK)

ifeq ($(CONFIG_NGINX_GEOIP2_MODULE),y)
  $(eval $(call Download,nginx-geoip2-module))
  $(Prepare/nginx-geoip2-module)
endif

ifeq ($(CONFIG_NGINX_UBUS),y)
  $(eval $(call Download,nginx-ubus-module))
  $(Prepare/nginx-ubus-module)
endif

ifeq ($(CONFIG_NGINX_NAXSI),y)
  $(eval $(call Download,nginx-naxsi))
  $(Prepare/nginx-naxsi)
endif

ifneq "$(or $(CONFIG_NGINX_LUA),$(QUILT))" ""
  $(eval $(call Download,lua-nginx))
  $(Prepare/lua-nginx)
endif

ifneq "$(or $(CONFIG_NGINX_DAV_EXT),$(QUILT))" ""
  $(eval $(call Download,nginx-dav-ext-module))
  $(Prepare/nginx-dav-ext-module)
endif

ifeq ($(CONFIG_NGINX_HEADERS_MORE),y)
  $(eval $(call Download,nginx-headers-more))
  $(Prepare/nginx-headers-more)
endif

ifeq ($(CONFIG_NGINX_HTTP_BROTLI),y)
  $(eval $(call Download,nginx-brotli))
  $(Prepare/nginx-brotli)
endif

ifneq "$(or $(CONFIG_NGINX_RTMP_MODULE),$(QUILT))" ""
  $(eval $(call Download,nginx-rtmp))
  $(Prepare/nginx-rtmp)
endif

ifeq ($(CONFIG_NGINX_TS_MODULE),y)
  $(eval $(call Download,nginx-ts))
  $(Prepare/nginx-ts)
endif

ifeq ($(CONFIG_NGINX_HTTP_AUTH_DIGEST),y)
  $(eval $(call Download,nginx-auth-digest))
  $(Prepare/nginx-auth-digest)
endif

	$(Build/Patch)
endef

$(eval $(call BuildPackage,nginx-ssl))
$(eval $(call BuildPackage,nginx-all-module))
$(eval $(call BuildPackage,nginx-mod-luci))

define BuildModule
  define Package/nginx-mod-$(1)
    $(call Package/nginx/Default)
    TITLE:=Nginx $(2) module
    DEPENDS:=$(3)
  endef

  define Package/nginx-mod-$(1)/install
	$(INSTALL_DIR) $$(1)/usr/modules
	for so in $(4) ; do \
		$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/modules/$$$$$$$$so $$(1)/usr/modules/ ; \
	done
  endef

  $$(eval $$(call BuildPackage,nginx-mod-$(1)))
endef

$(eval $(call BuildModule,stream,stream,,ngx_stream_module.so))
$(eval $(call BuildModule,geoip2,geoip2,+libmaxminddb,ngx_http_geoip2_module.so ngx_stream_geoip2_module.so))
$(eval $(call BuildModule,ubus,Ubus,+libubus +libblobmsg-json +libjson-c,ngx_http_ubus_module.so))
$(eval $(call BuildModule,naxsi,NAXSI,,ngx_http_naxsi_module.so))
$(eval $(call BuildModule,lua,LUA,+luajit,ngx_http_lua_module.so))
$(eval $(call BuildModule,dav-ext,DAV-EXT,+libxml2,ngx_http_dav_ext_module.so))
$(eval $(call BuildModule,headers-more,Headers More,,ngx_http_headers_more_filter_module.so))
$(eval $(call BuildModule,brotli,Brotli,,ngx_http_brotli_filter_module.so ngx_http_brotli_static_module.so))
$(eval $(call BuildModule,rtmp,RTMP,,ngx_rtmp_module.so))
$(eval $(call BuildModule,ts,TS,,ngx_http_ts_module.so))
$(eval $(call BuildModule,auth-digest,HTTP auth digest,,ngx_http_auth_digest_module.so))
