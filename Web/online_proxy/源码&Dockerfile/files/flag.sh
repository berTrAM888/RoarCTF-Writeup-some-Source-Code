#!/bin/bash

if [[ -f /var/www/html/db.sql ]]; then
    mysql -e "source /var/www/html/db.sql" -uroot -proot
    rm -f /var/www/html/db.sql
fi

export FLAG=roarctf{760f51cfab7a9138}
mysql -e "USE F4l9_D4t4B45e;INSERT INTO F4l9_t4b1e VALUES('$FLAG');" -uroot -proot

export FLAG=not_flag
FLAG=not_flag

rm -f /flag.sh

chown -R root:root /var/www/html/
chmod -R 755 /var/www/html/
