/*
** irc.c for irc in /home/durand_u/github/Myirc
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Mon Apr  6 12:39:45 2015 Rémi DURAND
** Last update Wed Apr  8 13:45:53 2015 Rémi DURAND
*/

#include "irc.h"

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
  cdata.fd_type[sfd] = FD_SERVER;
  cdata.fct_read[sfd] = server_read;
  cdata.fct_write[sfd] = server_write;
  while (init_cli(&cdata) == 0)
    ;
  return (0);
}
