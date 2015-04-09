/*
** my_str_to_wordtab.c for wordtab in /home/durand_u/rendu/PSU_2014_myftp/server_dir
** 
** Made by Rémi DURAND
** Login   <durand_u@epitech.net>
** 
** Started on  Wed Mar 11 10:40:00 2015 Rémi DURAND
** Last update Tue Mar 17 09:50:52 2015 Rémi DURAND
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void		free_wtab(char **wtab)
{
  int		v;

  v = 0;
  while (wtab[v] != NULL)
    {
      free(wtab[v]);
      ++v;
    }
  free(wtab);
}

int		get_nb_w(char *str)
{
  int		ret;
  int		v;

  v = 0;
  ret = 0;
  while (str[v] != '\0')
    {
      if ((v == 0 && str[v] != ' ') ||
	  (str[v] == ' ' && str[v + 1] != ' ' && str[v + 1] != '\0'))
	++ret;
      ++v;
    }
  return (ret);
}

int		len_next_word(char *str, int *of)
{
  int		ret;
  int		tmp;

  ret = 0;
  tmp = *of;
  while (str[tmp] == ' ')
    ++tmp;
  while (str[tmp] != '\0' && str[tmp] != ' ')
    {
      ++tmp;
      ++ret;
    }
  return (ret);
}

void		write_next_word(char *word, char *str, int *of, int wlen)
{
  int		v;

  v = 0;
  while (str[*of] == ' ')
    ++(*of);
  while (v != wlen)
    {
      word[v] = str[*of];
      ++v;
      ++(*of);
    }
  while (str[*of] == ' ')
    ++(*of);
  word[v] = '\0';
}

char		**my_str_to_wordtab(char *str)
{
  int		nb_w;
  char		**ret;
  int		v;
  int		of;
  int		wlen;

  v = 0;
  of = 0;
  nb_w = get_nb_w(str);
  if ((ret = malloc(sizeof(char *) * (nb_w + 1))) == NULL)
    return (NULL);
  while (v != nb_w)
    {
      wlen = len_next_word(str, &of);
      if ((ret[v] = malloc(sizeof(char) * (wlen + 1))) == NULL)
	return (NULL);
      write_next_word(ret[v], str, &of, wlen);
      ++v;
    }
  ret[v] = NULL;
  return (ret);
}
