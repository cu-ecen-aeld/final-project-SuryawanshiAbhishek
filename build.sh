#!/bin/bash
# Script to build image for qemu.
# Author: Siddhant Jajoo.
# Modified By: Abhishek Suryawanshi

git submodule init
git submodule sync
git submodule update

# local.conf won't exist until this step on first execution
source poky/oe-init-build-env

#Target 
CONFLINE="MACHINE = \"raspberrypi4\""
cat conf/local.conf | grep "${CONFLINE}" > /dev/null
local_conf_info=$?

#Licence
LICENCE="LICENSE_FLAGS_WHITELIST = \"commercial\""

#Wifi
DISTRO_F="DISTRO_FEATURES_append = \"wifi\""
cat conf/local.conf | grep "${DISTRO_F}" > /dev/null
local_distro_info=$?

#firmware
IMAGE_ADD="IMAGE_INSTALL_append = \"linux-firmware-rpidistro-bcm43430 v4l-utils python3 ntp wpa-supplicant\""
cat conf/local.conf | grep "${IMAGE_ADD}" > /dev/null
local_imgadd_info=$?

#ssh
IMAGE_F="IMAGE_FEATURES += \"ssh-server-openssh\""
cat conf/local.conf | grep "${IMAGE_F}" > /dev/null
local_imgf_info=$?

#wifi
#CORE_IM_ADD="CORE_IMAGE_EXTRA_INSTALL += \"i2c-config gpio-config client-config server-config wifi-init-configuration\""
#cat conf/local.conf | grep "${CORE_IM_ADD}" > /dev/null
#local_coreimadd_info=$?

#I2C
#MODULE_I2C="ENABLE_I2C = \"1\""
#cat conf/local.conf | grep "${MODULE_I2C}" > /dev/null
#local_i2c_info=$?

#Kernel Module
#AUTOLOAD_I2C="KERNEL_MODULE_AUTOLOAD:rpi += \"i2c-dev i2c-bcm2708\""
#cat conf/local.conf | grep "${AUTOLOAD_I2C}" > /dev/null
#local_i2c_autoload_info=$?

#Add files which are missing in local.conf

if [ $local_conf_info -ne 0 ];then
	echo "Append ${CONFLINE} in the local.conf file"
	echo ${CONFLINE} >> conf/local.conf
	
else
	echo "${CONFLINE} already exists in the local.conf file"
fi


if [ $local_distro_info -ne 0 ];then
        echo "Append ${DISTRO_F} in the local.conf file"
        echo ${DISTRO_F} >> conf/local.conf 
else
        echo "${DISTRO_F} already exists in the local.conf file"
fi

if [ $local_imgadd_info -ne 0 ];then
        echo "Append ${IMAGE_ADD} in the local.conf file"
        echo ${IMAGE_ADD} >> conf/local.conf
else
        echo "${IMAGE_ADD} already exists in the local.conf file"
fi

if [ $local_imgf_info -ne 0 ];then
        echo "Append ${IMAGE_F} in the local.conf file"
        echo ${IMAGE_F} >> conf/local.conf
else
        echo "${IMAGE_F} already exists in the local.conf file"
fi

#if [ $local_coreimadd_info -ne 0 ];then
#        echo "Append ${CORE_IM_ADD} in the local.conf file"
#        echo ${CORE_IM_ADD} >> conf/local.conf       
#else
#        echo "${CORE_IM_ADD} already exists in the local.conf file"
#fi

#if [ $local_i2c_info -ne 0 ];then
#        echo "Append ${MODULE_I2C} in the local.conf file"
#        echo ${MODULE_I2C} >> conf/local.conf
#else
#        echo "${MODULE_I2C} already exists in the local.conf file"
#fi

#if [ $local_i2c_autoload_info -ne 0 ];then
#        echo "Append ${AUTOLOAD_I2C} in the local.conf file"
#        echo ${AUTOLOAD_I2C} >> conf/local.conf
#else
#        echo "${AUTOLOAD_I2C} already exists in the local.conf file"
#fi

# Add required meta-layer

bitbake-layers show-layers | grep "meta-oe" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
	echo "Adding meta-oe layer"
	bitbake-layers add-layer ../meta-openembedded/meta-oe
else
	echo "meta-oe layer already exists"
fi

bitbake-layers show-layers | grep "meta-python" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-python layer"
        bitbake-layers add-layer ../meta-openembedded/meta-python
else
        echo "meta-python layer already exists"
fi

bitbake-layers show-layers | grep "meta-networking" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-networking layer"
        bitbake-layers add-layer ../meta-openembedded/meta-networking
else
        echo "meta-networking layer already exists"
fi

bitbake-layers show-layers | grep "meta-raspberrypi" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-raspberrypi layer"
        bitbake-layers add-layer ../meta-raspberrypi
else
        echo "meta-raspberrypi layer already exists"
fi
<<<comment
bitbake-layers show-layers | grep "meta-i2c" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-i2c layer"
        bitbake-layers add-layer ../meta-i2c
else
        echo "meta-i2c layer already exists"
fi


bitbake-layers show-layers | grep "meta-gpio" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-gpio layer"
        bitbake-layers add-layer ../meta-gpio
else
        echo "meta-gpio layer already exists"
fi

bitbake-layers show-layers | grep "meta-server" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-server layer"
        bitbake-layers add-layer ../meta-server
else
        echo "meta-server layer already exists"
fi

bitbake-layers show-layers | grep "meta-client" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-client layer"
        bitbake-layers add-layer ../meta-client
else
        echo "meta-client layer already exists"
fi

bitbake-layers show-layers | grep "meta-wifi" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-wifi layer"
        bitbake-layers add-layer ../meta-wifi
else
        echo "meta-wifi layer already exists"
fi

comment 

set -e

bitbake core-image-base