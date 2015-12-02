function [Dato,status]=fcn(Pulso,Contador,motorPAP1,motorPAP2,motorPAP3,motorPAP4,motorPAP5,servo1,servo2,servo3)
if (Pulso>0)&&(Contador==0)
Dato=-1;
status=0;
elseif (Pulso>0)&&(Contador==1) % Apartir de 100 son motoresPAP
Dato=100;
status=0;
elseif (Pulso>0)&&(Contador==2)
Dato=motorPAP1;
status=0;
elseif (Pulso>0)&&(Contador==3)
Dato=101;
status=0;
elseif (Pulso>0)&&(Contador==4)
Dato=motorPAP2;
status=0;
elseif (Pulso>0)&&(Contador==5)
Dato=102;
status=0;
elseif (Pulso>0)&&(Contador==6)
Dato=motorPAP3;
status=0;
elseif (Pulso>0)&&(Contador==7)
Dato=103;
status=0;
elseif (Pulso>0)&&(Contador==8)
Dato=motorPAP4;
status=0;
elseif (Pulso>0)&&(Contador==9)
Dato=104;
status=0;
elseif (Pulso>0)&&(Contador==10)
Dato=motorPAP5;
status=0;
elseif (Pulso>0)&&(Contador==11) % Apartir de 200 son servos
Dato=200;
status=0;
elseif (Pulso>0)&&(Contador==12)
Dato=servo1;
status=0;
elseif (Pulso>0)&&(Contador==13)
Dato=201;
status=0;
elseif (Pulso>0)&&(Contador==14)
Dato=servo2;
status=0;
elseif (Pulso>0)&&(Contador==15)
Dato=202;
status=0;
elseif (Pulso>0)&&(Contador==16)
Dato=servo3;
status=0;
elseif (Pulso>0)&&(Contador==17)
Dato=-2;
status=1;
else
Dato=-1; % pulso de sincronización para el microcontrolador
status=0;
end


if(Pulso>0)
	for lp = 1:17
    	fprintf('%d squared\n', lp);
	end
end