/*
** cmds.c for cmds in /home/durand_u/github/Myirc/server_dir
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Thu Apr  9 14:23:25 2015 Rémi DURAND
** Last update Thu Apr  9 16:24:34 2015 Rémi DURAND
*/

#include "irc.h"

void		nick(t_cfds *e, char **cmd, int fd)
{
  if (!cmd[0] || cmd[1])
    {
      write(fd, "Error, none or too many arguments\r\n", 36);
      return ;
    }
  free(e->nicks[fd]);
  e->nicks[fd] = strdup(cmd[0]);
  write(fd, "Name changed\r\n", 14);
}

void		join(t_cfds *e, char **cmd, int fd)
{
  if (!cmd[0] || cmd[1])
    {
      write(fd, "Error, none or too many arguments\r\n", 36);
      return ;
    }
  if (e->chan[fd])
    free(e->chan[fd]);
  e->chan[fd] = strdup(cmd[0]);
  write(fd, "Channel joined\r\n", 16);
  //Add to chan_name;
}

void		make_list_msg(char *string, t_cfds *e, char **msg)
{
  int		len;
  int		v;

  len = 0;
  v = 0;
  while (e->chan_name[v] != NULL)
    {
      if (string == NULL || strstr(e->chan_name[v], string) != NULL)
	len += (strlen(e->chan_name[v]) + 1);
      ++v;
    }
  if ((*msg = malloc(sizeof(char) * (len + 1))) == NULL)
    return ;
  *msg[0] = '\0';
  v = 0;
  while (e->chan_name[v] != NULL)
    {
      if (string == NULL || strstr(e->chan_name[v], string) != NULL)
	{
	  strcat(*msg, e->chan_name[v]);
	  if (e->chan_name[v + 1])
	    strcat(*msg, "\n");
	}
      ++v;
    }
}

void		list(t_cfds *e, char **cmd, int fd)
{
  char		*msg;

  if (cmd[0] && cmd[1])
    {
      write(fd, "Error, too many arguments\r\n", 29);
      return ;
    }
  make_list_msg(cmd[0], e, &msg);
  write(fd, msg, strlen(msg));
  free(msg);
}
