/*
** init.c for init in /home/durand_u/github/Myirc
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Mon Apr  6 12:43:25 2015 Rémi DURAND
** Last update Wed Apr  8 15:25:29 2015 Ambroise Coutarel
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

void			init_set(t_cfds *cdata, struct timeval *tv)
{
  int			v;

  v = 0;
  tv->tv_sec = 20;
  tv->tv_usec = 0;
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
}

int			init_cli(t_cfds *cdata)
{
  struct timeval	tv;
  int			v;

  while (1)
    {
      v = 0;
      FD_ZERO(&cdata->fd_r);
      FD_ZERO(&cdata->fd_w);
      cdata->ncfd = 0;
      init_set(cdata, &tv);
      if (select(cdata->ncfd + 1, &cdata->fd_r, &cdata->fd_w, NULL, &tv) == -1)
	perror("select");
      while (v < NB_QUE)
	{
	  if (FD_ISSET(v, &cdata->fd_r))
	    {
	      cdata->fct_read[v](cdata, v, &cdata->fd_w);
	    }
	  ++v;
	}
    }
  return (0);
}
