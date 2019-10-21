FROM ubuntu:18.04

RUN sed -i 's/archive.ubuntu.com/asia-east1.gce.archive.ubuntu.com/g' /etc/apt/sources.list && apt update && apt-get install -y lib32z1 xinetd python-pip && rm -rf /var/lib/apt/lists/ && rm -rf /root/.cache && apt-get autoclean && rm -rf /tmp/* /var/lib/apt/* /var/cache/* /var/log/*
#apt update && apt-get install -y lib32z1 xinetd && rm -rf /var/lib/apt/lists/ && rm -rf /root/.cache && apt-get autoclean && rm -rf /tmp/* /var/lib/apt/* /var/cache/* /var/log/*

#RUN apt install -y python-pip python-dev && pip install pwntools
COPY ./pwn.xinetd /etc/xinetd.d/pwn

COPY ./service.sh /service.sh

RUN chmod +x /service.sh

# useradd and put flag
RUN useradd -m rvm && echo 'flag{funny_vm_with_negative_overflow}' > /home/rvm/flag
RUN mkdir /home/rvm/tmp
# copy bin
COPY ./bin/rvm /home/rvm/rvm
COPY ./server.py /home/rvm/server.py

# chown & chmod
RUN chown -R root:rvm /home/rvm && chmod -R 750 /home/rvm && chmod 740 /home/rvm/flag

EXPOSE 10050

CMD ["/service.sh"]

