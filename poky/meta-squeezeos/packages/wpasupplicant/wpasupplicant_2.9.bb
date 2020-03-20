DESCRIPTION = "wpasupplicant"
SECTION = "base"
LICENSE = "GNU GPL"

PR = "r0"

SRC_URI = "http://hostap.epitest.fi/releases/wpa_supplicant-${PV}.tar.gz \
	   file://defconfig"

S = "${WORKDIR}/wpa_supplicant-${PV}/wpa_supplicant"

# With the csl2010q1 and high optimization it fails. 'arm' instruction set to be safe
ARM_INSTRUCTION_SET = "arm"
FULL_OPTIMIZATION = "-O1 -s"

inherit autotools

do_configure () {
	install -m 0644 ${WORKDIR}/defconfig ${S}/.config
}

do_compile() {
##	make clean
	oe_runmake all
}

do_install() {
	install -m 0755 -d ${D}${sbindir}

	# Install wpa_supplicant, wpa_cli
	install -m 0755 ${S}/wpa_supplicant ${D}${sbindir}/wpa_supplicant
	install -m 0755 ${S}/wpa_cli ${D}${sbindir}/wpa_cli
}

PACKAGES = "wpasupplicant-dbg wpasupplicant"

FILES_wpasupplicant = "${sbindir}"
FILES_wpasupplicant-dbg = "${sbindir}.debug"

