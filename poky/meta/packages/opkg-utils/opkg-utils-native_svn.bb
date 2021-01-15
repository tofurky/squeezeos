require opkg-utils_svn.bb

RDEPENDS = ""

inherit native

# Avoid circular dependencies from package_ipk.bbclass
PACKAGES = ""

SRC_URI += "file://use_python2.patch;patch=1"
