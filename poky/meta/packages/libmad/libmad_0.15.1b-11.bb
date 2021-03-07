DESCRIPTION = "MPEG Audio Decoder Library"
SECTION = "libs"
PRIORITY = "optional"
DEPENDS = ""
LICENSE = "GPL"
PR = "r0"

SRC_URI = "${RALPHY_SQUEEZEOS}/libmad-${PV}.tar.gz"

S = "${WORKDIR}/libmad-${PV}"

inherit autotools pkgconfig

EXTRA_OECONF = "--enable-shared"
# The ASO's don't take any account of thumb...
EXTRA_OECONF_append_thumb = " --disable-aso --enable-fpm=default"
EXTRA_OECONF_append_arm = " --enable-fpm=arm"

do_configure_prepend () {
#	damn picky automake...
	touch NEWS AUTHORS ChangeLog
}

do_stage() {
	oe_libinstall -so libmad ${STAGING_LIBDIR}
	install -m 0644 mad.h ${STAGING_INCDIR}
}

ARM_INSTRUCTION_SET = "arm"
