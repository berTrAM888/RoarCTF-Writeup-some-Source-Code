FROM tomcat:8
MAINTAINER fuhei
ENV REFRESHED_AT 2019-09-01
ENV LANG C.UTF-8

RUN rm -rf /usr/local/tomcat/
COPY BBR/ /usr/local/tomcat

COPY start.sh /root/start.sh
RUN chmod +x /root/start.sh
ENTRYPOINT cd /root; ./start.sh

EXPOSE 80