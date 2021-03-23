DESCRIPTION = "libjpeg is a library for handling the JPEG (JFIF) image format."
LICENSE ="jpeg"
SECTION = "libs"
PRIORITY = "required"

DEPENDS = "libtool-cross"

PR = "r8"

SRC_URI = "http://www.ijg.org/files/jpegsrc.v${PV}.tar.gz \
	file://silent_rules.patch;patch=1 \
	file://fix_for_automake_1.11.2.patch;patch=1 \
	file://jpeg_fix_for_automake-1.12.patch;patch=1"

inherit autotools 

EXTRA_OECONF="--enable-static --enable-shared"

ARM_INSTRUCTION_SET = "arm"

do_configure_prepend () {
	rm -f ${S}/ltconfig
	rm -f ${S}/ltmain.sh
}

do_stage() {
	install -m 644 jconfig.h ${STAGING_INCDIR}/jconfig.h
	install -m 644 jpeglib.h ${STAGING_INCDIR}/jpeglib.h
	install -m 644 jmorecfg.h ${STAGING_INCDIR}/jmorecfg.h
	install -m 644 jerror.h ${STAGING_INCDIR}/jerror.h
	install -m 644 jpegint.h ${STAGING_INCDIR}/jpegint.h
	oe_libinstall -so libjpeg ${STAGING_LIBDIR}
}

do_install() {
	install -d ${D}${bindir} ${D}${includedir} \
		   ${D}${mandir}/man1 ${D}${libdir}
	oe_runmake 'DESTDIR=${D}' install
}

PACKAGES =+ 		"jpeg-tools "
FILES_jpeg-tools = 	"${bindir}/*"


