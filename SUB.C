




#include "stdio.h"
#include "disp.h"
#include "unsigned.h"

void drawbox(uchar x,uchar y,uchar length,uchar width);

main()
{
disp_open();

drawbox(10,10,10,10);

disp_close();


}


void drawbox(uchar x,uchar y,uchar length,uchar width)
{
uint loop;
disp_move(y,x);

disp_putc(201);

for(loop=0;loop<=(width-3);loop++)
disp_putc(205);

disp_putc(187);

for(loop=y+1;loop<=(length+y-1);loop++)
{
disp_move(loop,x+width-1);
disp_putc(186);
}

disp_move(loop,x+width-2)
disp_putc(188);

for(loop=(x+width);loop>=x+1;loop--)
{
disp_move(y+length,loop);
disp_putc(205);
}


disp_putc(200);

for(loop=(y+length);loop>=y+1;loop--)
{
disp_move(loop,x);
disp_putc(186);
}


} 
