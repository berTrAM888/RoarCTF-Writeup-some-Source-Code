#!/bin/bash

qemu-system-x86_64 -hda rootfs.img -kernel 4.20.0-bzImage -append 'console=ttyS0 root=/dev/sda rw nokaslr quiet' -m 128M -monitor /dev/null --nographic 
