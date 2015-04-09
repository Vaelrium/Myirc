/*
** irc.h for header in /home/durand_u/github/Myirc
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Mon Apr  6 12:39:14 2015 Rémi DURAND
** Last update Thu Apr  9 16:08:00 2015 Ambroise Coutarel
*/

#ifndef _IRC_H_
# define _IRC_H_

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

# define NB_QUE 512
# define FD_FREE 0
# define FD_CLIENT 1
# define FD_SERVER 2
# define CMD_SERV 3 // à augmenter au fur et à mesure des implementations

/*
** NICK
*/

# define ERR_NONICKNAMEGIVEN "431" // pas de paramètre pour /nick
# define ERR_ERRONEUSNICKNAME "432" // nickname contient chars invalides
# define ERR_NICKNAMEINUSE "433" //
# define ERR_NICKCOLLISION "436" // redondant avec nicknameinuse ?
# define ERR_NEEDMOREPARAMS "461"
# define ERR_INVITEONLYCHAN "743"
# define ERR_CHANNELISFULL "471"
# define ERR_NOSUCHCHANNEL "403"
# define ERR_BANNEDFROMCHAN "474"
# define ERR_BADCHANNELKEY "475"
# define ERR_BADCHANMASK "476"
# define ERR_TOOMANYCHANNELS "405"
# define ERR_NOTONCHANNEL "442"

typedef const struct sockaddr *	caddr_c;
typedef struct sockaddr *	addr_c;
typedef				void(*fct)();

typedef struct	s_cfds
{
  char		fd_type[NB_QUE];
  fct		fct_read[NB_QUE];
  fct		fct_write[NB_QUE];
  char		*nicks[NB_QUE];
  int		port;
  fd_set	fd_r;
  fd_set	fd_w;
  int		ncfd;
}		t_cfds;

typedef struct		s_command
{
  char			*command;
  int			(*func)(t_cfds *e, char **cmd, int fd);
}			t_command;

int		init_serv(struct protoent **pe, char **av,
			  struct sockaddr_in *s_in);
int		init_cli(t_cfds *cdata);
void		server_read(t_cfds *cdata, int fd, fd_set *set);
void		server_write(t_cfds *cdata, int fd, fd_set writefds);
void		handle_cmds(t_cfds *e, char **cmd, int fd);
char		**my_str_to_wordtab(char *str);
void	subinit(t_command *cmd, char *name,
		int (*func)(t_cfds*, char**, int));
void	init_commands();
void	free_wtab(char **tab);

extern	t_command	g_commands_server[8];

#endif /* !_IRC_H_ */
