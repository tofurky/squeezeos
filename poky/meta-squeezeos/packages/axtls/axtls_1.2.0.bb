DESCRIPTION = "axTLS SSL library"
SECTION = "libs"
#PR = "r0"

SRC_URI = "http://downloads.sourceforge.net/axtls/axTLS-${PV}.tar.gz \
           file://axTLS.config \
	   "

S = "${WORKDIR}/axTLS"

inherit autotools pkgconfig binconfig

LIBTOOL = "${S}/builds/unix/${HOST_SYS}-libtool"
EXTRA_OEMAKE = "'LIBTOOL=${LIBTOOL}'"
EXTRA_OECONF = "--without-zlib"

do_configure() {
	cp ${WORKDIR}/axTLS.config ${S}/config/.config
	echo "PREFIX=\"${D}${prefix}\"" >> ${S}/config/.config
	oe_runmake oldconfig
}

do_stage() {
	install -d ${STAGING_INCDIR}/axTLS
	install -m 0644 ${S}/crypto/bigint.h ${STAGING_INCDIR}/axTLS/bigint.h
	install -m 0644 ${S}/crypto/bigint_impl.h ${STAGING_INCDIR}/axTLS/bigint_impl.h
	install -m 0644 ${S}/config/config.h ${STAGING_INCDIR}/axTLS/config.h
	install -m 0644 ${S}/crypto/crypto.h ${STAGING_INCDIR}/axTLS/crypto.h
	install -m 0644 ${S}/ssl/crypto_misc.h ${STAGING_INCDIR}/axTLS/crypto_misc.h
	install -m 0644 ${S}/ssl/os_port.h ${STAGING_INCDIR}/axTLS/os_port.h
	install -m 0644 ${S}/ssl/ssl.h ${STAGING_INCDIR}/axTLS/ssl.h
	install -m 0644 ${S}/ssl/tls1.h ${STAGING_INCDIR}/axTLS/tls1.h
	install -m 0644 ${S}/ssl/version.h ${STAGING_INCDIR}/axTLS/version.h
	oe_libinstall -so -a -C _stage libaxtls ${STAGING_LIBDIR}/
}

do_install() {
	PREFIX=${D} oe_runmake install
}

FILES_${PN} = "${libdir}/lib*${SOLIBS}"
FILES_${PN}-dev += "${bindir}"
