DESCRIPTION = "SqueezePlay - Fab4 specific code"
LICENSE = "Logitech Public Source License"

PR = "r3"

PROVIDES = "squeezeplay-fab4"

DEPENDS += "squeezeplay"

SRC_URI="file://fab4_bsp.so"

S = "${WORKDIR}/squeezeplay_fab4"

do_install() {
	# move lua fab4 bsp module to correct location.
	mkdir -p ${D}${libdir}/lua/5.1
	install -m 0755 ${WORKDIR}/fab4_bsp.so ${D}${libdir}/lua/5.1/fab4_bsp.so
}

FILES_${PN} += "${datadir} ${libdir}/lua/5.1"
FILES_${PN}-dbg += "${libdir}/lua/5.1/.debug"
