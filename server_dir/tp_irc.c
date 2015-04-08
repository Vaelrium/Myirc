#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define FD_FREE 0
#define FD_CLIENT 1
#define FD_SERVER 2

#define MAX_FD 255

typedef		void(*fct)();

typedef struct	s_env
{
  char		fd_type[MAX_FD];
  fct		fct_read[MAX_FD];
  fct		fct_write[MAX_FD];
  int		port;
}		t_env;

void		client_read(t_env *e, int fd, fd_set *set)
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
      while (i < MAX_FD)
	{
	  if (FD_ISSET(i, set) && i != fd)
	    write(i, buf, r);
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

void		client_write(t_env *e, int fd, fd_set *writefds)
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
      while (i < MAX_FD)
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

void			add_client(t_env *e, int s)
{
  int			cs;
  struct sockaddr_in	client_sin;
  int			client_sin_len;

  client_sin_len = sizeof(client_sin);
  cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
  e->fd_type[cs] = FD_CLIENT;
  e->fct_read[cs] = client_read;
  e->fct_write[cs] = client_write;
}

void		server_read(t_env *e, int fd, fd_set *set)
{
  printf("New client\n");
  add_client(e, fd);
}

void		server_write(t_env *e, int fd, fd_set writefds)
{
}

void			add_server(t_env *e)
{
  int			s;
  struct sockaddr_in	sin;

  s = socket(PF_INET, SOCK_STREAM, 0);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(e->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  bind(s, (struct sockaddr*)&sin, sizeof(sin));
  listen(s, 42);
  e->fd_type[s] = FD_SERVER;
  e->fct_read[s] = server_read;
  e->fct_write[s] = server_write;
}

int			main(int argc, char **argv)
{
  t_env			e;
  int			i;
  int			fd_max;
  fd_set		fd_read;
  fd_set		fd_write;
  struct timeval	tv;

  if (argc < 2)
    {
      printf("gonna need a port chief\n");
      return (0);
    }
  memset(e.fd_type, FD_FREE, MAX_FD);
  e.port = atoi(argv[1]);
  add_server(&e);
  tv.tv_sec = 20;
  tv.tv_usec = 0;
  while (1)
    {
      FD_ZERO(&fd_read);
      FD_ZERO(&fd_write);
      fd_max = 0;
      i = 0;
      while (i < MAX_FD)
	{
	  if (e.fd_type[i] != FD_FREE)
	    {
	      FD_SET(i, &fd_read);
	      FD_SET(i, &fd_write);
	      fd_max = i;
	    }
	  ++i;
	}
      if (select(fd_max + 1, &fd_read, &fd_write, NULL, &tv) == -1)
	perror("select");
      i = 0;
      while (i < MAX_FD)
	{
	  if (FD_ISSET(i, &fd_read))
	    e.fct_read[i](&e, i, &fd_write);
	  ++i;
	}
    }
  return (0);
}
