/*
** irc.c for irc in /home/durand_u/github/Myirc
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Mon Apr  6 12:39:45 2015 Rémi DURAND
** Last update Tue Apr  7 14:34:39 2015 Rémi DURAND
*/

#include "irc.h"

int	main(int ac, char **av)
{
  struct protoent       *pe;
  struct sockaddr_in    s_in;
  int                   sfd;
  char                  *cip;
  t_cfds		cdata;

  if ((ac != 2 && printf("No port\n")) || init_serv(&pe, av, &s_in) == (-1))
    return (-1);
  if ((sfd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == (-1) ||
      bind(sfd, (caddr_c)&s_in, sizeof(s_in)) == (-1) ||
      listen(sfd, NB_QUE) == (-1))
    return (-1);
  cdata.nfds = 0;
  cdata.of = 0;
  FD_ZERO(&cdata.set);
  while (init_cli(sfd, &cip, &cdata) == 0)
    ;
  return (0);
}
