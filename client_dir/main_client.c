/*
** main_client.c for myIRC in /home/ganesha/projets/Myirc/client_dir
**
** Made by Ambroise Coutarel
** Login   <ganesha@epitech.net>
**
** Started on  Thu Apr  9 18:12:56 2015 Ambroise Coutarel
** Last update Sat Apr 11 14:13:28 2015 Ambroise Coutarel
*/

#include "irc_client.h"

int	read_request(char buffer[512])
{
  int	len;

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

  while ("jeff")
    {
      memset(user_request, 0, 512);
      write(1, PROMPT, strlen(PROMPT));
      if (read_request(user_request) != -1)
	{
	  handle_cmds(user_request, &socket, &is_connected);
	}
    }
  return (0);
}
