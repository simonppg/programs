function Dato=fcn(Pulso,Contador,motorPAP1,motorPAP2,motorPAP3,motorPAP4,motorPAP5,servo1,servo2,servo3)
if (Pulso>0)&&(Contador==0)
Dato=-1;
elseif (Pulso>0)&&(Contador==1) % Apartir de 100 son motoresPAP
Dato=100;
elseif (Pulso>0)&&(Contador==2)
Dato=motorPAP1;
elseif (Pulso>0)&&(Contador==3)
Dato=101;
elseif (Pulso>0)&&(Contador==4)
Dato=motorPAP2;
elseif (Pulso>0)&&(Contador==5)
Dato=102;
elseif (Pulso>0)&&(Contador==6)
Dato=motorPAP3;
elseif (Pulso>0)&&(Contador==7)
Dato=103;
elseif (Pulso>0)&&(Contador==8)
Dato=motorPAP4;
elseif (Pulso>0)&&(Contador==9)
Dato=104;
elseif (Pulso>0)&&(Contador==10)
Dato=motorPAP5;
elseif (Pulso>0)&&(Contador==11) % Apartir de 200 son servos
Dato=200;
elseif (Pulso>0)&&(Contador==12)
Dato=servo1;
elseif (Pulso>0)&&(Contador==13)
Dato=201;
elseif (Pulso>0)&&(Contador==14)
Dato=servo2;
elseif (Pulso>0)&&(Contador==15)
Dato=202;
elseif (Pulso>0)&&(Contador==16)
Dato=servo3;
elseif (Pulso>0)&&(Contador==17)
Dato=-2;
else
Dato=-1; % pulso de sincronización para el microcontrolador
end



function Dato=fcn(Pulso,Contador,motorPAP1,motorPAP2,motorPAP3,motorPAP4,motorPAP5,servo1,servo2,servo3)
if (Pulso>0)&&(Contador==0)
Dato=-1;
elseif (Pulso>0)&&(Contador==1) % Apartir de 100 son motoresPAP
Dato=motorPAP1;
elseif (Pulso>0)&&(Contador==2)
Dato=motorPAP2;
elseif (Pulso>0)&&(Contador==3)
Dato=motorPAP3;
elseif (Pulso>0)&&(Contador==4)
Dato=motorPAP4;
elseif (Pulso>0)&&(Contador==5)
Dato=motorPAP5;
elseif (Pulso>0)&&(Contador==6) % Apartir de 200 son servos
Dato=servo1;
elseif (Pulso>0)&&(Contador==7)
Dato=servo2;
elseif (Pulso>0)&&(Contador==8)
Dato=servo3;
elseif (Pulso>0)&&(Contador==9)
Dato=-2;
else
Dato=-1; % pulso de sincronización para el microcontrolador
end