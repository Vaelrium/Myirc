/*
** irc_client.h for MyIRC in /home/ganesha/projets/Myirc/client_dir
**
** Made by Ambroise Coutarel
** Login   <ganesha@epitech.net>
**
** Started on  Thu Apr  9 18:11:49 2015 Ambroise Coutarel
** Last update Sat Apr 11 13:49:35 2015 Ambroise Coutarel
*/

#ifndef IRC_CLIENT_H_

# define IRC_CLIENT_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/sendfile.h>
# include <fcntl.h>
# include <netdb.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <dirent.h>

# define PROMPT ">"

typedef struct sockaddr* sock;

typedef struct	s_client_com
{
  char		*command;
  void		(*func)(char **cmd, int *server_socket, char *is_connected);
}		t_client_com;

void	init_commands();
int		server_response(int fd);
void	subinit(t_client_com *cmd, char *name,
		void (*func)(char**, int*, char*));
void	server(char **cmd, int *socket, char *is_connected);
void	send_file(char **cmd, int *socket, char *is_connected);
void	accept_file(char **cmd, int *socket, char *is_connected);
void	free_wtab(char **wordtab);
char	**my_str_to_wordtab(char *str);
void	handle_cmds(char *query, int *server_socket, char* is_connected);

extern	t_client_com	g_commands_client[3];
# endif /* !IRC_CLIENT_H_ */
