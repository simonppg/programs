function [exectime, data] = node_sa37_t1(seg, data)
global temp;
switch seg,
 case 1, 
  ttFetch('sroom1');
  exectime = 0;
 case 2,
  ttEnterMonitor('mutex');   
  temp = ttRetrieve('sroom1');
  %fprintf('Var R21 %6.2f.\n',temp.R1v1);
  ttAnalogOut(1, temp.R1v1);
  ttAnalogOut(2, temp.R1v2);
  exectime = 0.0005;
 case 3,
   data.msg.uR1v1 = ttAnalogIn(1);
   data.msg.uR1v2 = ttAnalogIn(2);
   data.msg.type = 'croom1';
   ttSendMsg(35, data.msg, 80);  
   exectime = 0.0004; 
 case 4,
   ttExitMonitor('mutex'); 
   exectime = -1;     
 end