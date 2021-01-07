DESCRIPTION = "stress"
SECTION = "bin"
LICENSE = "GPL"

#PR = "r0"

SRC_URI="http://weather.ou.edu/~apw/projects/stress/stress-${PV}.tar.gz \
	file://disable-docs.patch;patch=1"

S = "${WORKDIR}/stress-${PV}"

inherit autotools

PACKAGES = "stress"
FILES_${PN} = "${bindir}/*"
