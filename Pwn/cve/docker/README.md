## run as root

docker build . -t ctf
docker run -d -p "0.0.0.0:8888:8888" ctf

# start.sh 复制一份rootfs.img，避免修改rootfs.img原件，导致后面做题的选手看到前面的记录。
