%truetime
setenv('TTKERNEL', '/home/x86/truetime/kernel')
addpath([getenv('TTKERNEL')])
addpath([getenv('TTKERNEL') '/matlab'])
addpath([getenv('TTKERNEL') '/matlab/help'])
init_truetime
open net.slx