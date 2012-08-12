


#include "stdio.h"
#include "disp.h"

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

typedef struct
{
uchar *name;
ulong size;
ulong seg;
uchar offset;
uchar attribute;

ulong location;
FILE *file;
char block[256];
} open_file;

int disp_header(open_file file);
int disp_frame();
int disp_data();

main()
{
disp_open();

}

int disp_header(open_file file)
{
disp_move(20,5);
disp_printf("Name:%s",file.name);
disp_move(21,5);
disp_printf("Size:%lu",file.size);
disp_move(22,





}
