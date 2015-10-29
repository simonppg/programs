/*
	Simple udp server
	Silver Moon (m00n.silv3r@gmail.com)
*/
#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
 
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

static float temp;
static float ph;
static float orp;
static float torque;
static float biomasa;
static float brix;

static long long getLong(uint64_t int64);
static double getDouble(uint64_t int64);
static float getFloat(uint32_t int32);
static uint16_t from8To16(uint8_t msb, uint8_t lsb);
static uint32_t from16to32(uint16_t msb, uint16_t lsb);
static uint64_t from32to64(uint32_t msb, uint32_t lsb);
 
void die(char *s)
{
	perror(s);
	exit(1);
}
 
int main(void)
{
	float tramaSalida[6];
	
	ph = 2;
	orp = 3;
	torque = 4;
	biomasa = 5;
	brix = 6;



	struct sockaddr_in si_me, si_other;
	 
	int s, i, slen = sizeof(si_other) , recv_len;
	char buf[BUFLEN];
	double a[BUFLEN];
	 
	//create a UDP socket
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		die("socket");
	}
	 
	// zero out the structure
	memset((char *) &si_me, 0, sizeof(si_me));
	 
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	 
	//bind socket to port
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
	{
		die("bind");
	}
	 
	//keep listening for data
	while(1)
	{
		//printf("Waiting for data...");
		fflush(stdout);
		bzero(buf, BUFLEN);
		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, a, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		{
			die("recvfrom()");
		}
		 
		//print details of the client/peer and the data received
		//printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		//printf("len: %d\n" , recv_len);
		//printf("Data: %d\n" , buf);

		int i;
		for (i = 0; i < recv_len; ++i)
		{
			printf("[%f], ", a[i]);
		}
		printf("\n");

		/*for (i = 0; i < recv_len; i+=8)
		{
			printf("[%lld],", getDouble(
						from32to64(
							from16to32(
								from8To16(buf[i+7],
									buf[i+6]),
								from8To16(buf[i+4],
									buf[i+4])
								),
							from16to32(
								from8To16(buf[i+3],
									buf[i+2]),
								from8To16(buf[i+1],
									buf[i])
								)
							)
						)
						);
			printf("[%lld],", getLong(
						from32to64(
							from16to32(
								from8To16(buf[i+7],
									buf[i+6]),
								from8To16(buf[i+4],
									buf[i+4])
								),
							from16to32(
								from8To16(buf[i+3],
									buf[i+2]),
								from8To16(buf[i+1],
									buf[i])
								)
							)
						)
						);
			printf("[%lld],", getDouble(
						from32to64(
							from16to32(
								from8To16(buf[i],
									buf[i+1]),
								from8To16(buf[i+2],
									buf[i+3])
								),
							from16to32(
								from8To16(buf[i+4],
									buf[i+5]),
								from8To16(buf[i+6],
									buf[i+7])
								)
							)
						)
						);
			printf("[%lld],", getLong(
						from32to64(
							from16to32(
								from8To16(buf[i],
									buf[i+1]),
								from8To16(buf[i+2],
									buf[i+3])
								),
							from16to32(
								from8To16(buf[i+4],
									buf[i+5]),
								from8To16(buf[i+6],
									buf[i+7])
								)
							)
						)
						);
		}*/
		 
		float data[6];
		data[0] = 1.0;
		data[1] = 2.0; 
		data[2] = 3.0;
		data[3] = 4.0;
		data[4] = 5.0;
		data[5] = 6.0;

		//now reply the client with the same data
		if (sendto(s, data, 6*4, 0, (struct sockaddr*) &si_other, slen) == -1)
		{
			die("sendto()");
		}
	}
 
	close(s);
	return 0;
}

static long long getLong(uint64_t int64)
{
	long long valor;
	valor = (long long) int64;
	return valor;
}

static double getDouble(uint64_t int64)
{
	double valor;
	uint64_t s, e, m;
	s = e = m = 0;
	s = (int64 & 0x80000000) >> 63;
	e = (int64 & 0x7F800000) >> 52;
	m = (int64 & 0x007FFFFF);
	valor = pow(-1,s)*(1.0+m/pow(2,52))*pow(2,(e-1023));
	return valor;
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

static uint64_t from32to64(uint32_t msb, uint32_t lsb)
{
	uint64_t valor;
	valor = msb;
	valor = valor << 32;
	valor = valor + lsb;
	return valor;
}