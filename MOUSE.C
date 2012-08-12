

#include "stdio.h"
#include "disp.h"
#include "msmouse.h"


void mouse_handler(unsigned w,unsigned x,unsigned y,unsigned z);
/*void (*mouse_handler_ptr)(unsigned w,unsigned x,unsigned y,unsigned z);*/

/*mouse_handler_ptr=mouse_handler;*/

main()
{
unsigned char far *cls;
unsigned int x,y,z;
int loop;

system("cls");
disp_open();
msm_init();
/*msm_setareax(0,80);
msm_setareay(0,25);*/

msm_showcursor();
disp_setattr(4);

msm_signal(31,mouse_handler,(void *)0);

do
{
} while(1);

}


void mouse_handler(unsigned w,unsigned x,unsigned y,unsigned z)
{
disp_setattr(4);
disp_move(1,1);
disp_printf("%u\n%u\n%u\n%u",w,x,y,z);
}

