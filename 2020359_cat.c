#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[512];


void
cat(int fd)
{
  int n;
  int c=1;
  while((n = read(fd, buf, sizeof(buf))) > 0) {
    printf("%d\t",c);
    for (int i=0;i<n;i++)
    { 
      printf("%c",buf[i]);
      if(buf[i]=='\n')
      {
        c+=1;
        if(i<n-1)
        {
        printf("%d\t",c);
        }
      }
    }
}
}


int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    cat(0);
    exit(0);
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      fprintf(2, "cat: cannot open %s\n", argv[i]);
      exit(1);
    }

    cat(fd);
    close(fd);
  }
  exit(0);
}
