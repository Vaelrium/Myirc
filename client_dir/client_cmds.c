/*
** client_cmds.c for myirc in /home/ganesha/projets/Myirc/client_dir
**
** Made by Ambroise Coutarel
** Login   <ganesha@epitech.net>
**
** Started on  Thu Apr  9 20:44:57 2015 Ambroise Coutarel
** Last update Sun Apr 12 14:06:32 2015 Ambroise Coutarel
*/

#include "irc_client.h"

void	server(char **cmd, int *s_fd, char *is_connected)
{
  struct protoent	*prot;
  struct sockaddr_in	sock_in;

  if ((!cmd[0]  && !cmd[1]) || !cmd[1])
    {
      printf("usage : /server <IP> <port>\r\n");
      return ;
    }
  sock_in.sin_family = AF_INET;
  sock_in.sin_port = htons(atoi(cmd[1]));
  sock_in.sin_addr.s_addr = inet_addr(cmd[0]);
  if (((prot = getprotobyname("TCP")) == NULL) ||
      (((*s_fd) = socket(AF_INET, SOCK_STREAM, prot->p_proto)) == -1) ||
      (connect((*s_fd), (sock)&sock_in, sizeof(sock_in)) == -1))
    {
      printf("Failure to connect to %s on port %s\r\n", cmd[0], cmd[1]);
      return ;
    }
  if (server_response((*s_fd)) != (-1))
    (*is_connected) = 1;
}

void	send_file(char **cmd, int *socket, char *is_connected)
{
  int		len;
  int		nfd;
  char		*file;

  len = 0;
  if ((*is_connected))
    {
      cmd[1][(int)strlen(cmd[1]) - 1] = 0;
      printf("opening %s, len name = %ld\n", cmd[1], strlen(cmd[1]));
      if ((nfd = open(cmd[1], O_RDONLY)) == (-1))
	{
	  send_to_serv("xxx : fail", socket);
	  return ;
	}
      ioctl(nfd, FIONREAD, &len);
      if ((file = malloc(sizeof(char) * len)) == NULL)
	return ;
      read(nfd, file, len);
      write((*socket), file, len);
      printf("File %s : upload put\n", cmd[1]);
      free(file);
    }
}

void		recv_file(int *socket, int nfd)
{
  int		len;
  char		*filecontents;

  while (!len && ioctl((*socket), FIONREAD, &len) >= 0)
    usleep(3000);
  if ((filecontents = malloc(sizeof(char) * len)) == NULL)
    return ;
  read((*socket), filecontents, len);
  write(nfd, filecontents, len);
}

void		accept_file(char **cmd, int *socket, char *is_connected)
{
  int		nfd;

  if ((*is_connected))
    {
      if ((nfd = open(cmd[0], O_CREAT | O_RDWR, 0666)) == (-1))
	{
	  write((*socket), "Failed to open file\r\n", 21);
	  return ;
	}
      recv_file(socket, nfd);
      }
}
