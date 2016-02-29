function node_sa37_init

% Distributed control system: actuator node
%
% Receives messages from the controller and actuates 
% the plant.

% Initialize TrueTime kernel
ttInitKernel('prioEDF'); % fixed priority


% Create mailboxes
ttCreateMailbox('sroom1', 10)
ttCreateMailbox('sroom2', 10)
ttCreateMailbox('sroom3', 10)
ttCreateMailbox('sroom4', 10)
ttCreateMailbox('sroom5', 10)
ttCreateMailbox('sroom6', 10)
ttCreateMailbox('sroom7', 10)
ttCreateMailbox('sroom8', 10)
ttCreateMailbox('sroom9', 10)
ttCreateMailbox('sroom10', 10)
ttCreateMailbox('sroom11', 10)
ttCreateMailbox('sroom12', 10)
ttCreateMonitor('mutex')
prio=1;
deadline37_t1 = 0.5; 
ttCreateTask('node_sa37_t1_task', deadline37_t1, 'node_sa37_t1');
ttSetPriority(prio, 'node_sa37_t1_task');

prio=1;
deadline37_t2 = 0.5; 
ttCreateTask('node_sa37_t2_task', deadline37_t2, 'node_sa37_t2');
ttSetPriority(prio, 'node_sa37_t2_task');

prio=1;
deadline37_t3 = 0.5; 
ttCreateTask('node_sa37_t3_task', deadline37_t3, 'node_sa37_t3');
ttSetPriority(prio, 'node_sa37_t3_task');

prio=1;
deadline37_t4 = 0.5; 
ttCreateTask('node_sa37_t4_task', deadline37_t4, 'node_sa37_t4');
ttSetPriority(prio, 'node_sa37_t4_task');

prio=1;
deadline37_t5 = 0.5; 
ttCreateTask('node_sa37_t5_task', deadline37_t5, 'node_sa37_t5');
ttSetPriority(prio, 'node_sa37_t5_task');

prio=1;
deadline37_t6 = 0.5; 
ttCreateTask('node_sa37_t6_task', deadline37_t6, 'node_sa37_t6');
ttSetPriority(prio, 'node_sa37_t6_task');

prio=1;
deadline37_t7 = 0.5; 
ttCreateTask('node_sa37_t7_task', deadline37_t7, 'node_sa37_t7');
ttSetPriority(prio, 'node_sa37_t7_task');

prio=1;
deadline37_t8 = 0.5; 
ttCreateTask('node_sa37_t8_task', deadline37_t8, 'node_sa37_t8');
ttSetPriority(prio, 'node_sa37_t8_task');

prio=1;
deadline37_t9 = 0.5; 
ttCreateTask('node_sa37_t9_task', deadline37_t9, 'node_sa37_t9');
ttSetPriority(prio, 'node_sa37_t9_task');

prio=1;
deadline37_t10 = 0.5; 
ttCreateTask('node_sa37_t10_task', deadline37_t10, 'node_sa37_t10');
ttSetPriority(prio, 'node_sa37_t10_task');

prio=1;
deadline37_t11 = 0.5; 
ttCreateTask('node_sa37_t11_task', deadline37_t11, 'node_sa37_t11');
ttSetPriority(prio, 'node_sa37_t11_task');

prio=1;
deadline37_t12 = 0.5; 
ttCreateTask('node_sa37_t12_task', deadline37_t12, 'node_sa37_t12');
ttSetPriority(prio, 'node_sa37_t12_task');


% Initialize network
ttCreateHandler('nw_handler_sa37', 1, 'msgRcvnode_sa37');
ttAttachNetworkHandler('nw_handler_sa37');