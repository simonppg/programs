#!/bin/bash

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run with sudo" 1>&2
   exit 1
fi

set -e

# Build and install PRU DTBO
echo "Installing PRU Device Tree Overlay"
cd dtbos/
make
make install

#export paths
SLOTS=/sys/devices/bone_capemgr.*/slots
PINS=/sys/kernel/debug/pinctrl/44e10800.pinmux/pins
export SLOTS
export PINS
#cat $SLOTS
#cat $PINS

# Enable PRU
echo "Enabling PRU"
echo BB-BONE-PRU > /sys/devices/bone_capemgr.*/slots
echo BB-ADC > /sys/devices/bone_capemgr.*/slots
exit 0

