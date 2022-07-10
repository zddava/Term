#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "command.h"
#include "util.h"

void usage_pack()
{
  outputln("Usage: t pack [-d] -f FILENAME.[tar|tar.gz|tar.bz2|gz|bz2|zip|xz|bz] ...");
  // -d 删除源文件
}

void usage_unpack() {}

void help_pack() {}

void help_unpack() {}

int invoke_pack(int argc, char *argv[])
{
  char optstr[] = "df:";
  int c;

  int delfile = 0;
  char *packfile = NULL;

  while ((c = getopt(argc, argv, optstr)) != -1)
  {
    switch (c)
    {
    case 'd':
      delfile = 1;
      break;
    case 'f':
      packfile = optarg;
      break;
    case '?':
      return EXIT_WRONG_USAGE;
    }
  }

  char suffix[10];
  char *filename = malloc(strlen(packfile));
  if (filename == NULL)
  {
    return EXIT_FAILURE;
  }

  int ret = filesuffix(packfile, suffix, filename);
  if (ret == EXIT_SUCCESS)
  {
    outputln("%s", filename);
    outputln("%s", suffix);
  }
  else
  {
  }

  free(filename);
}

int invoke_unpack(int argc, char *argv[]) {}
