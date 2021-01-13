DESCRIPTION = "System watchdog daemon"
LICENSE = "GPL"
PR = "r0"

SRC_URI = " \
	https://downloads.sourceforge.net/project/watchdog/watchdog/${PV}/${PN}-${PV}.tar.gz \
	file://startup-delay.patch;patch=1 \
	file://watchdog-semaphore.patch;patch=1 \
	"

inherit autotools

FILES_${PN} = "${sbindir}/watchdog"
