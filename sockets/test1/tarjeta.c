#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int init_net();
int escucha();
int close_net();
int sensar();
int recibir();
int enviar();
int actuar();

static int sockfd, newsockfd, portno=10000;
static socklen_t clilen;
static char buffer[256];
static struct sockaddr_in serv_addr, cli_addr;
static int n;
static unsigned int ph;
static unsigned int maxInt;

int main() {
	maxInt = 2147483647;
	ph = 63;
	if(init_net() == 0) {
		printf("init_net\n");
		while(1) {
			printf("while 1 init\n");
			while(escucha() == 0) {
				printf("while escucha init\n");
				while(1) {
					printf("\n");
					//sensar();
					//enviar();
					sleep(1);
					recibir();
				}
				printf("while escucha end\n");
			}
			printf("while 1 end\n");
			sleep(1);
		}
	}
	printf("Saliendo\n");
	close_net();
	return 0;
}
int init_net(){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0){
		printf("ERROR opening socket");
		return -1;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		printf("ERROR on binding");
		return -1;
	}
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	
	return 0;
}

int escucha() {
	
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd < 0){
		printf("ERROR on accept");
		return -1;
	}
	printf("OK on accept");
	return 0;
}

int close_net() {
	close(newsockfd);
	close(sockfd);
	return 0;
}

int recibir() {
	bzero(buffer, 256);
	//n = read(newsockfd, buffer, 255);
	n = read(newsockfd, &ph, sizeof(int));
	if (n < 0){
		printf("ERROR reading from socket\n");
	}
	/*printf("Here is %d the message: %s\n", n, buffer);
	//[34],[31],[23]

	int b = n;
	while(n >= 0) {
		if(buffer[n] == 0x34 && buffer[n-1] == 0x31 && buffer[n-2] == 0x23){
			n=n-3;
			printf(" ");
		}
		printf("[%c],", buffer[n]);
		n--;
	}
	printf("\n");
	printf("\n");
	while(b >= 0) {
		if(buffer[b] == 0x34 && buffer[b-1] == 0x31 && buffer[b-2] == 0x23){
			b=b-3;
			printf(" ");
		}
		printf("[%x],", buffer[b]);
		b--;
	}*/

	//printf("\n");
	//exit(1);


	printf("Here is %d the message: %d\n", n, ph);
	return 0;
}

int enviar() {
	printf("Send ph: %d\n", ph);
	//n = write(newsockfd, "I got your message", 18);
	n = write(newsockfd, &ph, sizeof(int));
	//n = send(sockfd, &ph, sizeof(float),0);
	
	if (n < 0){
		printf("ERROR writing to socket");
		return -1;
	}
	return 0;
}

int sensar() {
	//ph++;
	return 0;
}

int actuar() {
	return 0;
}