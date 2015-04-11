/*
** cmds3.c for cmds3 in /home/durand_u/github/Myirc/server_dir
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Sat Apr 11 10:56:59 2015 Rémi DURAND
** Last update Sat Apr 11 11:40:12 2015 Rémi DURAND
*/

#include "irc.h"

char		*make_path(char *arg, char *wd)
{
  char		*path;

  path = malloc(sizeof(char) * (strlen(arg) + strlen(wd) + 2));
  if (!path)
    return (NULL);
  strcpy(path, wd);
  strcat(path, "/");
  strcat(path, arg);
  return (path);
}

void	        accept_file(t_cfds *e, char **cmd, int fd)
{
  int		nfd;
  char		*path;
  int		len;

  (void)e;
  if (!cmd[0] || cmd[1] || !(path = make_path(cmd[0], "./")))
    {
      write(fd, "Error, none or too many arguments\r\n", 36);
      return ;
    }
  else if ((nfd = open(path, O_RDONLY)) == (-1))
    {
      write(fd, "Error, no file\r\n", 16);
      return ;
    }
  ioctl(nfd, FIONREAD, &len);
  sendfile(fd, nfd, NULL, len);
  close(nfd);
  remove(path);
  free(path);
  write(fd, "File tranfered\r\n", 16);
}

int		write_file(int cfd, int fd)
{
  int		len;
  char		*file;

  while (!len && ioctl(cfd, FIONREAD, &len) >= 0)
    usleep(3000);
  if ((file = malloc(sizeof(char) * len)) == NULL)
    return (-1);
  read(cfd, file, len);
  write(fd, file, len);
  free(file);
  return (0);
}

void		invite_file(char *nick, t_cfds *e)
{
  int		v;
  char		*invit;

  if ((invit = malloc(sizeof(char) * (24 + strlen(nick) + 1))) == NULL)
    return ;
  sprintf(invit, "Available file from : \"%s\"", nick);
  v = 0;
  while (v != NB_QUE)
    {
      if (e->nicks[v] && strcmp(nick, e->nicks[v]) == 0)
	{
	  write(v, invit, strlen(invit));
	  return ;
	}
      ++v;
    }
}

void	        send_file(t_cfds *e, char **cmd, int fd)
{
  char		*path;
  int		nfd;

  (void)e;
  if (!cmd[0] || !cmd[1] || cmd[2] || !(path = make_path(cmd[0], "./")))
    {
      write(fd, "Error, none or too many arguments\r\n", 36);
      return ;
    }
  else if ((nfd = open(path, O_CREAT | O_WRONLY, 0666)) == (-1))
    {
      write(fd, "Failed to open file\r\n", 21);
      return ;
    }
  write_file(fd, nfd);
  invite_file(cmd[0], e);
  write(fd, "File tranfered\r\n", 16);
  return ;
}
