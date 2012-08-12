#include "math.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct {
byte character;
byte lenth;
byte code[2];
} bit_code;

typedef struct {
byte lenth;
byte code[2];
} short_bit_code;

typedef struct {
float probability;
byte character;
byte zero_one;
byte next;
} branch;

typedef struct {
float probability;
byte zero_one;
byte next;
} node;

typedef struct {
byte branch_used :2;
byte node_used   :2;
byte             :4;
} update;

byte Pow_two[8];
ulong bit_pointer=0;


byte pow_two[8]
pow_two[0]=128;
pow_two[1]=64;
pow_two[2]=32;
pow_two[3]=16;
pow_two[4]=8;
pow_two[5]=4;
pow_two[6]=2;
pow_two[7]=1;




#define setbit(x,y) (x=x|y)
#define toggle_bit(x,y) (x=x^y)
#define clear_bit(x,y) (x=x&~y)


#define byte unsigned char
#define ulong unsigned long

#define BLOCKSIZE 4096

#define handle_bit_io(buffer,bit_num) (*(buffer+(int)(bit_num/8))+=pow_two[bit_num%8])
#define load_file_seg(buffer,size,file) fread(buffer,size,1,file)
#define write_file_seg(buffer,size,file) fwrite(buffer,size,1,file)
#define open_in_file() fopen("test.txt","rb")
#define open_out_file() fopen("output.txt","wb")


ulong *analyse(FILE *infile);
branch *sort(ulong *frequency,ulong file_lenth);
int fcmp(float *val1,float *val2);
void assign_nodes(branch *branches,ulong file_lenth);
update lowest_two(branch *branches,node *nodes,int *lowest,byte lowest_branch,byte lowest_node);
void scan_lowest(branch *branches,node *nodes,byte *lowest_branch,byte *lowest_node,byte node_used,byte node_full,byte branch_used);
int make_node(int *lowest,branch *branches,node *nodes,byte node_full);
bit_code *trace(branch *branches,node *nodes);
void do_branch(branch *branches,node *nodes,ulong loop,bit_code *bitcodes);
void do_node(node *nodes,bit_code *bitcodes,byte next,byte current_bit);
void handle_mem(branch *branches,node *nodes,ulong *frequency);
void compress(bit_code *bit_codes,FILE *infile,FILE *outfile);



main()
{
bit_code *bitcodes;
branch *branches;
node *nodes;
ulong *frequecy;
FILE *infile,*outfile;
ulong file_lenth;
infile=open_in_file;
outfile=open_out_file;
file_lenth=filesize("test.txt");
frequency=analyse(infile);
branches=sort(frequency,file_lenth);
nodes=assign_nodes(branches,file_lenth)
bit_codes=trace(branches,nodes);
handle_mem(branches,nodes,frequency);





compress(bit_codes,infile,outfile)
}

void write_header(FILE *outfile,bit_code *bit_codes)
{
ulong loop;
short_bit_code buffer[256];
for (loop=0;loop<=768;loop++)
{
buffer[loop].lenth=*(bit_codes+loop).lenth;
buffer[loop].code[1]=*(bit_codes+loop).code[1];
buffer[loop].code[2]=*(bit_codes+loop).code[2];
}
free(bit_codes);


}

void set_buffer(byte *buffer,ulong lenth)
{
ulong loop;
for (loop=0;loop<=lenth;loop++)
*(buffer+loop)=0;
}







#define handle_bit_io(buffer,bit_num,bit) (*(buffer+(int)(bit_num/8))+=bit*pow_two[bit_num%8])










void compress(bit_code *bit_codes,FILE *infile,FILE *outfile)
{
void *in_buffer;
void *out_buffer;




}



void handle_mem(branch *branches,node *nodes,ulong *frequency)
{
free(frequency);
free(branches);
free(nodes);
}

