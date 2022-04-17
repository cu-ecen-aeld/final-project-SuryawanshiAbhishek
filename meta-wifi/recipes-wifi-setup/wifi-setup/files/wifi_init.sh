#!/bin/sh

ifdown wlan0

cp /usr/bin/wpa_supplicant.conf  /etc/wpa_supplicant.conf

ifup wlan0




