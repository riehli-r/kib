#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  dev_t         dev;
  int           error;
  char          path[] = "/dev/Mousetick";
  mode_t        mode;
  
  mode = S_IFCHR | 0660;
  dev = makedev(332, 0);
  error = mknod(path, mode, dev);
  if (error < 0)
    {
      printf("mknod: node cannot be creat\n");
      return (0);
    }
  printf("Create /dev/Mousetick\n");
  return (0);
}
