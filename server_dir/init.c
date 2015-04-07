/*
** init.c for init in /home/durand_u/github/Myirc
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Mon Apr  6 12:43:25 2015 Rémi DURAND
** Last update Tue Apr  7 14:41:09 2015 Rémi DURAND
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

void		get_maxfds(t_cfds *cdata)
{
  int		v;

  v = 0;
  while (cdata->fds[v] != 0)
      ++v;
  cdata->nfds = cdata->fds[v];
}

void		aff_msg(int cfd)
{
  char		buff[512];
  int		len;

  len = read(cfd, buff, 511);
  if (len != -1)
    {

    }
  write(1, buff, len);
}

int		init_cli(int sfd, char **cip, t_cfds *cdata)
{
  socklen_t		in_size;
  struct sockaddr_in	in_client;
  struct timeval	timeout;

  in_size = sizeof(in_client);
  if ((cdata->fds[cdata->of] = accept(sfd, (addr_c)&in_client, &in_size)) == (-1))
    return (-1);
  cdata->fds[++cdata->of] = 0;
  FD_SET(cdata->fds[cdata->nfds], &cdata->set);
  if ((*cip = inet_ntoa(in_client.sin_addr)) == NULL)
    return (-1);
  printf("%s\n", *cip);
  get_maxfds(cdata);
  timeout.tv_usec = 150000;
  timeout.tv_sec = 0;
  select(cdata->nfds, &cdata->set, &cdata->set, NULL, &timeout);
  if (FD_ISSET(cdata->fds[0], &cdata->set))
    aff_msg(cdata->fds[0]);
  else if (FD_ISSET(cdata->fds[1], &cdata->set))
    aff_msg(cdata->fds[1]);
  return (0);
}
