/*
** get_next_line.c for getnextline in /home/robin/rendu/prog_elem/CPE_2015_getnextline
**
** Made by robin
** Login   <robin@epitech.net>
**
** Started on  Mon Jan  4 15:11:24 2016 robin
** Last update Thu Jan 14 10:01:06 2016 robin
*/

#include "./get_nextline.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

char	my_putchar(char c)
{
  write(1, &c, 1);
}

int	my_putstr(char *str)
{
  int	j;

  j = 0;
  while (str[j] != '\0')
    {
      my_putchar(str[j]);
      j++;
    }
  return (j);
}

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
  int	i;
  int	k;

  i = k = 0;
  if (buffer == NULL)
    return (buffer);
  if (stock == NULL)
    fill_stock(buffer, stock);
  tmp = stock;
  stock = malloc(my_strlen(buffer) + 1 + (my_strlen(tmp)));
  while (tmp[k] != '\0')
    {
      stock[k] = tmp[k];
      k++;
    }
  free (tmp);
  return (stock);
}

int		fill_stock(char *buffer, char *stock)
{
  int		j;
  static int	k = 0;

  j = 0;
  while (buffer[j] != '\0' && buffer[j] != '\n')
    {
      stock[k] = buffer[j];
      j++;
      k++;
      if (buffer[j] == '\n')
	{
	  stock[k] = '\0';
	  return (1);
	}
    }
  stock[k] = '\0';
  return (0);
}

char	*manhattan_project(char *buffer)
{
  int	i;
  char	*tmp;
  int	k;

  i = k = 0;
  while (buffer[i] != '\n' && buffer[i] != '\0')
    {
      i++;
      if (buffer[i] == '\n')
	{
	  k = i;
	  i = 0;
	  tmp = malloc(READ_SIZE + 1);
	  while (buffer[i] != '\0')
	    {
	      tmp[k] = buffer[i];
	      i++;
	      k++;
	    }
	  tmp[READ_SIZE + 1] = '\0';
	  free (buffer);
	  buffer = tmp;
	}
    }
  return (buffer);
}

char		*get_next_line(const int fd)
{
  static char	*buffer = NULL;
  char		*stock;
  int		k;
  int		j;

  j = k = 0;
  stock = malloc(READ_SIZE + 1);
  if (buffer == NULL)
    {
      buffer = malloc(READ_SIZE + 1);
      if ((j = read(fd, buffer, READ_SIZE)) < 0)
	return (NULL);
      buffer[j] = '\0';
    }
  else
    buffer = manhattan_project(buffer);
  while ((k = fill_stock(buffer, stock) == 0))
    {
      j = read(fd, buffer, READ_SIZE);
      buffer[j] = '\0';
      stock = my_realloc(buffer, stock);
    }
  return (stock);
}

int	main(int ac, char **av)
{
  char	*s;
  int	fd;

  //fd = open(av[1], O_RDONLY);
  while (s = get_next_line(0))
    {
      //s = get_next_line(fd);
      my_putstr(s);
      my_putchar('\n');
      free(s);
    }
  return (0);
}
