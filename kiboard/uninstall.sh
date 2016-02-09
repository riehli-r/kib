echo "Module compilation in progress"
make
echo "Module compilation done"
sudo rmmod module/kiboard.ko
echo "Module uninstalation done"
make clean
sudo rm /dev/Kiboard
