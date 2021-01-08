DESCRIPTION = "A minimal SNMP agent implementation"
HOMEPAGE = "https://troglobit.com/projects/mini-snmpd/"
LICENSE = "GPLv2"
SECTION = "console/network"
PRIORITY = "optional"
PR = "r0"
S="${WORKDIR}/${PN}-${PV}"

SRC_URI = "https://codeload.github.com/troglobit/mini-snmpd/tar.gz/v${PV}?.tar.gz \
	file://old_autotools.patch;patch=1 \
	file://old_automake.patch;patch=1"

inherit autotools

do_stage() {
	autotools_stage_all
}
