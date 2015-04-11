/*
** client_cmds.c for myirc in /home/ganesha/projets/Myirc/client_dir
**
** Made by Ambroise Coutarel
** Login   <ganesha@epitech.net>
**
** Started on  Thu Apr  9 20:44:57 2015 Ambroise Coutarel
** Last update Sat Apr 11 13:49:56 2015 Ambroise Coutarel
*/

#include "irc_client.h"

void	server(char **cmd, int *s_fd, char *is_connected)
{
  struct protoent	*prot;
  struct sockaddr_in	sock_in;

  sock_in.sin_family = AF_INET;
  sock_in.sin_port = htons(atoi(cmd[1]));
  sock_in.sin_addr.s_addr = inet_addr(cmd[0]);
  if ((prot = getprotobyname("TCP")) == NULL)
    return ;
  if (((*s_fd) = socket(AF_INET, SOCK_STREAM, prot->p_proto)) == -1)
    return ;
  if ((connect((*s_fd), (sock)&sock_in, sizeof(sock_in))) == -1)
    return ;
  if (server_response((*s_fd)) != (-1))
    {
      (*is_connected) = 1;
    }
  return ;
}

void	send_file(char **cmd, int *socket, char *is_connected)
{
  (void)cmd;
  (void)socket;
  (void)is_connected;
  return ;
}

void	accept_file(char **cmd, int *socket, char *is_connected)
{
  (void)cmd;
  (void)socket;
  (void)is_connected;
  return ;
}
