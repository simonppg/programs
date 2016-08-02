#include<stdio.h>
#include<unistd.h>
void main()
{
	pid_t pid;
	pid = fork();
	if(pid==-1)
	{
		printf("Error al crear proceso hijo\n");
		exit(0);
	}
	if(pid)
	{
		printf("soy el padre, y el PID de mi hijo es %d\n");
	}
	else
	{
		printf("soy el hijo; y voy a ejecutar la herramienta date\n");
		execve("/bin/date",NULL,NULL);
	}
}
