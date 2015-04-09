/*
** client_handler.c for  in /home/ganesha/projets/Myirc/server_dir
**
** Made by Ambroise Coutarel
** Login   <ganesha@epitech.net>
**
** Started on  Wed Apr  8 15:23:57 2015 Ambroise Coutarel
** Last update Thu Apr  9 16:52:19 2015 Rémi DURAND
*/

#include "irc.h"

void		write_to_all(fd_set *set, int fd, char *buf, char *r)
{
  char		id[strlen(r) + 4];
  int		i;

  i = 0;
  while (i < NB_QUE)
    {
      if (FD_ISSET(i, set) && i != fd)
	{
	  sprintf(id, "%s : ", r);
	  write(i, id, strlen(id));
	  write(i, buf, strlen(buf));
	}
      ++i;
    }
}

void		client_read(t_cfds *e, int fd, fd_set *set)
{
  int		r;
  char		buf[4096];

  r = read(fd, buf, 4096);
  if (r > 0)
    {
      buf[r - 1] = '\0';
      if (buf[0] == '/')
	handle_cmds(e, my_str_to_wordtab(buf), fd);
      else
	write_to_all(set, fd, buf, e->nicks[fd]);
      printf("%s: %s\n", e->nicks[fd], buf);
    }
  else
    {
      printf("%s: Connection closed\n", e->nicks[fd]);
      close(fd);
      e->fd_type[fd] = FD_FREE;
    }
}

void			add_client(t_cfds *cdata, int s)
{
  int			cs;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;
  char			*cip;

  client_sin_len = sizeof(client_sin);
  cs = accept(s, (addr_c)&client_sin, &client_sin_len);
  if ((cip = inet_ntoa(client_sin.sin_addr)) == NULL)
    return ;
  printf("%s\n", cip);
  cdata->nicks[cs] = strdup(cip);
  cdata->chan[cs] = strdup("Default Channel");
  cdata->fd_type[cs] = FD_CLIENT;
  cdata->fct_read[cs] = client_read;
  cdata->fct_write[cs] = NULL;
}

void		server_read(t_cfds *cdata, int fd, fd_set *set)
{
  printf("New client\n");
  add_client(cdata, fd);
  (void)set;
}

void		server_write(t_cfds *cdata, int fd, fd_set writefds)
{
  (void)cdata;
  (void)fd;
  (void)writefds;
}
