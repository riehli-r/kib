#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void    my_putstr(char *str)
{
  while (*str != '\0')
    {
      write(1,str, 1);
      str++;
    }
}

int	main()
{
  int	fd;
  char	read_buff[1];

  if ((fd = open("/dev/Mousetick", O_RDWR)) != 0)
    {
      while (read(fd, read_buff, 1) > 0)
	{
	  if ((unsigned short) *read_buff - 1 < 100)
	    printf("Interruption: %u\n", read_buff);
	}
      my_putstr("Fin de lecture\n");
    }
  else
    my_putstr("Impossible de lire le fichier /dev/Kiboard\n");
  return (0);
}
