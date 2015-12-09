#if !defined (_SERIAL_H_)
#define _SERIAL_H_

int fd_uart;
#define XBEE_DEV "/dev/ttyO1"
#define BAUDRATE B9600

int UartInit();
void UartClose();
void SendByte(char c);
unsigned char ReceiveByte(void);
int flush();

#endif
