/*
** irc.h for header in /home/durand_u/github/Myirc
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Mon Apr  6 12:39:14 2015 Rémi DURAND
** Last update Mon Apr  6 12:52:58 2015 Rémi DURAND
*/

#ifndef _IRC_H_
# define _IRC_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/sendfile.h>
# include <fcntl.h>
# include <netdb.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <dirent.h>

# define NB_QUE 7

typedef const struct sockaddr *	caddr_c;
typedef struct sockaddr *	addr_c;

int		init_serv(struct protoent **pe, char **av,
			  struct sockaddr_in *s_in);

#endif /* !_IRC_H_ */
