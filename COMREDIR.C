


#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "dos.h"


/* Constants */


#define uchar char
#define uint unsigned int
#define ulong unsigned long


#define BAUD(x)	((uint)(115200/x))
#define DATA_5		0
#define DATA_6		1
#define DATA_7		2
#define DATA_8		3
#define STOP_1		0
#define STOP_2		4
#define PARITY_N	0
#define PARITY_O	8
#define PARITY_E	24
#define PARITY_M	40
#define PARITY_S	56
#define DLAB		128
#define BREAK		64


#define EN_RS_INPUT 8
#define EN_ERROR 4
#define EN_SEND 2
#define EN_RECV 1

#define ID_RS_INPUT 0
#define ID_ERROR 6
#define ID_SEND 2
#define ID_RECV 4

#define DATA		0
#define INT_ENABLE	1
#define INT_IDENT	2
#define FIFO		2
#define LINE_CONTROL	3
#define MODEM_CONTROL	4
#define LINE_STATUS	5
#define MODEM_STATUS	6

#define LOOPBACK 16
#define GP_OUT1 4
#define GP_OUT2 8
#define RTS 2
#define DTR 1


#define BUFFERSIZE 2048

#define PORTIN (*ports[portnum].inbuffer)
#define PORTOUT (*ports[portnum].outbuffer)
#define PORTSTATUS (*ports[portnum].status)


/* Structures */


struct circle_buff {
	uchar *buffer;
	uint in;
	uint out;
	uint diff;
};

struct com_status {
	uchar enabled_ints;
	uchar modem_control;
	uchar line_stat;
	uchar modem_stat;
};

struct comport {
	uchar irq;
	uchar intr;
	uint port;
	struct com_status *status;
	struct circle_buff *inbuffer;
	struct circle_buff *outbuffer;
};




/* Global Variables */

struct comport ports[2];
struct circle_buff buffer[2];



/* Functions */


void com_init(uchar portnum,uint baud,uchar data,uchar stop,uchar parity,void interrupt (*isr)())
{
uchar setbyte;

outportb(ports[portnum].port+INT_ENABLE,0);			/* turn port "off" */
outportb(ports[portnum].port+FIFO,0);
outportb(ports[portnum].port+MODEM_CONTROL,0);

setbyte=DLAB;					/* enable baud rate bytes */
outportb(ports[portnum].port+LINE_CONTROL,setbyte);
outport(ports[portnum].port+DATA,BAUD(baud));

setbyte=data+stop+parity;			/* set line for 8N1 */
outportb(ports[portnum].port+LINE_CONTROL,setbyte);


setvect(ports[portnum].intr,isr);				/* put handle routine into modems IRQ */

setbyte=RTS+DTR+GP_OUT2;			/* Enable RTS,DTR and General Purpose output #2 */
outportb(ports[portnum].port+MODEM_CONTROL,setbyte);

setbyte=EN_RECV+EN_SEND;	/* Enable interrupts */
outportb(ports[portnum].port+INT_ENABLE,setbyte);


}



struct com_status *getcom_status(uchar portnum)
{
struct com_status status;

status.enabled_ints=inportb(ports[portnum].port+INT_ENABLE);
status.modem_control=inportb(ports[portnum].port+MODEM_CONTROL);
status.line_stat=inportb(ports[portnum].port+LINE_STATUS);
status.modem_stat=inportb(ports[portnum].port+MODEM_STATUS);

return &status;
}



void rs_error(uchar portnum)
{}

void rs_input(uchar portnum)
{}


void receive_data(uchar portnum)
{

*(PORTIN.buffer+PORTIN.in)=inportb(ports[portnum].port+DATA);

printf("%c",*(PORTIN.buffer+PORTIN.in));

PORTIN.in+=1;
PORTIN.diff+=1;
if (PORTIN.in=BUFFERSIZE)
	PORTIN.in=0;


/*if (PORTIN.diff>=BUFFERSIZE)
	{
	ports[portnum].status.modem_control=(ports[portnum].status.modem_control)^RTS;
	outportb(ports[portnum].port+MODEM_CONTROL,ports[portnum].status.modem_control);
	}*/

}



void send_data(uchar portnum)
{
if (PORTOUT.diff>0)
	outportb(ports[portnum].port+DATA,*(PORTOUT.buffer+PORTOUT.out));
PORTOUT.in+=1;
PORTOUT.diff-=1;
if (PORTOUT.in=BUFFERSIZE)
	PORTOUT.in=0;


/*if (PORTOUT.diff>=BUFFERSIZE)
	{
	ports[portnum].status.modem_control=(ports[portnum].status.modem_control)^RTS;
	outportb(ports[portnum].port+MODEM_CONTROL,ports[portnum].status.modem_control);
	}*/

}



void interrupt handle_first_com()
{
uchar getbyte,setbyte;

disable();			/* Disable all interrupts */

getbyte=inport(ports[0].port+INT_IDENT);

switch (getbyte)
	{
	case ID_RECV:
		receive_data(0);
	case ID_SEND:
		send_data(0);
	case ID_RS_INPUT:
		rs_input(0);
	case ID_ERROR:
		rs_error(0);
	}

enable();			/* Enable all interrupts */

}


void interrupt handle_second_com()
{
uchar getbyte,setbyte;

disable();			/* Disable all interrupts */

getbyte=inport(ports[1].port+INT_IDENT);

switch (getbyte)
	{
	case ID_RECV:
		receive_data(1);
	case ID_SEND:
		send_data(1);
	case ID_RS_INPUT:
		rs_input(1);
	case ID_ERROR:
		rs_error(1);
	}

enable();			/* Enable all interrupts */

}





void initialize_data()
{

/* Set up port Parameters */
ports[0].intr=0x0c;		/* IRQ 4 */
ports[1].intr=0x0b;		/* IRQ 3 */
ports[0].port=0x3f8;		/* COM1 */
ports[1].port=0x2f8;		/* COM3 */

ports[0].inbuffer=&buffer[0];	   /* Assign Buffers */
ports[0].outbuffer=&buffer[1];
ports[1].inbuffer=&buffer[1];
ports[1].outbuffer=&buffer[0];

buffer[0].buffer=malloc(BUFFERSIZE);
buffer[1].buffer=malloc(BUFFERSIZE);

buffer[0].in=0;
buffer[1].in=0;
buffer[0].out=0;
buffer[1].out=0;
buffer[0].diff=0;
buffer[1].diff=0;

}



main()
{

initialize_data();
com_init(0,115200,DATA_8,STOP_1,PARITY_N,&handle_first_com);
com_init(1,115200,DATA_8,STOP_1,PARITY_N,&handle_second_com);

ports[0].status=getcom_status(0);
ports[1].status=getcom_status(1);

while (1){}

}


