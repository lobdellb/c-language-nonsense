/* CRYPT.C */
/* 5/9/95 */
/* Bryce Lobdell */


#include "stdio.h"
#include "stdlib.h"
#include "dos.h"
#include "string.h"
#include "io.h"

#define byte unsigned char
#define ulong unsigned long
#define NUL 0

#define load_file_seg(infile,buffer,size) fread(buffer,size,1,infile);
#define write_file_seg(outfile,buffer,size) fwrite(buffer,size,1,outfile);

void get_file_names(char **infile,char **outfile,int *ed,int numargs,char *args[],char **password);
void load_key_set(FILE *keyfile,byte *buffer,byte set_num);
void substitute(byte *buffer,byte *key_buffer,ulong lenth);
void shift(byte *buffer,byte *key_buffer,ulong lenth,int ed);
void crypt(byte *buffer,byte *key_buffer,int lenth,FILE *infile,FILE *outfile,FILE *keyfile,FILE *keyfile2,char *password,int ed,int seg_size);
ulong file_lenth(FILE *filename);
void crypt_set(byte *buffer,int shift_sub,byte *key_buffer,int ed,ulong seglenth);
void select_key(int odd_even,char password,byte *buffer,int ed,FILE *keyfile,FILE *keyfile2);
void full_file(FILE *infile,FILE *outfile,FILE *keyfile,FILE *keyfile2,char *password,int ed,ulong filelenth,int lenth);
void help(void);

main(int numargs,char *args[])
{
char *k1="key.fil",*k2="dekey.fil";
ulong flenth;
int ed,lenth;
char *password;
FILE *infilex,*outfilex,*keyx,*keyx2;
char *infile,*outfile,*key;
get_file_names(&infile,&outfile,&ed,numargs,args,&password);
if (ed==1)
key=k2;
else
key=k1;
infilex=fopen(infile,"rb");
if (infilex==NUL)
{
fprintf(stderr,"Unable to open input file!\n");
exit(2);
}
outfilex=fopen(outfile,"wb");
if (outfilex==NUL)
{
fprintf(stderr,"Unable to creat output file!\n");
exit(3);
}
keyx=fopen(key,"rb");
if (keyx==NUL)
{
fprintf(stderr,"Unable to open the key file!\n");
exit(3);
}
lenth=strlen(password);
if (ed==1)
{
keyx2=fopen("key.fil","rb");
if (keyx2==NUL)
{
fprintf(stderr,"Unable to open the key file!\n");
exit(3);
}
password=strrev(password);
}
flenth=file_lenth(infilex);
if (keyx==0)
exit(0);
full_file(infilex,outfilex,keyx,keyx2,password,ed,flenth,lenth);
fcloseall();
return 0;
}


void get_file_names(char **infile,char **outfile,int *ed,int numargs,char *args[],char **password)
{
int toggle;
if (strcmp(args[1],"/?")==0)
help();
if (numargs!=5)
{
fprintf(stderr,"Wrong number of arguments!\n");
exit(4);
}
*infile=args[1];
*outfile=args[2];
*password=args[3];
toggle=*args[4];
if ((toggle==68)||(toggle==100))
*ed=1;
else if ((toggle==69)||(toggle==101))
*ed=0;
else
{
fprintf(stderr,"Incorrect value for \"ed\"!\n");
exit(6);
}
}



int get_password(char *password)
{
size_t lenth;
printf("\nEnter your password:");
scanf("%s",password);
lenth=strlen(password);
return lenth;
}


void load_key_set(FILE *keyfile,byte *buffer,byte set_num)
{
int loop;
long offset=set_num*256;
fseek(keyfile,offset,0);  
fread(buffer,256,1,keyfile);
}

void substitute(byte *buffer,byte *key_buffer,ulong lenth)
{
long loop;
for (loop=0;loop<=lenth;++loop)
*(buffer+loop)=*(key_buffer+*(buffer+loop));
}


void shift(byte *buffer,byte *key_buffer,ulong lenth,int ed)
{
int loop;
if (ed==0)
{
for (loop=0;loop<=lenth;++loop)
*(buffer+loop)+=*(key_buffer+(loop%256));
}
else
{
for (loop=0;loop<=lenth;loop++)
*(buffer+loop)-=*(key_buffer+(loop%256));
}
}

void full_file(FILE *infile,FILE *outfile,FILE *keyfile,FILE *keyfile2,char *password,int ed,ulong filelenth,int lenth)
{
ulong loop;
byte *buffer,*key_buffer;
buffer=malloc(4096);
key_buffer=malloc(256);
if (key_buffer==NUL ||buffer==NUL)
{
fprintf(stderr,"Unable to allocate memory!\n");
exit(1);
}
for (loop=4096;loop<=filelenth;loop+=4096)
{
crypt(buffer,key_buffer,lenth,infile,outfile,keyfile,keyfile2,password,ed,4096);
}
crypt(buffer,key_buffer,lenth,infile,outfile,keyfile,keyfile2,password,ed,filelenth%4096);
}


void crypt(byte *buffer,byte *key_buffer,int lenth,FILE *infile,FILE *outfile,FILE *keyfile,FILE *keyfile2,char *password,int ed,int seg_size)
{
int loop;
int odd_even;
load_file_seg(infile,buffer,seg_size);
for (loop=0;loop<=lenth-1;loop++)
{
if (ed&&((strlen(password)%2)==0))
odd_even=(loop+1)%2;
else
odd_even=loop%2;
select_key(odd_even,*(password+loop),key_buffer,ed,keyfile, keyfile2);
crypt_set(buffer,odd_even,key_buffer,ed,seg_size);
}
write_file_seg(outfile,buffer,seg_size);
}

void crypt_set(byte *buffer,int shift_sub,byte *key_buffer,int ed,ulong seglenth)
{
int loop;
int oddeven;
if (shift_sub==0)
substitute(buffer,key_buffer,seglenth);
else
shift(buffer,key_buffer,seglenth,ed);
}

void select_key(int odd_even,char password,byte *buffer,int ed,FILE *keyfile,FILE *keyfile2)
{
if (ed==1)
{
if (odd_even==0)
load_key_set(keyfile,buffer,password);
else
load_key_set(keyfile2,buffer,password);
}
else
load_key_set(keyfile,buffer,password);
}


ulong file_lenth(FILE *filename)
{
ulong lenth;
lenth=filelength(fileno(filename));
return lenth;
}

void help(void)
{
printf("\n");
printf("Usage:\n");
printf("\n");
printf("CRYPT infile outfile password ed\n");
printf("\n");
printf("infile:  This is the file that  the opperation\n");
printf("specified by \"ed\" is done to\n");
printf("\n");
printf("outfile:  This is the result of the opperation\n");
printf("specified by \"ed.\"\n");
printf("\n");
printf("password:  If you are encrypting, you specify\n");
printf("this as your password.  I you're decrypting\n");
printf("this is the password you put in when you\n");
printf("were encrypting the file.\n");
printf("\n");
printf("ed:  This tells CRYPT weather to encrypt or\n");
printf("decrypt.  E or e causes it to encrypt a file.\n");
printf("D or d causes it to decrypt a file.\n");
printf("\n");
exit(5);
}