/*
** cmds_handler.c for handler in /home/durand_u/github/Myirc/server_dir
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Thu Apr  9 13:59:06 2015 Rémi DURAND
** Last update Thu Apr  9 18:32:35 2015 Rémi DURAND
*/

#include "irc.h"

t_command	g_commands_server[8];

void	subinit(t_command *cmd, char *name,
		void (*func)(t_cfds*, char**, int))
{
  cmd->command = strdup(name);
  cmd->func = func;
}

void	init_commands()
{
  subinit(&(g_commands_server[0]), "/nick", &nick);
  subinit(&(g_commands_server[1]), "/list", &list);
  subinit(&(g_commands_server[2]), "/join", &join);
  subinit(&(g_commands_server[3]), "/part", &part);
  subinit(&(g_commands_server[4]), "/users", &users);
  /* subinit(&(g_commands_server[5]), "/msg", &msg); */
  /* subinit(&(g_commands_server[6]), "/send_file", &send_file); */
  /* subinit(&(g_commands_server[7]), "/accept_file", &accept_file); */
}

void		handle_cmds(t_cfds *e, char **cmd, int fd)
{
  int		v;

  v = 0;
  init_commands();
  while (v != CMD_SERV)
    {
      if (strcmp(cmd[0], g_commands_server[v].command) == 0)
	{
	  g_commands_server[v].func(e, &(cmd[1]), fd);
	  free_wtab(cmd);
	  return ;
	}
      ++v;
    }
}
