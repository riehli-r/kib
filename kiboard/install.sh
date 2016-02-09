make -C install/
echo "Node creation in progress"
sudo ./install/install_kiboard
make fclean -C install/
echo "Node creation done"
echo "Module compilation in progress"
make
echo "Module compilation done"
sudo insmod module/kiboard.ko
echo "Module instalation done"
make clean
