#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>

#define BUFFER_SIZE 		256
#define ELEMENTS_IN_TRAMA 	8*2 	//8 pares de datos (clave, setPoint)
#define ELEMENTS_SIZE 		7

typedef unsigned char 			uint8_t;

static int sockfd, newsockfd, portno=10000;
static socklen_t clilen;
static uint8_t buffer[BUFFER_SIZE];
static float setPoints[ELEMENTS_IN_TRAMA];
static struct sockaddr_in serv_addr, cli_addr;
static int n;
static float temp;
static float ph;
static float orp;
static float torque;
static float biomasa;
static float brix;

int init_net();
int escucha();
int close_net();
int sensar();
int recibir();
int enviar();
int actuar();
int buscaTrama(uint8_t *buffer, int size, int *begin, int *end);
static float getFloat(uint32_t int32);
static uint16_t from8To16(uint8_t msb, uint8_t lsb);
static uint32_t from16to32(uint16_t msb, uint16_t lsb);
static int beginTramaBE(uint8_t *buffer, int i);
static int endTramaBE(uint8_t *buffer, int i);
static int beginTramaLE(uint8_t *buffer, int i);
static int endTramaLE(uint8_t *buffer, int i);
static int getSetPointsBE(float *setPoints, uint8_t *buffer, int noElementos, int begin);
static int getSetPointsLE(float *setPoints, uint8_t *buffer, int noElementos, int begin);

