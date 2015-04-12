/*
** main_client.c for myIRC in /home/ganesha/projets/Myirc/client_dir
**
** Made by Ambroise Coutarel
** Login   <ganesha@epitech.net>
**
** Started on  Thu Apr  9 18:12:56 2015 Ambroise Coutarel
** Last update Sat Apr 11 19:05:39 2015 Ambroise Coutarel
*/

#include "irc_client.h"

t_client_com	g_commands_client[3];

void	free_commands()
{
  int	i;

  i = 0;
  while (i != CLIENT_CMD)
    {
      free(g_commands_client[i].command);
    }
}

int		read_request(char buffer[512])
{
  int		len;

 while (1)
    {
      if ((len = read(0, buffer, 255)) > 0 && len <= 510)
	{
	  buffer[len] = 0;
	  return (len);
	}
      else
	return (-1);
    }
  return (0);
}

int	main(void)
{
  int	socket;
  char	user_request[512];
  char	is_connected;

  socket = -1;
  is_connected = 0;
  init_commands();
  while ("jeff")
    {
      memset(user_request, 0, 512);
      write(1, PROMPT, strlen(PROMPT));
      if (read_request(user_request) != -1 && strcmp(user_request, "\n") != 0)
	{
	  handle_cmds(user_request, &socket, &is_connected);
	}
      if(socket != -1 && is_connected == 1)
	server_response(socket);
    }
  return (0);
}
