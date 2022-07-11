#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "command.h"
#include "util.h"

// pack
int pack_tar(char *packfile, int delfile, char **files)
{
}

int pack_targz(char *packfile, int delfile, char **files)
{
}

int pack_tarbz2(char *packfile, int delfile, char **files)
{
}

int pack_bz(char *packfile, int delfile, char **files)
{
}

int pack_bz2(char *packfile, int delfile, char **files)
{
}

int pack_gz(char *packfile, int delfile, char **files)
{
}

int pack_xz(char *packfile, int delfile, char **files)
{
}

int pack_zip(char *packfile, int delfile, char **files)
{
}

// unpack
int unpack_tar(char **packfile, int delfile)
{
}

int unpack_targz(char **packfile, int delfile)
{
}

int unpack_tarbz2(char **packfile, int delfile)
{
}

int unpack_bz(char **packfile, int delfile)
{
}

int unpack_bz2(char **packfile, int delfile)
{
}

int unpack_gz(char **packfile, int delfile)
{
}

int unpack_xz(char **packfile, int delfile)
{
}

int unpack_zip(char **packfile, int delfile)
{
}

struct PACKER
{
  char *name;
  int (*packer)(char *, int, char **);
  int (*unpacker)(char *, int);
  struct PACKER children[];
};

struct PACKER packers[] = {
    {
        .name = "tar",
        .packer = pack_tar,
        .unpacker = unpack_tar,
        .children = {
            {
                .name = "tar.gz",
                .packer = pack_targz,
                .unpacker = unpack_targz,
            },
            {
                .name = "tar.bz2",
                .packer = pack_tarbz2,
                .unpacker = unpack_tarbz2,
            },
        },
    },
    // ...
};

struct PACKER *get_packer(char *suffix, char *filaname)
{
}

void usage_pack()
{
  outputln("Usage: t pack [-d] -f filename.(tar|tar.gz|tar.bz2|bz|bz2|gz|xz|zip) file1[,file2,file3...]");
}

void usage_unpack()
{
  outputln("Usage: t unpack [-d] filename.(tar|tar.gz|tar.bz2|bz|bz2|gz|xz|zip)");
}

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

  if (optind == argc)
  {
    outputln("pack: packed files must be specified");
    return EXIT_WRONG_USAGE;
  }

  char **filenames = (char **)acmalloc((argc - optind) * sizeof(char *));
  if (filenames == NULL)
  {
    return EXIT_FAILURE;
  }

  for (int i = optind; i < argc; i++)
  {
    filenames[i - optind] = argv[i];
  }

  char suffix[10];
  char *filename = acmalloc(strlen(packfile));
  if (filename == NULL)
  {
    return EXIT_FAILURE;
  }

  int ret = filesuffix(packfile, suffix, filename);
  if (ret == EXIT_SUCCESS)
  {
    outputln("%s", filename);
    outputln("%s", suffix);
    // TODO 获取PACKER INFO，调用PACKER
    struct PACKER *packer_info = get_packer(suffix, filename);
    if (packer_info == NULL)
    {
      outputln("pack: packing file format is not supported");
      return EXIT_WRONG_USAGE;
    }

    int retval = (packer_info->packer)(packfile, delfile, filenames);
  }
  else
  {
    outputln("pack: unrecognized pack file format");
    return EXIT_FAILURE;
  }
}

int invoke_unpack(int argc, char *argv[]) {}
