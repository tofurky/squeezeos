require libdbd-sqlite-perl_${PV}.bb
inherit native

PR = "r10"

DEPENDS = "libdbi-perl-native sqlite3-native"
