Raspberry Pi Autostart SmartVideoCar:

sudo nano /etc/init.d/svc_startup

	edit file with init process

sudo chmod 755 /etc/init.d/svc_startup
sudo update-rc.d svc_startup defaults
sudo reboot


to stop the service: "sudo /etc/init.d/svc_startup stop"
or use "htop" and "sudo kill -kill <pid>"


compile line:
g++ -std=c++17 -pthread -O2 `pkg-config --cflags --libs opencv` smartvideocar_multithreaded.cpp rs232.c -o smartvideocar_noVideo_multiThreaded