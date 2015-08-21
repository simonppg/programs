function [canal1,canal2,canal3,canal4,canal5,canal6]= fcn(Dato,Canal)
if (Canal==0)
canal1=Dato;
canal2=0;
canal3=0;
canal4=0;
canal5=0;
canal6=0; % Condición para asignar dato de entrada a Canal 1.
elseif (Canal==1) % Condición para asignar dato de entrada a Canal 2.
canal1=0;
canal2=Dato;
canal3=0;
canal4=0;
canal5=0;
canal6=0;
elseif (Canal==2)
canal1=0;
canal2=0;
canal3=Dato;
canal4=0;
canal5=0;
canal6=0; % Condición para asignar dato de entrada a Canal 3.
elseif (Canal==3)
canal1=0;
canal2=0;
canal3=0;
canal4=Dato;
canal5=0;
canal6=0; % Condición para asignar dato de entrada a Canal 4.
elseif (Canal==4)
canal1=0;
canal2=0;
canal3=0;
canal4=0;
canal5=Dato;
canal6=0; % Condición para asignar dato de entrada a Canal 5.
elseif (Canal==5) && (Dato<10000) % Condición para asignar dato a Canal 6 y sincronización.
canal1=0;
canal2=0;
canal3=0;
canal4=0;
canal5=0;
canal6=Dato;
else
canal1=0;
canal2=0;
canal3=0;
canal4=0;
canal5=0;
canal6=0;
end