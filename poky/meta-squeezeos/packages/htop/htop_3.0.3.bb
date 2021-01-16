SUMMARY = "Interactive process viewer"
HOMEPAGE = "https://htop.dev"
SECTION = "console/utils"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=4099d367cd5e59b6d4fc1ee33accb891"

DEPENDS = "ncurses"

SRC_URI = "git://github.com/htop-dev/htop.git;protocol=git \
	file://configure_without_ncurses-config.patch;patch=1 \
	file://opath_define.patch;patch=1 \
	file://escdelay_missing.patch;patch=1"

#SRCREV = "4c8bc0158a6a14e2956d48ebe0caf5cc681e9dd8"
SRCREV = "${PV}"

S = "${WORKDIR}/git"

CFLAGS_prepend = "-lrt "

#inherit autotools pkgconfig
inherit autotools

EXTRA_OECONF = "--disable-unicode"

#PACKAGECONFIG ??= "cgroup \
#                   taskstats \
#                   unicode \
#                   linux-affinity \
#                   delayacct"
#PACKAGECONFIG[openvz] = "--enable-openvz,--disable-openvz"
#PACKAGECONFIG[cgroup] = "--enable-cgroup,--disable-cgroup"
#PACKAGECONFIG[vserver] = "--enable-vserver,--disable-vserver"
#PACKAGECONFIG[taskstats] = "--enable-taskstats,--disable-taskstats"
#PACKAGECONFIG[unicode] = "--enable-unicode,--disable-unicode"
#PACKAGECONFIG[linux-affinity] = "--enable-linux-affinity,--disable-linux-affinity"
#PACKAGECONFIG[hwloc] = "--enable-hwloc,--disable-hwloc,hwloc"
#PACKAGECONFIG[setuid] = "--enable-setuid,--disable-setuid"
#PACKAGECONFIG[delayacct] = "--enable-delayacct,--disable-delayacct,libnl"
