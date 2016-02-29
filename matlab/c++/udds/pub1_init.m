function pub1_init

% Initialize TrueTime kernel
ttInitKernel('prioEDF'); % fixed priority

% Create mailboxes
ttCreateMailbox('croom5', 1)
data.nexttime=0;
data.TimeDead = 0;
data.Kc1=1;
data.Kc2=1;
data.Kd1=0.2;
data.Kd2=0.2;
data.uk11=0;
data.uk21=0;
data.uk31=0;
data.uk12=0;
data.uk22=0;
data.uk32=0;
data.i=1;
data.uR5v1 = 0;
data.uR5v2 = 0;
period =0.05; %equivale a 36s
offset = 0.028;
ttCreatePeriodicTask('pub1_task', offset, period, 'pub1', data);

% Initialize network
ttCreateHandler('nw_handler_pub1', 1, 'msgRcv_pub1');
ttAttachNetworkHandler('nw_handler_pub1');
