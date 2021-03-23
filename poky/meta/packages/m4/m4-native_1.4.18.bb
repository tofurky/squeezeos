require m4_${PV}.bb
inherit native

INHIBIT_AUTOTOOLS_DEPS = "1"
DEPENDS += "gnu-config-native"

SRC_URI += "file://m4-1.4.18-glibc-change-work-around.patch;patch=1"

do_configure()  {
	install -m 0644 ${STAGING_DATADIR}/gnu-config/config.sub .
	install -m 0644 ${STAGING_DATADIR}/gnu-config/config.guess .
	oe_runconf
}

do_stage() {
	install -m 0755 src/m4 ${STAGING_BINDIR}/
}

