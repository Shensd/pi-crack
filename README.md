# How To Use This

## Real Hardware Instructions

There is a bash script at the top level named `build.sh`, executing this (likely **with root permissions** since we are using loopback devices) should build the project, make a filesystem, move the needed files to the filesystem, and then unmount and produce an disk image named `disk.img`. 

This can then be written to an SD card with `dd if=disk.img of=/dev/sdx bs=1M`, where `/dev/sdx` is the SD card to be written to, not to a parition on it, but the *raw SD card*. I think it goes without saying this will completely roll the SD card so don't leave anything valuable on it.

At present the raspberry pi is completely interacted with over serial, [here](https://cdn-learn.adafruit.com/downloads/pdf/adafruits-raspberry-pi-lesson-5-using-a-console-cable.pdf "here") is a guide for doing so. You will need a [USB to TTL Serial cable](https://www.amazon.com/s?url=search-alias%3Daps&field-keywords=usb+to+ttl+serial+cable&rh=i%3Aaps%2Ck%3Ausb+to+ttl+serial+cable "USB to TTL Serial cable") if you are following this guide exactly. I won't detail it here but if you have an arduino and a way to connect it to the raspberry pi serial pins, you can use the pi's serial without that specific cable. 

Once you have the USB cable connected to the pins, run `dmesg -w` and connect it to your PC. If dmesg says that its connected to `/dev/ttyUSB0` then you can just move into the next step, but in my case I had to have it connected while I turned on the pi once. So connect the cable, power cycle the pi, and then move on. 

You can interface with the serial line with the command `screen /dev/ttyUSB0 115200`, this will almost certainly need to be run as root. If you did everything right you should see some output from the pi, but so far in my experience the mini UART provided by the chip is very unreliable and its rare that all characters make it across.

## Emulation Instructions

*These instructions are written for Debian based systems.*

Install QEMU with 
```
sudo apt install qemu-system qemu-system-arm
```
from the root of the project, build the project with `make` and then run it on QEMU with
```
qemu-system-aarch64 -nographic -m 1024 -M raspi3 -serial null -serial mon:stdio -kernel build/kernel8.img
```
This should print serial output to console. To exit the VM, hit `ctrl+a` and then `x`.

# Resources
Code from:
- https://github.com/mpaland/printf
	- Provides an embedded printf solution
- https://github.com/s-matyukevich/raspberry-pi-os
	- Bootloader code, mini uart code, and other boot resources
- https://github.com/RPi-Distro/pi-gen
	- Very useful in writing the script for auto-generating sd card images

Programming resources:
- https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf
	- Peripheral manual for the rpi's CPU
- https://jsandler18.github.io/
	- What lead me to the peripheral manual, plus some other good stuff