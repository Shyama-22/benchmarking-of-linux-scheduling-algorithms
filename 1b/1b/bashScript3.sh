#/bin/bash
cd /home/kernel3/linux-5.15.79
make mrproper -s
sudo cp /home/ .config /home/kernel3/linux-5.15.79/ .config
make -j2 -s