DESCRIPTION = "SqueezePlay - Fab4 specific code"
LICENSE = "Logitech Public Source License"

PR = "r4"

PROVIDES = "squeezeplay-fab4-bin"

DEPENDS += "squeezeplay"

SRC_URI=" \
	file://fab4_bsp.so \
	file://libspotify.so.6.0.600035 \
	"

S = "${WORKDIR}/squeezeplay_fab4"

do_install() {
	# move lua fab4 bsp module to correct location.
	mkdir -p ${D}${libdir}/lua/5.1
	install -m 0755 ${WORKDIR}/fab4_bsp.so ${D}${libdir}/lua/5.1/fab4_bsp.so

	install -m 0755 ${WORKDIR}/libspotify.so.6.0.600035 ${D}${libdir}/libspotify.so.6.0.600035
	cd ${D}${libdir}; ln -sf libspotify.so.6.0.600035 libspotify.so.6

}

FILES_${PN} += "${datadir} ${libdir}/lua/5.1"
FILES_${PN}-dbg += "${libdir}/lua/5.1/.debug"