int main() {
	if(init_net() == 0) {
		printf("init_net\n");
		while(1) {
			printf("while 1 init\n");
			while(escucha() == 0) {
				printf("while escucha init\n");
				while(1) {
					//printf("\n");
					//sensar();
					int a = -1;
					int intentos = 0;
					while((a = enviar()) != 0) 
					{
						//sleep(1);
						/*if(intentos == 1)
							break;
						intentos++;*/
					}
					a = -1;
					intentos = 0;
					while((a = recibir()) != 0)
					{
						printf("recibiendo...\n");
						//sleep(1);
						/*if(intentos == 1)
							break;
						intentos++;*/
					}
					/*recibir();
					enviar();
					sleep(1);*/
					//sleep(1);
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
		printf("ERROR on binding\n");
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
	//printf("\nRead\n");
	int noRecv = 0;
	bzero(buffer, 256);
	n = read(newsockfd, buffer, 255);
	//n = read(newsockfd, &ph, sizeof(int));
	if (n < 0){
		//printf("ERROR reading from socket\n");
	}
	//printf("Here is %d the message: %s\n", n, buffer);

	noRecv = n;

	while(n >= 0) {
		if(buffer[n] == 0x34 &&
			buffer[n - 1] == 0x31 &&
			buffer[n - 2] == 0x23) {
			n = n - 3;
			//printf("\n");
		}
		//printf("[%x],", buffer[n]);
		n--;
	}

	//printf("\n");
	//printf("\n");
	//printf("Datos leidos: %d\n", noRecv);
	int inicio = 0;
	int fin = 0;
	int result;
	if((result  = buscaTrama(buffer, noRecv, &inicio, &fin)) == 0 ) {
		//printf("Hay una trama desde %d hasta %d, %d\n", inicio, fin, fin - inicio);
		int elementos = (fin - inicio - 7) / ELEMENTS_SIZE;
		int resuduo = (fin - inicio - 7) % ELEMENTS_SIZE;
		printf("Elementos en la trama: %d, resuduo: %d\n", elementos, resuduo);
		if(resuduo == 0)
		{
			bzero(setPoints, ELEMENTS_IN_TRAMA);
			getSetPointsLE(setPoints, buffer, elementos, inicio);
			int count = 0;
			while(count < elementos) {
				//printf("[%f], ", setPoints[count]);
				if((count % 2) != 0){
					//printf("\n");
				}
				count++;
			}

			/*int recorre1 = 0;
			while(recorre1 <= noRecv) {
				printf("[%x],", buffer[recorre1]);
				recorre1++;
			}*/
			//exit(0);
			return 0;
		}
	}
	if(result == -1 && noRecv > 100) {
		//printf("result: %d, noRecv: %d\n", result, noRecv);
		//printf("%s\n", buffer);
		
		/*int recorre = 0;
		while(recorre <= noRecv) {
			printf("[%x],", buffer[recorre]);
			recorre++;
		}*/

		//exit(-1);
	}

	printf("Read fail\n");
	//printf("\n");
	//exit(1);	
	return -1;
}

int enviar() {
	/*printf("\nSend: %.4f, %.4f, %.4f, %.4f, %.4f, %.4f\n",
		temp, ph, orp,
		torque, biomasa, brix);*/
	//n = write(newsockfd, "I got your message", 18);
	//n = write(newsockfd, &ph, sizeof(int));
	//n = send(sockfd, &ph, sizeof(float),0);

	float tramaSalida[14];
	temp = 1.5;
	ph = 2;
	orp = 3;
	torque = 4;
	biomasa = 5;
	brix = 6;

	/*tramaSalida[0] = -1;
	tramaSalida[1] = 300;
	tramaSalida[2] = temp; 
	tramaSalida[3] = 1; 
	tramaSalida[4] = ph; 
	tramaSalida[5] = 1;
	tramaSalida[6] = orp;
	tramaSalida[7] = 1;
	tramaSalida[8] = torque;
	tramaSalida[9] = 1;
	tramaSalida[10] = biomasa;
	tramaSalida[11] = 1;
	tramaSalida[12] = brix;
	tramaSalida[13] = -2;*/


	tramaSalida[0] = temp; 
	tramaSalida[1] = ph; 
	tramaSalida[2] = orp;
	tramaSalida[3] = torque;
	tramaSalida[4] = biomasa;
	tramaSalida[5] = brix;

	uint8_t valortemp;
	uint8_t valor;
	uint32_t tramaSalidaBinblock[12];

	//Esta funciono con binary
	n = send(newsockfd, &tramaSalida, 6 * sizeof(float), MSG_NOSIGNAL);
	

	/*valortemp = temp << 8
	valor = (temp & 0xFF000000) >> 24;
	tramaSalidaBinblock[]*/

	/*n = send(sockfd, &temp, sizeof(float),0);
	n = send(sockfd, &ph, sizeof(float),0);
	n = send(sockfd, &orp, sizeof(float),0);
	n = send(sockfd, &torque, sizeof(float),0);
	n = send(sockfd, &biomasa, sizeof(float),0);
	n = send(sockfd, &brix, sizeof(float),0);*/
	
	//printf("Send end\n");
	if (n < 0){
		printf("ERROR writing to socket");
		return -1;
	}
	printf("total de envios: %d\n", n);
	
	return 0;
}

int sensar() {
	//ph++;
	return 0;
}

int actuar() {
	return 0;
}

int buscaTrama(uint8_t *buffer, int size, int *begin, int *end) {
	int i, hayInicio = 0, hayFin = 0;
	for (i = 0; i < size; ++i)
	{
		if(beginTramaLE(buffer, i) == 0) {
			//printf(" begin\n");
			if(hayInicio == 0)
				*begin = i;
			hayInicio++;
		}
		else if(endTramaLE(buffer, i) == 0) {
			//printf(" end\n");
			if(hayInicio == 1){
				*end = i;
				hayFin++;
			}
		}
		else if(buffer[i] == 0x34){
			//printf("[%x],\n", buffer[i]);
		}
		else {
			//printf("[%x],", buffer[i]);
		}
		if(hayInicio == 1 && hayFin == 1)
			return 0;
	}
	return -1;
}

int getSetPointsBE(float *setPoints, uint8_t *buffer, int noElementos, int begin) {
	begin += 7;
	int count = 0;
	//float elementos[ELEMENTS_IN_TRAMA];
	while(count < noElementos) {
		setPoints[count] = getFloat(
							from16to32(
								from8To16(
									buffer[begin + (ELEMENTS_SIZE * count)],
									buffer[begin + (ELEMENTS_SIZE * count) + 1]),
								from8To16(
									buffer[begin + (ELEMENTS_SIZE * count) + 2],
									buffer[begin + (ELEMENTS_SIZE * count) + 3])
								)
							);
		count++;
	}
	return 0;
}

int getSetPointsLE(float *setPoints, uint8_t *buffer, int noElementos, int begin) {
	begin += 7;
	int count = 0;
	//float elementos[ELEMENTS_IN_TRAMA];
	while(count < noElementos) {
		setPoints[count] = getFloat(
							from16to32(
								from8To16(
									buffer[begin + (ELEMENTS_SIZE * count) + 3],
									buffer[begin + (ELEMENTS_SIZE * count) + 2]),
								from8To16(
									buffer[begin + (ELEMENTS_SIZE * count) + 1],
									buffer[begin + (ELEMENTS_SIZE * count)])
								)
							);
		count++;
	}
	return 0;
}

int beginTramaBE(uint8_t *buffer, int i) {
	if(i+6 > BUFFER_SIZE)
		return -1;
	if(buffer[i] == 0xbf &&
		buffer[i + 1] == 0x80 &&
		buffer[i + 2] == 0x0 &&
		buffer[i + 3] == 0x0 &&
		buffer[i + 4] == 0x23 &&
		buffer[i + 5] == 0x31 &&
		buffer[i + 6] == 0x34)//-1
		return 0;
	return -1;
}

static int endTramaBE(uint8_t *buffer, int i) {
	if(i+6 > BUFFER_SIZE)
		return -1;
	if(buffer[i] == 0xc0 &&
		buffer[i + 1] == 0x0 &&
		buffer[i + 2] == 0x0 &&
		buffer[i + 3] == 0x0 &&
		buffer[i + 4] == 0x23 &&
		buffer[i + 5] == 0x31 &&
		buffer[i + 6] == 0x34)//-2
		return 0;
	return -1;
}

int beginTramaLE(uint8_t *buffer, int i) {
	if(i+6 > BUFFER_SIZE)
		return -1;
	if(buffer[i] == 0x0 &&
		buffer[i + 1] == 0x0 &&
		buffer[i + 2] == 0x80 &&
		buffer[i + 3] == 0xbf &&
		buffer[i + 4] == 0x23 &&
		buffer[i + 5] == 0x31 &&
		buffer[i + 6] == 0x34)//-1
		return 0;
	return -1;
}

static int endTramaLE(uint8_t *buffer, int i) {
	if(i+6 > BUFFER_SIZE)
		return -1;
	if(buffer[i] == 0x0 &&
		buffer[i + 1] == 0x0 &&
		buffer[i + 2] == 0x0 &&
		buffer[i + 3] == 0xc0 &&
		buffer[i + 4] == 0x23 &&
		buffer[i + 5] == 0x31 &&
		buffer[i + 6] == 0x34)//-2
		return 0;
	return -1;
}

static float getFloat(uint32_t int32)
{
	float valor;
	uint32_t s, e, m;
	s = e = m = 0;
	s = (int32 & 0x80000000) >> 31;
	e = (int32 & 0x7F800000) >> 23;
	m = (int32 & 0x007FFFFF);
	valor = pow(-1,s)*(1.0+m/pow(2,23))*pow(2,(e-127));
	return valor;
}

static uint16_t from8To16(uint8_t msb, uint8_t lsb)
{
	uint16_t valor;
	valor = msb;
	valor = valor << 8;
	valor = valor + lsb;
	return valor;
}

static uint32_t from16to32(uint16_t msb, uint16_t lsb)
{
	uint32_t valor;
	valor = msb;
	valor = valor << 16;
	valor = valor + lsb;
	return valor;
}