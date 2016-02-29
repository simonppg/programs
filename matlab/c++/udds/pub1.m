function [exectime, data] =pub1(seg, data)

switch seg,
 case 1, 
  data.TimeDead=(ttCurrentTime-data.nexttime)+data.TimeDead;
  temp = ttTryFetch('croom5');
  if (~isempty(temp))
    while ((~isempty(temp))),
      data.uR5v1 = temp.uR5v1;
      data.uR5v2 = temp.uR5v2;
      temp = ttTryFetch('croom5');
    end
    data.TimeDead = 0;
    if (data.i==1) 
        data.uk11 = data.uR5v1;
        data.uk12 = data.uR5v2;
        data.i=data.i+1;
    end 
    if (data.i==2) 
        data.uk21 = data.uk11;
        data.uk22 = data.uk12;
        data.uk11 = data.uR5v1;
        data.uk12 = data.uR5v2;
        data.i=data.i+1;
    end  
    if (data.i==3) 
        data.uk31 = data.uk21;
        data.uk32 = data.uk22; 
        data.uk21 = data.uk11;
        data.uk22 = data.uk12;
        data.uk11 = data.uR5v1;
        data.uk12 = data.uR5v2;  
        data.i=1;
    end 
    ttAnalogOut(1, data.uR5v1)
    ttAnalogOut(2, data.uR5v2)
 end  

 if (data.TimeDead > 0.60)
     data.uR5v1 = data.Kc1*data.uk11+data.Kd1*(data.uk21 - data.uk31)/data.TimeDead;
     data.uR5v2 = data.Kc2*data.uk12+data.Kd2*(data.uk22 - data.uk32)/data.TimeDead;
     data.uk31=data.uk21;
     data.uk21=data.uk11;
     data.uk11=data.uR5v1;
     data.uk32=data.uk22;
     data.uk22=data.uk12;
     data.uk12=data.uR5v2;
     ttAnalogOut(1, data.uR5v1)
     ttAnalogOut(2, data.uR5v2)
     data.TimeDead = 0.0;
 end    
  exectime = 0.0008;
 case 2,
  data.nexttime=ttCurrentTime;
  exectime = -1; % finished
end
