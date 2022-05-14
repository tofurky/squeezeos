require git.inc

PR = "r0"

EXTRA_OECONF += "ac_cv_snprintf_returns_bogus=no ac_cv_c_c99_format=yes \
                 ac_cv_fread_reads_directories=${ac_cv_fread_reads_directories=yes} \
                 "

SRC_URI[md5sum] = "8d759f3477e5bd9fddeeb07a4a3b5136"
SRC_URI[sha256sum] = "41662c52fc16fec4963bfc41075e71f8ead6b5e386797eb6f9a1111ff95a8ddf"
