/*
** irc.h for header in /home/durand_u/github/Myirc
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Mon Apr  6 12:39:14 2015 Rémi DURAND
** Last update Thu Apr  9 14:11:02 2015 Rémi DURAND
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

# define NB_QUE 512
# define FD_FREE 0
# define FD_CLIENT 1
# define FD_SERVER 2

typedef const struct sockaddr *	caddr_c;
typedef struct sockaddr *	addr_c;
typedef				void(*fct)();

typedef struct	s_cfds
{
  char		fd_type[NB_QUE];
  fct		fct_read[NB_QUE];
  fct		fct_write[NB_QUE];
  char		*nicks[NB_QUE];
  int		port;
  fd_set	fd_r;
  fd_set	fd_w;
  int		ncfd;
}		t_cfds;

int		init_serv(struct protoent **pe, char **av,
			  struct sockaddr_in *s_in);
int		init_cli(t_cfds *cdata);
void		server_read(t_cfds *cdata, int fd, fd_set *set);
void		server_write(t_cfds *cdata, int fd, fd_set writefds);
void		handle_cmds(t_cfds *e, char **cmd, int fd);
char		**my_str_to_wordtab(char *str);

#endif /* !_IRC_H_ */
