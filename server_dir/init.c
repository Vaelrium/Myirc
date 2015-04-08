/*
** init.c for init in /home/durand_u/github/Myirc
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Mon Apr  6 12:43:25 2015 Rémi DURAND
** Last update Wed Apr  8 13:51:32 2015 Rémi DURAND
*/

#include "irc.h"

int		init_serv(struct protoent **pe, char **av,
			  struct sockaddr_in *s_in)
{
  *pe = getprotobyname("TCP");
  if (!*pe)
    return (-1);
  s_in->sin_family = AF_INET;
  s_in->sin_port = htons(atoi(av[1]));
  s_in->sin_addr.s_addr = INADDR_ANY;
  return (0);
}


void		client_read(t_cfds *e, int fd, fd_set *set)
{
  int		r;
  char		buf[4096];
  int		i;

  r = read(fd, buf, 4096);
  if (r > 0)
    {
      buf[r] = '\0';
      printf("%d: %s\n", fd, buf);
      i = 0;
      while (i < NB_QUE)
	{
	  if (FD_ISSET(i, set) && i != fd)
	    write(i, buf, r);
	  ++i;
	}
    }
  else
    {
      printf("%d: Connection closed\n", fd);
      close(fd);
      e->fd_type[fd] = FD_FREE;
    }
}

void		client_write(t_cfds *e, int fd, fd_set *writefds)
{
  int		r;
  char		buf[4096];
  int		i;

  r = read(fd, buf, 4096);
  if (r > 0)
    {
      buf[r] = '\0';
      printf("%d: %s\n", fd, buf);
      i = 0;
      while (i < NB_QUE)
      	 {
      	   if (FD_ISSET(i, writefds) && i != fd)
      	     {
      	       printf("write on %d\n", i);
      	       write(fd, buf, r);
      	     }
	   ++i;
      	 }
    }
  else
    {
      printf("%d: Connection closed\n", fd);
      close(fd);
      e->fd_type[fd] = FD_FREE;
    }
}

void			add_client(t_cfds *cdata, int s)
{
  int			cs;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;
  char			*cip;

  client_sin_len = sizeof(client_sin);
  cs = accept(s, (addr_c)&client_sin, &client_sin_len);
  if ((cip = inet_ntoa(client_sin.sin_addr)) == NULL)
    return ;
  printf("%s\n", cip);
  cdata->fd_type[cs] = FD_CLIENT;
  cdata->fct_read[cs] = client_read;
  cdata->fct_write[cs] = client_write;
}

void		server_read(t_cfds *cdata, int fd, fd_set *set)
{
  printf("New client\n");
  add_client(cdata, fd);
  (void)set;
}

void		server_write(t_cfds *cdata, int fd, fd_set writefds)
{
  (void)cdata;
  (void)fd;
  (void)writefds;
}

void			init_set(t_cfds *cdata)
{
  int			v;
  struct timeval	tv;

  v = 0;
  tv.tv_sec = 20;
  tv.tv_usec = 0;
  memset(cdata->fd_type, FD_FREE, NB_QUE);
  while (v < NB_QUE)
    {
      if (cdata->fd_type[v] != FD_FREE)
	{
	  FD_SET(v, &cdata->fd_r);
	  FD_SET(v, &cdata->fd_w);
	  cdata->ncfd = v;
	}
      ++v;
    }
  if (select(cdata->ncfd + 1, &cdata->fd_r, &cdata->fd_w, NULL, &tv) == -1)
    perror("select");
}

int		init_cli(t_cfds *cdata)
{
  int		v;

  v = 0;
  FD_ZERO(&cdata->fd_r);
  FD_ZERO(&cdata->fd_w);
  cdata->ncfd = 0;
  init_set(cdata);
  while (v < NB_QUE)
    {
      if (FD_ISSET(v, &cdata->fd_r))
	cdata->fct_read[v](&cdata, v, &cdata->fd_w);
      ++v;
    }
  return (0);
}
