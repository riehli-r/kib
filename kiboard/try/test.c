#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	my_putstr(char *str)
{
  while (*str != '\0')
    {
      write(1,str, 1);
      str++;
    }
}

int			main()
{
  int			fd;
  char			read_buff[1];
  char*			map;
  char*			map_maj;
  int			maj;
  int			caps;
  unsigned short	event;

  maj = 0;
  caps = 0;
  map = "`1234567890-=\b\tqwertyuiop[]\n asdfghjkl;' -=zxcvbnm,./### #######";
  map_maj = "~!@#$%^&*()_+\b\tQWERTYUIOP{}\n ASDFGHJKL:\" ##ZXCVBNM<>?### #######";
  if ((fd = open("/dev/Kiboard", O_RDWR)) != 0)
    {
      while (read(fd, read_buff, 1) > 0)
	{
	  event = (unsigned short) *read_buff - 1;
	  if (event == 65465 && !caps)
	    caps = 1;
	  else if (event == 41)
	    maj = 1;
	  else if (event == 65449)
	    maj = 0;
	  else if (event == 65465 && caps)
	    caps = 0;
	  else if (event < 100 && maj == caps)
	    write(1, &map[event], 1);
	  else if (event < 100 && maj != caps)
	    write(1, &map_maj[event], 1);
	  if (event == 13)
	    my_putstr(" \b");
	}
      my_putstr("Fin de lecture\n");
    }
  else
    my_putstr("Impossible de lire le fichier /dev/Kiboard\n");
  return (0);
}
