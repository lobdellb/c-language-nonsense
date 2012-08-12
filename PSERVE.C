
/* Include files */

#include "bios.h"
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "unsigned.h"

/* Constants */

#define INIT 0
#define SEND 1
#define RECV 2
#define STAT 3


#define SPEED 6
#define COMPORT 1
#define DATA 2
#define STOP 3
#define PARITY 4
#define WORK 5

/* Structures */

struct cfgdata {
	uchar uart;
	uint human;
	};


/* Global Variables */

struct cfgdata baud,stop,parity,data;
uchar comport;
uchar workdir[128];



/* Functions */

uint parse_config(void)
{
FILE *fp;
char buffer[256];
char *names[7];
char *scratch;
uchar var,loop;


names[SPEED]="BAUD";
names[COMPORT]="COMPORT";
names[DATA]="DATA";
names[STOP]="STOP";
names[PARITY]="PARITY";
names[WORK]="WORKDIR";



if ((fp=fopen("\\pserve.cfg","rt"))==NULL)
	{
	perror("Error opening file PSERVE.CFG");
	exit(1);
	};


do	{
	var=0;

	fscanf(fp,"%s",buffer);

	scratch =strupr(buffer);
	if ((strchr(scratch,61)!=NULL)&&(strchr(scratch,59)!=NULL))
		{
		scratch+=strspn(scratch," ");

		for(loop=1;loop<=6;loop++)
			if (strncmp(names[loop],scratch,strlen(names[loop]))==0)
				var=loop;

		scratch=strrchr(scratch,61);
		scratch+=1;
		scratch+=strspn(scratch," ");

		*(scratch+strcspn(scratch,";"))=0;
		*(scratch+strcspn(scratch," "))=0;
		switch (var)
			{
			case SPEED:
				{
				switch(atoi(scratch))
					{
					case 110:
						{
						baud.human=110;
						baud.uart=0x00;
						break;
						}
					case 150:
						{
						baud.human=150;
						baud.uart=0x20;
						break;
						}
					case 300:
						{
						baud.human=300;
						baud.uart=0x40;
						break;
						}
					case 600:
						{
						baud.human=600;
						baud.uart=0x60;
						break;
						}
					case 1200:
						{
						baud.human=1200;
						baud.uart=0x80;
						break;
						}
					case 2400:
						{
						baud.human=2400;
						baud.uart=0xA0;
						break;
						}
					case 4800:
						{
						baud.human=4800;
						baud.uart=0xC0;
						break;
						}
					case 9600:
						{
						baud.human=9600;
						baud.uart=0xE0;
						break;
						}
					default:
						{
						baud.human=9600;
						baud.uart=0xE0;
						break;
						}
					}
				break;
				}
			case COMPORT:
				{
				comport=atoi(scratch);
				break;
				}
			case DATA:
				{
				switch(atoi(scratch))
					{
					case 7:
						{
						data.human=7;
						data.uart=0x02;
						break;
						}
					case 8:
						{
						data.human=8;
						data.uart=0x03;
						break;
						}
					default:
						{
						data.human=8;
						data.uart=0x03;
						break;
						}
					}
				break;
				}
			case STOP:
				{
				switch(atoi(scratch))
					{
					case 1:
						{
						stop.human=1;
						stop.uart=0x00;
						break;
						}
					case 2:
						{
						stop.human=2;
						stop.uart=0x04;
						break;
						}
					default:
						{
						stop.human=1;
						stop.uart=0x00;
						break;
						}
					}
				break;
				}
			case PARITY:
				{
				switch(*scratch)
					{
					case 78:
						{
						parity.human=78;
						parity.uart=0x00;
						break;
						}
					case 79:
						{
						parity.human=79;
						parity.uart=0x08;
						break;
						}
					case 69:
						{
						parity.human=79;
						parity.uart=0x18;
						break;
						}
					default:
						{
						parity.human=78;
						parity.uart=0x00;
						break;
						}
					}
				break;
				}
			case WORK:
				{
				strcpy(workdir,scratch);
				break;
				}
			}
		}

	} while (!feof(fp));

fclose(fp);

return 0;
}


uint print_info(void)
{
puts("\n");
printf("BAUD RATE: %u		%x\n",baud.human,baud.uart);
printf("STOP BITS: %u		%x\n",stop.human,stop.uart);
printf("DATA BITS: %u		%x\n",data.human,data.uart);
printf("PARITY:	   %c		%x\n",(char)parity.human,parity.uart);
printf("COMPORT:   %u\n",comport);
printf("WORKDIR:   %s\n",workdir);

return 0;

}



#define initport bioscom(INIT,baud.uart|parity.uart|stop.uart|data.uart,comport)




main()
{

parse_config();
print_info();




}






/*  Format of the PSERVE.CFG file

line format:
	[parameter] [whitespace] [=] [whitespace] [value] [whitespace] [;] [comment information]


<BEGINING OF FILE>
baud=[BAUDRATE];
comport=[COMPORT];
data=[DATABITS];
parity=[PARITY];
stop=[STOPBITS];
workdir=[TEMPORARY STORAGE DIRECTORY];
<END OF FILE>

	no line can be longer than 256 characters


Valid Values for "baud="

110
150
300
600
1200
2400
4800
9600

B=66
C=67
D=68
P=80
S=83
W=87

*/