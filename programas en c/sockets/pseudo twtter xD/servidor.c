/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	int i;
	for(i = 1; i < argc; i++)
	{
		printf("argv[%d]: %s", i ,argv[i]);
		printf("\n");
	}
     return 0; 
}
