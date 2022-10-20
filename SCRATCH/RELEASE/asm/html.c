/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : html
 * @created     : Luni Oct 17, 2022 17:24:41 EEST
 */

#include "tiffio.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  fprintf(stderr, "html\n");
  int fd = open("/Users/alex/dev/parcurs/SCRATCH/RELEASE/asm/xxx__",
                O_CREAT | O_RDWR);
  write(fd, "a", 2);
  close(fd);
  TIFF *tif = TIFFOpen(argv[1], "r");
  if (tif) {
    int dircount = 0;
    do {
      dircount++;
    } while (TIFFReadDirectory(tif));
    printf("%d directories in %s\n", dircount, argv[1]);
    TIFFClose(tif);
    return 0;
  }
}
