FROM cyc1e/modsecuritywaf
ENV LANG C.UTF-8
ENV DEBIAN_FRONTEND noninteractive
RUN sed -i 's/Options Indexes FollowSymLinks/Options None/' /etc/apache2/apache2.conf

ADD html.tar /var/www
COPY my.conf /usr/share/modsecurity-crs/activated_rules/
COPY security2.conf /etc/apache2/mods-available/
COPY php.ini /etc/php/7.0/apache2/
COPY flag /f1agg
RUN chmod 744 /f1agg
RUN chmod 755 /var/www/html
RUN chmod 744 /var/www/html/*
RUN chmod +x /start.sh
ENTRYPOINT ./start.sh
EXPOSE 80