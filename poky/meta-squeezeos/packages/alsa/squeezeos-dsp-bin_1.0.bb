DESCRIPTION = "SqueezeOS DSP - Private code"
LICENSE = "Confidential"

PR = "r4"

PROVIDES = "squeezeos-dsp"

DEPENDS += "alsa-lib"

SRC_URI="file://libasound_module_pcm_babydsp.so"

S = "${WORKDIR}/squeezeos_dsp"

do_install() {
	mkdir -p ${D}/${libdir}/alsa-lib
	install -m 0644 ${WORKDIR}/libasound_module_pcm_babydsp.so ${D}/${libdir}/alsa-lib/libasound_module_pcm_babydsp.so
}

PACKAGES = "squeezeos-dsp squeezeos-dsp-dbg"

FILES_squeezeos-dsp = "${libdir}/alsa-lib"
FILES_squeezeos-dsp-dbg = "${libdir}/alsa-lib/.debug"
