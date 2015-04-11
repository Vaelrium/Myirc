/*
** cmds.c for cmds in /home/durand_u/github/Myirc/server_dir
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Thu Apr  9 14:23:25 2015 Rémi DURAND
** Last update Thu Apr  9 20:19:26 2015 Rémi DURAND
*/

#include "irc.h"

void		nick(t_cfds *e, char **cmd, int fd)
{
  int		v;

  v = 0;
  if (!cmd[0] || cmd[1])
    {
      write(fd, "Error, none or too many arguments\r\n", 36);
      return ;
    }
  while (v != NB_QUE)
    {
      if (e->nicks[v] && strcmp(e->nicks[v], cmd[0]) == 0)
	{
	  write(fd, "Error, nickname already taken\r\n", 31);
	  return ;
	}
      ++v;
    }
  free(e->nicks[fd]);
  e->nicks[fd] = strdup(cmd[0]);
  write(fd, "Name changed\r\n", 14);
}

void		add_chan(t_cfds *e, char *name)
{
  int		v;
  int		len;
  char		**tmp;

  v = 0;
  tmp = e->chan_name;
  while (e->chan_name[v])
    ++v;
  len = v;
  if ((e->chan_name = malloc(sizeof(char *) * (len + 2))) == NULL)
    return ;
  v = 0;
  while (v != len)
    {
      e->chan_name[v] = strdup(tmp[v]);
      ++v;
    }
  e->chan_name[v] = strdup(name);
  e->chan_name[v + 1] = NULL;
  free_wtab(tmp);
}

void		join(t_cfds *e, char **cmd, int fd)
{
  int		v;

  v = 0;
  if (!cmd[0] || cmd[1])
    {
      write(fd, "Error, none or too many arguments\r\n", 36);
      return ;
    }
  if (e->chan[fd])
    free(e->chan[fd]);
  e->chan[fd] = strdup(cmd[0]);
  write(fd, "Channel joined\r\n", 16);
  while (e->chan_name[v] != NULL)
    {
      if (strcmp(e->chan_name[v], cmd[0]) == 0)
	return ;
      ++v;
    }
  add_chan(e, cmd[0]);
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
      write(fd, "Error, too many arguments\r\n", 27);
      return ;
    }
  make_list_msg(cmd[0], e, &msg);
  write(fd, msg, strlen(msg));
  free(msg);
}
