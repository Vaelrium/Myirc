/*
** cmds_handler.c for handler in /home/durand_u/github/Myirc/server_dir
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Thu Apr  9 13:59:06 2015 Rémi DURAND
** Last update Thu Apr  9 16:18:22 2015 Rémi DURAND
*/

#include "irc.h"

void		handle_cmds(t_cfds *e, char **cmd, int fd)
{
  (void)e;
  (void)fd;
  list(e, &cmd[1], fd);
}
