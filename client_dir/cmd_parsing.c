/*
** cmd_parsing.c for myirc in /home/ganesha/projets/Myirc/client_dir
**
** Made by Ambroise Coutarel
** Login   <ganesha@epitech.net>
**
** Started on  Thu Apr  9 20:33:21 2015 Ambroise Coutarel
** Last update Sat Apr 11 18:54:42 2015 Ambroise Coutarel
*/

#include "irc_client.h"

t_client_com	g_commands_client[3];

int		server_response(int fd)
{
  int		len;
  int		timeout;
  char		*resp;

  len = 0;
  timeout = 1;
  while (!len && ioctl(fd, FIONREAD, &len) >= 0)
    {
      if (timeout == 10)
	return (-1);
      usleep(3000);
      ++timeout;
    }
  if ((resp = malloc(sizeof(char) * (len + 1))) == NULL)
    {
      printf("Unable to malloc response\n");
      return (-1);
    }
  len = read(fd, resp, len);
  resp[len] = '\0';
  printf("%s", resp);
  free(resp);
  return (0);
}

void	subinit(t_client_com *cmd, char *name,
		void (*func)(char **, int *, char *))
{
  cmd->command = strdup(name);
  cmd->func = func;
}

void	send_to_serv(char *query, int *server_socket)
{
  write((*server_socket), query, strlen(query));
}

void	init_commands()
{
  subinit(&(g_commands_client[0]), "/server", &server);
  subinit(&(g_commands_client[1]), "/send_file", &send_file);
  subinit(&(g_commands_client[2]), "/accept_file", &accept_file);
}

void		handle_cmds(char *query, int *server_socket, char *is_connected)
{
  char		**cmd;
  int		v;

  v = 0;
  cmd = my_str_to_wordtab(query);
  while (v != CLIENT_CMD)
    {
      if (strcmp(cmd[0], g_commands_client[v].command) == 0)
  	{
	  // if (cmd[1])
	    g_commands_client[v].func(&(cmd[1]), server_socket, is_connected);
	  //server_response((*server_socket));
  	  free_wtab(cmd);
  	  return ;
  	}
      ++v;
    }
  if ((*server_socket) != -1 && (*is_connected) == 1)
    {
      send_to_serv(query, server_socket);
      server_response((*server_socket));
      free_wtab(cmd);
    }
}
