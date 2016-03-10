/*
** get_next_line.c for getnextline in /home/robin/rendu/prog_elem/CPE_2015_getnextline
**
** Made by robin
** Login   <robin@epitech.net>
**
** Started on  Mon Jan  4 15:11:24 2016 robin
** Last update Fri Mar 11 00:27:02 2016 Voyevoda
*/

#include "./get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	my_strlen(char *str)
{
  int	k;

  k = 0;
  while (str[k] != '\0')
    {
      k++;
    }
  return (k);
}

char	*my_realloc(char *buffer, char *stock)
{
  char	*tmp;
  int	k;

  k = 0;
  tmp = stock;
  stock = malloc(my_strlen(buffer) + 1 + (my_strlen(tmp)));
  while (tmp[k] != '\0')
    {
      stock[k] = tmp[k];
      k++;
    }
  free(tmp);
  return (stock);
}

int		fill_stock(char *buffer, char *stock)
{
  int		j;
  static int	k = 0;

  j = 0;
  while (buffer[j] != '\0')
    {
      if (buffer[j] == '\n')
	{
	  stock[k] = '\0';
	  k = 0;
	  return (1);
	}
      stock[k] = buffer[j];
      j++;
      k++;
    }
  stock[k] = '\0';
  return (0);
}

char	*manhattan_project(char *buffer)
{
  int	i;
  int	k;

  i = k = 0;
  if (buffer[0] == '\0')
    return (NULL);
  while (buffer[i] != '\n' && buffer[i] != '\0')
    i++;
  if (buffer[i] == '\n')
    {
      i++;
      while (buffer[i] != '\0')
	{
	  buffer[k] = buffer[i];
	  k++;
	  i++;
	}
      buffer[k] = '\0';
    }
  return (buffer);
}

char		*get_next_line(const int fd)
{
  static char	*buffer = NULL;
  char		*stock;
  int		k;
  int		j;

  k = 0;
  j = 1;
  stock = malloc(READ_SIZE + 1);
  if (buffer == NULL)
    {
      if ((buffer = malloc(READ_SIZE + 1)) == NULL)
	return (NULL);
      if ((j = read(fd, buffer, READ_SIZE)) < 0)
	return (NULL);
      buffer[j] = '\0';
    }
  else if ((buffer = manhattan_project(buffer)) == NULL)
    return (NULL);
  while ((k = fill_stock(buffer, stock) == 0 && j > 0))
    {
      j = read(fd, buffer, READ_SIZE);
      buffer[j] = '\0';
      stock = my_realloc(buffer, stock);
    }
  return ((j == 0 && stock[0] == '\0') ? NULL : stock);
}
