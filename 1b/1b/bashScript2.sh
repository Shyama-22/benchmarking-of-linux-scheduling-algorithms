#/bin/bash
cd /home/kernel2/linux-5.15.79
make mrproper -s
sudo cp /home/ .config /home/kernel2/linux-5.15.79/ .config
make -j2 -s