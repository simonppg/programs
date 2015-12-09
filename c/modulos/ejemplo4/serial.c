#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "serial.h"

int UartInit()
{
  struct termios newtio;
  fd_uart = open(XBEE_DEV, O_RDWR | O_NOCTTY);
  if (fd_uart < 0)
  {
    perror("open_port: unable to open /dev/ttyACM0");
    exit(-1);  
  }
  
  bzero(&newtio, sizeof(newtio));
  newtio.c_cflag = BAUDRATE  | CRTSCTS | CS8 | CLOCAL | CREAD; 
  newtio.c_iflag = IGNPAR;
  newtio.c_oflag = 0;
  newtio.c_lflag = 0;
  newtio.c_cc[VMIN] = 1;
  newtio.c_cc[VTIME] = 0;
  
  cfsetispeed(&newtio,BAUDRATE);
  cfsetospeed(&newtio,BAUDRATE);
  
  // flush the input buffer
  if (tcflush(fd_uart,TCIFLUSH)==-1) {
    return -1;
  }
  // flush the output buffer
  if (tcflush(fd_uart,TCOFLUSH)==-1) {
    return -1;
  }

  //-- Configure the serial port now!!
  if (tcsetattr(fd_uart,TCSANOW,&newtio)==-1){
    return -1;
  }
  return 0;
}
//cierra puerto serial
void UartClose()
{
  close(fd_uart);
}
//envia caracter
void SendByte(char c)
{
  write(fd_uart,&c,1);
}

//recibe caracter
unsigned char ReceiveByte(void){

  unsigned char c;
  read(fd_uart,&c,1);
  return(c);
}

int flush()
{
  // flush the input buffer
  if (tcflush(fd_uart,TCIFLUSH)==-1) {
    return -1;
  }
  // flush the output buffer
  if (tcflush(fd_uart,TCOFLUSH)==-1) {
    return -1;
  }

  return 0;
}