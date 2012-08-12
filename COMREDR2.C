


#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "unsigned.h"

#define BAUD(x) ((uint)(115200/x))
#define DATA_5 0
#define DATA_6 1
#define DATA_7 2
#define DATA_8 3
#define STOP_1 0
#define STOP_2 4
#define	PARITY_N 0
#define PARITY_O 8
#define PARITY_E 24
#define PARITY_M 40
#define PARITY_S 56
#define DLAB 128
#define BREAK 64

#define RS_INPUT 8
#define ERROR 4
#define SEND 2
#define RECV 1


#define DATA		0
#define INT_ENABLE	1
#define INT_IDENT	2
#define FIFO		2
#define LINE_CONTROL	3
#define MODEM_CONTROL	4
#define LINE_STATUS	5
#define MODEM_STATUS	6

#define LOOPBACK 16
#define	GP_OUT1 4
#define GP_OUT2 8
#define RTS 2
#define DTR 1




struct comport {
	uchar irq;
	uchar intr;
	uint port;
}

struct comport ports[2];

ports[0].intr=0x0c;
ports[1].intr=0x0b;
ports[0].port=0x3f8;
ports[1].port=0x2f8;



void com_init(void interrupt (*isr)(),uchar intno,uint portid,uint baud,uchar data,uchar stop,uchar parity)
{
uchar setbyte;

setbyte=DLAB;
outportb(portid+LINE_CONTROL,setbyte);
outport(portid+DATA,BAUD(baud));

setbyte=data+stop+parity;
outportb(portid+LINE_CONTROL,setbyte);

outportb(portid+INT_ENABLE,0);
outportb(portid+FIFO,0);
outportb(portid+MODEM_CONTROL,0)

setvect(intno,isr);

}

uint com_status(uint portid)
{
uint retval;

retval=inport(portid+LINE_STATUS);
return retval;
}



void interrupt handle_first_com()
{





}

void interrupt handle_second_com()
{





}



main()
{





}


