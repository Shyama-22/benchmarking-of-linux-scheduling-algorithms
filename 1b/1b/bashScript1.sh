#/bin/bash
cd /home/kernel1/linux-5.15.79
make mrproper -s
sudo cp /home/ .config /home/kernel1/linux-5.15.79/ .config
make -j2 -s