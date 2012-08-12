/*

    $Id: common.c,v 1.10 1996/06/04 15:36:38 thoth Exp $, part of
    faucet and hose: network pipe utilities
    Copyright (C) 1992-95 Robert Forsman

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    */

#include	<stdio.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<errno.h>
#include	<unistd.h>
#include	<sys/socket.h>
#include	<sys/un.h>
#include	<netdb.h>
#include	<netinet/in.h>
#include "common.h"

char *programname;

/**********************************************************************/

int	*fds=0;
int	nfds;
int	fdsize=0;

int how_shutdown = -2;

void add_fd(fd)
    int	fd;
{
    if (fds==0) {
	fds = (int*)malloc(sizeof(*fds)*(fdsize=4));
    } else if (nfds >= fdsize) {
	fds = (int*)realloc(fds, sizeof(*fds)*(fdsize*=2));
	if (fds==0) {
	    fprintf(stderr, "%s: Out of memory\n", programname);
	    exit(1);
	}
    }
    fds[nfds++] = fd;
    if (fd>2)
	/* We should reserve this spot in the file descriptor table.
	 If we don't it could get allocated by the socket(2) call and
	 we would have an awful mess on our hands. */
	dup2(0, fd);
}

void dup_n(socket)
    int	socket;
{
    int	i;
#if 0
    printf("I will redirect fds");
    for (i=0; i<nfds; i++) {
	printf(" %d", fds[i]);
    }
    printf(" and shutdown with %d\n", how_shutdown);
#endif
    if (how_shutdown>=0)
	shutdown(socket, how_shutdown!=0);
    for (i=0; i<nfds; i++) {
	dup2(socket, fds[i]);
    }
}

/**********************************************************************/

int name_to_inet_port(portname)
char *portname;
/* This procedure converts a character string to a port number.  It looks
   up the service by name and if there is none, then it converts the string
   to a number with sscanf */
{
  struct servent	*p;

  if (portname==NULL)
    return 0;

  p = getservbyname(portname,"tcp");
  if (p!=NULL)
    {
      return p->s_port;
    }
  else
    {
      int	port;
      if (sscanf(portname,"%i",&port)!=1)
	{
	  return 0;
	}
      else
	return htons(port);
    }
}

struct in_addr ** /* addr_array */
convert_hostname(name, count_ret)
    char	*name;
    int		*count_ret;
{
  struct hostent	*hp;
  int		len;
  struct in_addr	**rval;

  hp = gethostbyname(name);
  if (hp != NULL) {
    int	i;
    if (hp->h_length != sizeof(struct in_addr)) {
	fprintf(stderr, "%s: Funky: (hp->h_length = %d) != (sizeof(struct in_addr) = %ld)\n", programname, hp->h_length, (long) sizeof(struct in_addr));
    }
    for (i = 0; hp->h_addr_list[i]; i++)
	{ }
    *count_ret = i;
    rval = (struct in_addr **)malloc(sizeof(*rval) * (i+1));
    for (i=0; i<*count_ret; i++) {
	rval[i] = (struct in_addr*)malloc(hp->h_length);
	memcpy((char*)rval[i], hp->h_addr_list[i], hp->h_length);
    }
    rval[*count_ret] = 0;
    return rval;
  } else {
      int	count;
      unsigned int	a1,a2,a3,a4;
      count = sscanf(name,"%i.%i.%i.%i%n", &a1, &a2, &a3, &a4, &len);
      if (4!=count || 0!=name[len] )
	return 0;

      *count_ret = 1;
      rval = (struct in_addr**)malloc(2*sizeof(*rval));
      rval[0] = (struct in_addr*)malloc(sizeof(struct in_addr));
      rval[0]->s_addr = (((((a1 << 8) | a2) << 8) | a3) << 8) | a4;
      rval[1] = 0;
      return rval;
  }
}


int
bindlocal(fd, name, addrname, domain)
     int	fd, domain;
     char	*name, *addrname;
{
  struct sockaddr	*laddr;
  int	addrlen;
  int	countdown;
  int	rval;
  
  if (domain==AF_INET)
    {
      static struct sockaddr_in	srv;
      static int	initted=0;

      laddr = (struct sockaddr*)&srv;
      addrlen = sizeof(srv);

      if (!initted) {
	srv.sin_family = AF_INET;

	if (addrname) {
	    int	count;
	    struct in_addr **addresses;
	    addresses = convert_hostname(addrname, &count);
	    if (addresses == 0) {
		fprintf(stderr, "%s: Unable to convert %s to an internet address\n", programname, addrname);
		errno=0;
		return 0;
	    }
	    srv.sin_addr = *(addresses[0]);
	} else {
	    srv.sin_addr.s_addr = INADDR_ANY;
	}
	
	srv.sin_port = name_to_inet_port(name);
      
	if (srv.sin_port==0)
	  {
	    fprintf(stderr, "%s: port %s unknown\n", programname, name);
	    errno = 0;
	    return 0;
	  }
      }
      initted = 1;		/* bindlocal is only called once in
				   each netpipes program */
    }
  else
    {
      static struct sockaddr_un	srv;
      laddr = (struct sockaddr*)&srv;
      addrlen = sizeof(srv);
      
      srv.sun_family = AF_UNIX;
      strcpy(srv.sun_path, name);
    }
  
  countdown= (domain==AF_UNIX)?1:10;
  do {
    rval = bind(fd, laddr, addrlen);
    if (rval)
      if (errno==EADDRINUSE && --countdown>0)
	{
	  fprintf(stderr,"%s: Address %s in use, sleeping 10.\n",
		  programname, name);
	  sleep (10);
	  fprintf(stderr,"%s: Trying again . . .\n", programname);
	}
      else
	return 0;
  } while (rval);

  return 1;
}
