/*
** client_handler.c for  in /home/ganesha/projets/Myirc/server_dir
**
** Made by Ambroise Coutarel
** Login   <ganesha@epitech.net>
**
** Started on  Wed Apr  8 15:23:57 2015 Ambroise Coutarel
** Last update Wed Apr  8 15:31:43 2015 Ambroise Coutarel
*/

#include "irc.h"

void		write_to_all(fd_set *set, int fd, char *buf, int r)
{
  char		id[15];
  int		i;

  i = 0;
  while (i < NB_QUE)
    {
      if (FD_ISSET(i, set) && i != fd)
	{
	  sprintf(id, "%d : ", i);
	  write(i, id, strlen(id));
	  write(i, buf, r);
	}
      ++i;
    }
}

void		client_read(t_cfds *e, int fd, fd_set *set)
{
  int		r;
  char		buf[4096];
  /* char		id[15]; */
  /* int		i; */

  r = read(fd, buf, 4096);
  if (r > 0)
    {
      buf[r] = '\0';
      printf("%d: %s\n", fd, buf);
      write_to_all(set, fd, buf, r);
      /* i = 0; */
      /* while (i < NB_QUE) */
      /* 	{ */
      /* 	  if (FD_ISSET(i, set) && i != fd) */
      /* 	    { */
      /* 	      sprintf(id, "%d : ", i); */
      /* 	      write(i, id, strlen(id)); */
      /* 	      write(i, buf, r); */
      /* 	    } */
      /* 	  ++i; */
      /* 	} */
    }
  else
    {
      printf("%d: Connection closed\n", fd);
      close(fd);
      e->fd_type[fd] = FD_FREE;
    }
}

void		client_write(t_cfds *e, int fd, fd_set *writefds)
{
  int		r;
  char		buf[4096];
  int		i;

  r = read(fd, buf, 4096);
  if (r > 0)
    {
      buf[r] = '\0';
      printf("%d: %s\n", fd, buf);
      i = 0;
      while (i < NB_QUE)
      	 {
      	   if (FD_ISSET(i, writefds) && i != fd)
      	     {
      	       printf("write on %d\n", i);
      	       write(fd, buf, r);
      	     }
	   ++i;
      	 }
    }
  else
    {
      printf("%d: Connection closed\n", fd);
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
  cdata->fd_type[cs] = FD_CLIENT;
  cdata->fct_read[cs] = client_read;
  cdata->fct_write[cs] = client_write;
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