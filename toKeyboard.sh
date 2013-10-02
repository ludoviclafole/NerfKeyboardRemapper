#! /bin/sh

sudo dfu-programmer atmega16u2 erase
sudo dfu-programmer atmega16u2 flash --debug 1 firmwares/keyboard.hex
sudo dfu-programmer atmega16u2 reset