ulong *analyse(FILE *infile)
{
ulong *frequency;
frequency=calloc(256,4);
do
{
*(frequency+getch(infile))++;
while (!feof(infile));
return frequency;
}

branch *sort(ulong *frequency,ulong file_lenth)
{
ulong loop;
branch *branches;
branches=calloc(256,7);
for (loop=0;loop<=256;loop++)
{
*(branches+loop).probability=*(frequency)/file_lenth;
*(branches+loop).character=loop;
}
qsort(branches,256,7,fcmp);
return branches;
}

int fcmp(float *val1,float *val2)
{
int out_val;
if (*val1<*val2)
out_val=-1;
else if (*val1==*val2)
out_val=0;
else
out_val=1;
return out_val;
}

int fcmp_2(byte *val1,byte *val2)
{
int out_val;
if (*val1<*val2)
out_val=-1;
else if (*val1==*val2)
out_val=0;
else
out_val=1;
return out_val;
}
void assign_nodes(branch *branches,ulong file_lenth)
{
node *nodes;
nodes=calloc(256,6);
int flag;
ulong loop;
byte node_used=0,node_full=0,branch_used=0;
int lowest[2];
byte lowest_branch,lowest_node;
update up_date;

for(loop=0;loop<=255;loop++)
*(nodes+loop).probability=1;

do
{
scan_lowest(branches,nodes,&lowest_branch,&lowest_node,node_used,node_full,branch_used);
up_date=lowest_two(branches,nodes,lowest,lowest_branch,lowest_node);
flag=make_node(lowest,branches,nodes,node_full);
node_full++
nodes_used+=update.nodes_used;
branches_used=update.branches_used;

} while (!flag);
return nodes;
}

int make_node(int *lowest,branch *branches,node *nodes,byte node_full)
{
float prob_1,prob_2;

if (*(lowest)>=256)
{
prob_1=*(nodes+*(lowest)-256).probability;
*(nodes+*(lowest)-256).zero_one=0;
*(nodes+*(lowest)-256).next=node_full;
}
else
{
prob_1=*(branches+*(lowest)).probability;
*(branches+*(lowest)).zero_one=0
*(branches+*(lowest)).next=node_full;
}

if (*(lowest+1)>=256)
{
prob_2=*(nodes+*(lowest+1)-256).probability;
*(nodes+*(lowest+1)-256).zero_one=1;
*(nodes+*(lowest+1)-256).next=node_full;
}
else
{
prob_2=*(branches+*(lowest+1)).probability;
*(branches+*(lowest+1)-256).zero_one=1;
*(branches+*(lowest+1)-256).next=node_full;
}

*(nodes+node_full).probability=prob_1+prob_2;

if (*(nodes+node_full).probabilty>=1)
return 1;
else
return 0;
}

void scan_lowest(branch *branches,node *nodes,byte *lowest_branch,byte *lowest_node,byte node_used,byte node_full,byte branch_used)
{
for(loop=branch_used;loop<=255;loop++)
{
if (*(branches+loop).probability<*(branches+lowest_branch).probability)
lowest_branch=loop;
}

for(loop=node_used;loop<=node_full;loop++)
{
if (*(nodes+loop).probability<*(nodes+lowest_node).probability)
lowest_node=loop;
}
}

update lowest_two(branch *branches,node *nodes,int *lowest,byte lowest_branch,byte lowest_node)
{
update output;
if(*(branches+lowest_branch+1)<*(nodes+lowest_node))
{
*(lowest)=lowest_branch;
*(lowest+1)=lowest_branch+1;
output.nodes_used=2;
}
else if (*(nodes+lowest_node+1)<*(branches+lowest_branch))
{
*(lowest)=lowest_node+256;
*(lowest+1)=lowest_node+257;
output.branches_used=2;
}
else
{
output.nodes_used=1;
output.branches_used=1;
if (*(nodes+lowest_node)<*(branches+lowest_branch))
{
*(lowest)=lowest_node+256;
*(lowest+1)=lowest_branch;
}
else
{
*(lowest)=lowest_branch;
*(lowest+1)=lowest_node+256;
}
}

bit_code *trace(branch *branches,node *nodes)
{
byte flag;
bit_code *bit_codes;
bit_codes=calloc(256,3);
ulong loop;
for (loop=0;loop<=255;loop++)
{
current_bit=0;
*(bit_codes+loop).character=*(branches+loop).character;
do_branch(branches,nodes,loop,bit_codes);
do_node(nodes,bit_codes+loop,*(branches+loop).next,0);
qsort(bit_codes,256,4,fcmp_2);
}

void do_branch(branch *branches,node *nodes,ulong loop,bit_code *bit_codes)
{
if (*(branches+loop).zero_one==1)
set_bit(*(bit_codes+loop).code[(int)floor(*current_bit/8)],2^(*current_bit%8));
else
clear_bit(*(bit_codes+loop).code[(int)floor(*current_bit/8)],2^(*current_bit%8));
*current_bit++;
}

void do_node(node *nodes,bit_code *bit_codes,byte next,byte current_bit)
{
if (*(nodes+next).probability<1)
do_node(nodes,bit_codes,*(nodes+next).next,current_bit++);

if (*(nodes+next).zero_one==1)
set_bit(*(bit_codes).code[(int)floor(current_bit/8)],2^(current_bit%8));
else
clear_bit(*(bit_codes+loop).code[(int)floor(current_bit/8)],2^(current_bit%8));
*(bit_codes).lenth=current_bit;
}


