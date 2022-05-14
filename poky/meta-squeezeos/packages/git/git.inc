DESCRIPTION = "The git revision control system used by the Linux kernel developers"
SECTION = "console/utils"
LICENSE = "GPL"
DEPENDS = "perl-native openssl curl zlib expat"

SRC_URI = "https://www.kernel.org/pub/software/scm/git/git-${PV}.tar.gz"

S = "${WORKDIR}/git-${PV}"

EXTRA_OECONF = "--with-perl=${STAGING_BINDIR_NATIVE}/perl --without-tcltk"

inherit autotools

do_install () {
	oe_runmake install prefix=${D} bindir=${D}${bindir} \
		template_dir=${D}${datadir}/git-core/templates \
		GIT_PYTHON_DIR=${D}${datadir}/git-core/python
}

FILES_${PN} += "${datadir}/git-core"

BBCLASSEXTEND = "native"
