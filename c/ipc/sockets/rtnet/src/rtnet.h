#if !defined (_RTNET_H_)
#define _RTNET_H_

#define rtnet_task_period 	1000000000 	//(1s)
#define rtnet_task_prio 	40

enum STATUS {
	RUNNING, CREATED, FINISHED, INIT, WAITING, ERROR, REINIT
};

extern const char *STATUS_STRING[];

typedef struct {
	char* name;
	enum STATUS status;
	int onoff;
} thread_s;


void rtnet(void *arg);

#endif