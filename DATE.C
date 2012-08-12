

#include "stdio.h"
#include "dos.h"


struct time
{
unsigned second		:5;
unsigned minut		:6;
unsigned hour		:5;
};

struct date
{
unsigned day		:5;
unsigned month		:4;
unsigned year		:7;
};

main()
{
struct time ftime;
struct date fdate;
struct find_t file;
unsigned *fdatex,*ftimex;
_dos_findfirst("ztc.com",63,&file);

fdatex=(unsigned *)&file.wr_date;
ftimex=(unsigned *)&file.wr_time;

*fdatex=file.wr_date;
*ftimex=file.wr_time;

printf("DATE: %u/%u/%u		TIME: %u:%u:%u",fdate.month,fdate.day,fdate.year,ftime.hour,ftime.minut,ftime.second);

}
