/*
** init.c for init in /home/durand_u/github/Myirc
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Mon Apr  6 12:43:25 2015 Rémi DURAND
** Last update Mon Apr  6 12:52:00 2015 Rémi DURAND
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
