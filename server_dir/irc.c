/*
** irc.c for irc in /home/durand_u/github/Myirc
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Mon Apr  6 12:39:45 2015 Rémi DURAND
** Last update Sat Apr 11 18:36:23 2015 Ambroise Coutarel
*/

#include "irc.h"

int	cdata_set(t_cfds *cdata, int sfd)
{
  int	v;

  v = 0;
  memset(cdata->fd_type, FD_FREE, NB_QUE);
  cdata->fd_type[sfd] = FD_SERVER;
  cdata->fct_read[sfd] = server_read;
  cdata->fct_write[sfd] = server_write;
  if ((cdata->chan_name = malloc(sizeof(char *) * 2)) == NULL ||
      (cdata->chan_name[0] = strdup("DefaultChannel")) == NULL)
    return (-1);
  cdata->chan_name[1] = NULL;
  while (v != NB_QUE)
    cdata->chan[v++] = NULL;
  v = 0;
  while (v != NB_QUE)
    cdata->nicks[v++] = NULL;
  return (0);
}

int	main(int ac, char **av)
{
  struct protoent       *pe;
  struct sockaddr_in    s_in;
  int                   sfd;
  t_cfds		cdata;

  if ((ac != 2 && printf("No port\n")) || init_serv(&pe, av, &s_in) == (-1))
    return (-1);
  if ((sfd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == (-1) ||
      bind(sfd, (caddr_c)&s_in, sizeof(s_in)) == (-1) ||
      listen(sfd, NB_QUE) == (-1))
    return (-1);
  if (cdata_set(&cdata, sfd) == (-1))
    return (-1);
  init_cli(&cdata);
  return (0);
}
