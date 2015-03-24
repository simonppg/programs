#!/bin/sh
 #compilando sistema
sudo make

#instalando script para iniciar y detener el demonio
sudo mv indessy /etc/init.d/
sudo chmod 755 /etc/init.d/indessy
sudo chown root:root /etc/init.d/indessy

#creando enlaces simbólicos para los run levels
sudo ln -s  /etc/init.d/indessy /etc/rc1.d/S76indessy
sudo ln -s  /etc/init.d/indessy /etc/rc2.d/S76indessy
sudo ln -s  /etc/init.d/indessy /etc/rc3.d/S76indessy
sudo ln -s  /etc/init.d/indessy /etc/rc4.d/S76indessy
sudo ln -s  /etc/init.d/indessy /etc/rc5.d/S76indessy
sudo ln -s  /etc/init.d/indessy /etc/rc0.d/K76indessy
sudo ln -s  /etc/init.d/indessy /etc/rc1.d/K76indessy
sudo ln -s  /etc/init.d/indessy /etc/rc6.d/K76indessy

#instalando sistema indessy
sudo chmod 775 sistema.out
sudo chown root:root sistema.out
sudo mv sistema.out /usr/sbin