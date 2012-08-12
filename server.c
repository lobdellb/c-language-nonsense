/*  This is just a simple program to test and demonstrate
the usage of unix sockets and ip networking.

Author:  Bryce Lobdell
Filename:  client.c
Date:  4/24/99

*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>

#define uchar unsigned char
#define ushort usigned short
#define uint unsigned int


#define HEREPORT 4002
#define THEREPORT 4000
#define LOCALIP "128.210.202.150"
#define REMOTEIP "128.210.195.36"


struct ipaddr_b
   {
   int a,b,c,d;
   };



int main()
{
struct in_addr here_ip,there_ip;
struct ipaddr_b ip;
int sock, retval, newsock, size;
struct sockaddr_in here_addr, there_addr;
char input;

sscanf(REMOTEIP,"%i.%i.%i.%i",&ip.a,&ip.b,&ip.c,&ip.d); 
there_ip.s_addr = ip.a + (ip.b << 8) + (ip.c << 16) + (ip.d << 24);

sscanf(LOCALIP,"%i.%i.%i.%i",&ip.a,&ip.b,&ip.c,&ip.d);
here_ip.s_addr = ip.a + (ip.b << 8) + (ip.c << 16) + (ip.d << 24);


there_addr.sin_port = THEREPORT;
here_addr.sin_port = HEREPORT;
there_addr.sin_family = AF_INET;
here_addr.sin_family = AF_INET;
there_addr.sin_addr = there_ip;
here_addr.sin_addr = here_ip;



sock = socket(AF_INET, SOCK_STREAM, 0);


retval = bind(sock, (struct sockaddr *)&here_addr, sizeof(struct sockaddr_in));

if (retval != 0)
   {
   printf("Something went wrong.\n");
   exit(0);
   }

/*  
retval = connect(sock,(struct sockaddr *)&there_addr,
                             sizeof(struct sockaddr_in));
*/

listen(sock,4);


newsock = accept(sock,(struct sockaddr *)&there_addr,&size);

   {
   fd_set stuff;

   FD_ZERO(&stuff);
   FD_SET(newsock,&stuff);

   input = 0;
   printf("Client Aquired...\n");
   while (input != '*') 
      {
      
      select(newsock+1,&stuff,NULL,NULL,NULL); 

      while (read(newsock,&input,1) != 0)
         printf("%c",input);

      }


   }

close(sock);
close(newsock);


   


return 0;
}
