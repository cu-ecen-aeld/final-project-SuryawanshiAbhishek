#!/bin/sh

#Author: Abhishek Suryawanshi
#filename: wifi-setup
#Auto configuration of wifi

echo "Starting Wifi-Setup Script..."
#Shutdown wifi service
ifdown wlan0

#ccpying file to /etc/wpa_supplicant.conf
cp /usr/bin/wpa_supplicant.conf  /etc/wpa_supplicant.conf


#Start wifi service
ifup wlan0

echo "Wifi-Setup Completed"





