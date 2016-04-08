function [exectime, data] = ctrl_code(segment, data)

switch segment
case 1
	y = ttAnalogIn(1);
	ttAnalogOut(1, y);
%	exectime = data.exectime;
%case 2
	y = ttAnalogIn(2);
	ttAnalogOut(2, y);
%	exectime = data.exectime;
%case 3
	y = ttAnalogIn(3);
	ttAnalogOut(3, y);
%	exectime = data.exectime;
%case 4
	y = ttAnalogIn(4);
	ttAnalogOut(4, y);
%	exectime = data.exectime;
%case 5
	y = ttAnalogIn(5);
	ttAnalogOut(5, y);
%	exectime = data.exectime;
%case 6
	y = ttAnalogIn(6);
	ttAnalogOut(6, y);
%	exectime = data.exectime;
%case 7
	y = ttAnalogIn(7);
	ttAnalogOut(7, y);
%	exectime = data.exectime;
%case 8
	y = ttAnalogIn(8);
	ttAnalogOut(8, y);
	exectime = data.exectime;
case 2
	%ttSleep(1);
	exectime = -1;
end
