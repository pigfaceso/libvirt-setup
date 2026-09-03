/* 
   TOCTOU (Time-of-Check to Time-of-Use) concept
*/
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {

  char *file = "/tmp/target";

  if (access(file, W_OK) != 0) {
    exit(1);
  }

  symlink(file, "file");

  int fd = open(file, O_WRONLY);
  
  void *buffer = "password123456\n";
  write(fd, buffer, strlen(buffer));

  close(fd);

  exit(0);
}
