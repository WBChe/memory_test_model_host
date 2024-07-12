#!bin/bash

echo "1" >/sys/bus/pci/devices/0000:05:00.0/remove
sleep 1s
echo "1" >/sys/bus/pci/rescan
chmod 666 /dev/xdma0_*
echo "sender rst success"
