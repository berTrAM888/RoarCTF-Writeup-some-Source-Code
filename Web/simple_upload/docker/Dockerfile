FROM php:7.2-apache
MAINTAINER fuhei
ENV REFRESHED_AT 2019-09-01
ENV LANG C.UTF-8

# ADD会自动解压压缩包，而COPY不会
COPY html/ /var/www/html
COPY flag /flag
RUN chmod 744 /flag
# 剩下一些操作（权限要控制好）
# 例如修改某个文件的所有者
RUN chown root:root /var/www/html/ -R
RUN chmod 755 /var/www/html/ -R
RUN chmod 777 /var/www/html/Public/Uploads -R
RUN chmod 777 /var/www/html/Application/Runtime -R

COPY start.sh /root/start.sh
# 加上执行权限
RUN chmod +x /root/start.sh
# 使用ENTRYPOINT而不使用CMD（CMD容易受run命令最后的命令给影响）
ENTRYPOINT cd /root; ./start.sh
# WEB开放端口默认为80，一般为一个，若有特殊情况，请写明
EXPOSE 80
