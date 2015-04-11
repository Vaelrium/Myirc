/*
** client_handler.c for  in /home/ganesha/projets/Myirc/server_dir
**
** Made by Ambroise Coutarel
** Login   <ganesha@epitech.net>
**
** Started on  Wed Apr  8 15:23:57 2015 Ambroise Coutarel
** Last update Sat Apr 11 13:59:02 2015 Ambroise Coutarel
*/

#include "irc.h"

void		write_to_all(t_cfds *e, int fd, char *buf)
{
  char		id[strlen(e->nicks[fd]) + 4];
  int		i;

  i = 0;
  while (i < NB_QUE)
    {
      if (FD_ISSET(i, &(e->fd_w)) && i != fd &&
	  (strcmp(e->chan[fd], e->chan[i]) == 0))
	{
	  sprintf(id, "%s : ", e->nicks[fd]);
	  write(i, id, strlen(id));
	  write(i, buf, strlen(buf));
	  write(i, "\r\n", 2);
	}
      ++i;
    }
}

void		client_read(t_cfds *e, int fd)
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
	write_to_all(e, fd, buf);
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
  write(cs, "Myirc durand_u/coutar_a V.1 connected\r\n", 39);
  printf("%s\n", cip);
  cdata->nicks[cs] = strdup(cip);
  cdata->chan[cs] = strdup("DefaultChannel");
  cdata->fd_type[cs] = FD_CLIENT;
  cdata->fct_read[cs] = client_read;
  cdata->fct_write[cs] = NULL;
}

void		server_read(t_cfds *cdata, int fd)
{
  printf("New client\n");
  add_client(cdata, fd);
}

void		server_write(t_cfds *cdata, int fd)
{
  (void)cdata;
  (void)fd;
}
