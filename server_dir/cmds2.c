/*
** cmds2.c for  in /home/durand_u/github/Myirc/server_dir
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Thu Apr  9 17:27:25 2015 Rémi DURAND
** Last update Thu Apr  9 18:37:24 2015 Rémi DURAND
*/

#include "irc.h"

void	        part(t_cfds *e, char **cmd, int fd)
{
  if (!cmd[0] || cmd[1])
    {
      write(fd, "Error, none or too many arguments\r\n", 36);
      return ;
    }
  else if ((e->chan[fd] && strcmp(e->chan[fd], cmd[0]) != 0) ||
	   strcmp(cmd[0], "DefaultChannel") == 0)
    {
      write(fd, "Cannot leave unjoined channel\r\n", 31);
      return ;
    }
  if (e->chan[fd])
    free(e->chan[fd]);
  e->chan[fd] = strdup("DefaultChannel");
}

void		make_users_msg(t_cfds *e, char **msg, int fd)
{
  int		v;
  int		len;

  v = 0;
  len = strlen(e->chan[fd]) + 9;
  while (v != NB_QUE)
    {
      if (e->chan[v] && strcmp(e->chan[fd], e->chan[v]) == 0)
	len += (strlen(e->nicks[v]) + 1);
      ++v;
    }
  if ((*msg = malloc(sizeof(char) * (len + 1))) == NULL)
    return ;
}

void		users(t_cfds *e, char **cmd, int fd)
{
  char		*msg;
  int		v;

  v = 0;
  if (cmd[0])
    {
      write(fd, "Error, too many arguments\r\n", 27);
      return ;
    }
  make_users_msg(e, &msg, fd);
  strcpy(msg, e->chan[fd]);
  strcat(msg, " users :\n");
  while (v != NB_QUE)
    {
      if (e->chan[v] && strcmp(e->chan[fd], e->chan[v]) == 0)
	{
	  strcat(msg, e->nicks[v]);
	  strcat(msg, "\n");
	}
      ++v;
    }
  write(fd, msg, strlen(msg));
  free(msg);
}
