#!/bin/sh
# Add your startup script
/usr/bin/python /home/rvm/server.py;
# DO NOT DELETE
/etc/init.d/xinetd start;
sleep infinity;

