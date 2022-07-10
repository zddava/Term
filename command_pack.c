#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "command.h"
#include "util.h"

void usage_pack() {}

void usage_unpack() {}

void help_pack() {}

void help_unpack() {}

int invoke_pack(int argc, char *argv[])
{
  char optStr[] = "ab:";
  int c;

  while ((c = getopt(argc, argv, optStr)) != -1)
  {
    printf("optind: %d\n", optind);
    switch (c)
    {
    case 'a':
      printf("-a\n");
      break;
    case 'b':
      printf("-b: %s\n", optarg);
      break;
    case '?':
      printf("arg:%s\n", argv[optopt]);
      break;
    }
  }
}

int invoke_unpack(int argc, char *argv[]) {}
