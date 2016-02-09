#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  dev_t         dev;
  int           error;
  char          path[] = "/dev/Kiboard";
  mode_t        mode;
  
  mode = S_IFCHR | 0660;
  dev = makedev(333, 0);
  error = mknod(path, mode, dev);
  if (error < 0)
    {
      printf("mknod: node cannot be creat\n");
      return (0);
    }
  printf("Create /dev/Kiboard\n");
  return (0);
}
