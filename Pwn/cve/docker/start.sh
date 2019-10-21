#!/bin/bash

cd /home/ctf
tmp=`date +%N`
cp rootfs.img $tmp
timeout 180 qemu-system-x86_64 -hda $tmp -kernel 4.20.0-bzImage -append 'console=ttyS0 root=/dev/sda rw nokaslr quiet' -m 128M --nographic -monitor /dev/null
rm $tmp
exit 0
