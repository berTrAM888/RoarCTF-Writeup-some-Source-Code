FROM ubuntu:18.04

RUN sed -i "s/http:\/\/archive.ubuntu.com/http:\/\/mirrors.tuna.tsinghua.edu.cn/g" /etc/apt/sources.list
RUN apt-get update && apt-get -y dist-upgrade
RUN apt-get update && apt-get install -y lib32z1 xinetd build-essential
RUN apt-get install -y qemu && apt-get install -y qemu-system

RUN useradd -m ctf
WORKDIR /home/ctf

#bin files
RUN mkdir /home/ctf/bin

COPY ./ctf.xinetd /etc/xinetd.d/ctf
COPY ./start.sh /home/ctf
COPY ./4.20.0-bzImage /home/ctf
COPY ./rootfs.img /home/ctf

RUN chmod +x /home/ctf/*

RUN echo "Blocked by ctf_xinetd" > /etc/banner_fail
RUN echo 'ctf - nproc 1500' >>/etc/security/limits.conf

CMD exec /bin/bash -c "/etc/init.d/xinetd start; trap : TERM INT; sleep infinity & wait"

EXPOSE 8888 
