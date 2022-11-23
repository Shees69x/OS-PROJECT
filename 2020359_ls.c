#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
char*fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path)+1; p >= path+1 && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p)+1);
  memset(buf+strlen(p)+1, ' ', DIRSIZ-strlen(p)+1);
  return buf;
}

void
lsn(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls Error: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls Error: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_DEVICE:
  case T_FILE:
    printf("%d %s %d %d %l\n",st.ino, fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      printf("%d %s %d %d %d\n",st.ino, fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  close(fd);
}

void ls(char*path)
{
char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_DEVICE:
  case T_FILE:
    printf("h %s %d %d %l\n",fmtname(path), st.type, st.ino, st.size);
 break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      printf("%s %d %d %d\n",fmtname(buf), st.type, st.ino, st.size);
      }
      break;
      }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;
  char str1[] = "-n";
  for(i = 0; argv[1][i] == str1[i] && argv[1][i] == '\0'; i++);
  if(argv[1][i] == str1[i])  //checking if first argumment is "-n"
   	{

                if(argc < 3){
                 lsn(".");
                 exit(0);
                 }
                for(i=2; i<argc; i++)
                lsn(argv[i]);
                exit(0);
                
        }



	else
   	{
   	        if(argc < 2){
                 ls(".");
                 exit(0);
                 }
                for(i=1; i<argc; i++)
                ls(argv[i]);
                exit(0);
	}


  return 0;
}
