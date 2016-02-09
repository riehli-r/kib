make -C install/
echo "Node creation in progress"
sudo ./install/install_mousetick
make fclean -C install/
echo "Node creation done"
echo "Module compilation in progress"
make
echo "Module compilation done"
sudo insmod module/mousetick.ko
echo "Module instalation done"
make clean
