
int		receive_file(int fd, char *f_name)
{
  int		len;
  int		nfd;
  char		*file;

  len = 0;
  newline_suppr(f_name);
  nfd = open(f_name, O_CREAT | O_WRONLY, 0666);
  write(fd, "7", 1);
  while (!len && ioctl(fd, FIONREAD, &len) >= 0)
    usleep(3000);
  if ((file = malloc(sizeof(char) * len)) == NULL)
    return (-1);
  read(fd, file, len);
  write(nfd, file, len);
  printf("File %s got\n", f_name);
  free(file);
  return (0);
}

int		send_file(int fd, char *f_name)
{
  int		len;
  int		nfd;
  char		*file;

  len = 0;
  newline_suppr(f_name);
  if ((nfd = open(f_name, O_RDONLY)) == (-1))
    {
      send_msg(fd, "xxx : fail");
      return (-1);
    }
  ioctl(nfd, FIONREAD, &len);
  if ((file = malloc(sizeof(char) * len)) == NULL)
    return (-1);
  read(nfd, file, len);
  write(fd, file, len);
  printf("File %s put\n", f_name);
  free(file);
  return (0);
}

int		server_response(int fd)
{
  int		len;
  char		*resp;

  len = 0;
  while (!len && ioctl(fd, FIONREAD, &len) >= 0)
    usleep(3000);
  if ((resp = malloc(sizeof(char) * (len + 1))) == NULL)
    {
      printf("Unable to malloc response\n");
      return (-1);
    }
  len = read(fd, resp, len);
  resp[len] = '\0';
  printf("%s", resp);
  if (strncmp(resp, "777 : ", 6) == 0)
    receive_file(fd, &resp[6]);
  else if (strncmp(resp, "778 : ", 6) == 0)
    send_file(fd, &resp[6]);
  free(resp);
  return (0);
}
