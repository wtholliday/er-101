#! /bin/sh
echo "Erasing flash..."
dfu-programmer at32uc3c1512 erase
echo "Writing new firmware..."
dfu-programmer at32uc3c1512 flash er-101-firmware-2.10.hex --suppress-bootloader-mem
echo "Restarting device..."
dfu-programmer at32uc3c1512 reset
