DESCRIPTION = "Command line tool and library for client-side URL transfers."
LICENSE = "MIT"
DEPENDS = "openssl zlib gnutls"
SECTION = "console/network"
PR = "r0"

SRC_URI = "https://curl.se/download/curl-${PV}.tar.gz \
	file://autoconf_fix.patch;patch=1" 

inherit autotools_stage pkgconfig binconfig

EXTRA_OECONF = "--with-zlib=${STAGING_LIBDIR}/../ \
                --with-gnutls=${STAGING_BINDIR_CROSS}/ \
                --with-ssl=${STAGING_LIBDIR}/../ \
		--with-random=/dev/urandom \
		--without-libidn \
		--enable-crypto-auth \
		"

do_configure_prepend() {
	sed -i s:OPT_GNUTLS/bin:OPT_GNUTLS:g configure.ac
}

PACKAGES += "${PN}-certs libcurl libcurl-dev libcurl-doc"

FILES_${PN} = "${bindir}/curl"

FILES_${PN}-certs = "${datadir}/curl/curl-*"
PACKAGE_ARCH_${PN}-certs = "all"

FILES_${PN}-doc = "${mandir}/man1/curl.1"

FILES_lib${PN} = "${libdir}/lib*.so.*"
RRECOMMENDS_lib${PN} += "${PN}-certs"
FILES_lib${PN}-dev = "${includedir} \
                      ${libdir}/lib*.so \
                      ${libdir}/lib*.a \
                      ${libdir}/lib*.la \
                      ${libdir}/pkgconfig \
                      ${datadir}/aclocal \
                      ${bindir}/*-config"

FILES_lib${PN}-doc = "${mandir}/man3 \
                      ${mandir}/man1/curl-config.1"

