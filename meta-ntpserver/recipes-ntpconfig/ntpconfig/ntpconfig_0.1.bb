# See http://git.yoctoproject.org/cgit.cgi/poky/tree/meta/files/common-licenses
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://ntp.conf \
	   file://ntp_init.sh "

# See http://git.yoctoproject.org/cgit.cgi/poky/plain/meta/conf/bitbake.conf?h=warrior for yocto path prefixes
# Adding init script configurations
# these 3 lines will have the script run on boot
inherit update-rc.d
INITSCRIPT_PACKAGES = "${PN}"
INITSCRIPT_NAME = "ntp_init.sh"

do_install () {
	
	install -d ${D}${bindir}
	install -m 0755 ${WORKDIR}/ntp.conf ${D}${bindir}/ntp.conf
	
	#boot script
	install -d ${D}${INIT_D_DIR}
	install -m 0755 ${WORKDIR}/ntp_init.sh ${D}${INIT_D_DIR}/ntp_init.sh
}

FILES_${PN} += "${datadir}/ntp_custom/ntp.conf"
FILES_${PN} += "${INIT_D_DIR}/ntp_init.sh"
