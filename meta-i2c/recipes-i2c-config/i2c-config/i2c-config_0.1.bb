# See http://git.yoctoproject.org/cgit.cgi/poky/tree/meta/files/common-licenses
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Location of files in the current directory
SRC_URI = "file://mlx90614.c \
           file://htud21.c \
           file://Makefile"


S = "${WORKDIR}"

FILES_${PN} += "${bindir}/mlx90614test"
FILES_${PN} += "${bindir}/htud21test"


do_configure () {
        :
}

do_compile () {
        oe_runmake
}

do_install () {

        #Install your binaries/scripts here.
        install -d ${D}${bindir}
        install -m 0755 ${WORKDIR}/mlx90614test ${D}${bindir}/
        install -m 0755 ${WORKDIR}/htud21test ${D}${bindir}/
}

