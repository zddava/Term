#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "command.h"
#include "util.h"

// pack
int pack_tar(char *packfile, int delfile, int filenum, char **filenames)
{
  int filearglen = allstrlen(filenum, filenames) + filenum;
  char *fileargs = malloc(filearglen);
  allstrcat(fileargs, " ", filenum, filenames);

  char *command = malloc(strlen("tar -cvf ") + strlen(packfile) + filearglen);
  sprintf(command, "tar -cvf %s%s", packfile, fileargs);

  int retval = system(command);
  free(command);
  free(fileargs);

  if (retval == -1)
  {
    return EXIT_FAILURE;
  }

  if (delfile == 1)
  {
    retval = allremove(filenum, filenames);
    if (retval == EXIT_FAILURE)
    {
      outputln("pack: remove source files error");
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

int pack_targz(char *packfile, int delfile, int filenum, char **filenames)
{
}

int pack_tarbz2(char *packfile, int delfile, int filenum, char **filenames)
{
}

int pack_bz2(char *packfile, int delfile, int filenum, char **filenames)
{
  if (filenum > 1)
  {
    outputln("pack: bz2 file can only pack ONE file at a time");
    return EXIT_WRONG_USAGE;
  }

  // 判断filenames[0] 是否是目录
  // 压缩
  // 改名
}

int pack_gz(char *packfile, int delfile, int filenum, char **filenames)
{
}

int pack_xz(char *packfile, int delfile, int filenum, char **filenames)
{
}

int pack_zip(char *packfile, int delfile, int filenum, char **filenames)
{
}

// unpack
int unpack_tar(char *packfile, int delfile)
{
}

int unpack_targz(char *packfile, int delfile)
{
}

int unpack_tarbz2(char *packfile, int delfile)
{
}

int unpack_bz2(char *packfile, int delfile)
{
}

int unpack_gz(char *packfile, int delfile)
{
}

int unpack_xz(char *packfile, int delfile)
{
}

int unpack_zip(char *packfile, int delfile)
{
}

struct PACKER
{
  char *name;
  int (*packer)(char *, int, int, char **);
  int (*unpacker)(char *, int);
  struct PACKER *child;
};

struct PACKER targz = {
    .name = "tar.gz",
    .packer = pack_targz,
    .unpacker = unpack_targz,
};

struct PACKER tarbz2 = {
    .name = "tar.bz2",
    .packer = pack_tarbz2,
    .unpacker = unpack_tarbz2,
};

struct PACKER packers[] = {
    {
        .name = "tar",
        .packer = pack_tar,
        .unpacker = unpack_tar,
    },
    {
        .name = "tgz",
        .packer = pack_targz,
        .unpacker = unpack_targz,
    },
    {
        .name = "bz2",
        .packer = pack_bz2,
        .unpacker = unpack_bz2,
        .child = &tarbz2,
    },
    {
        .name = "gz",
        .packer = pack_gz,
        .unpacker = unpack_gz,
        .child = &targz,
    },
    {
        .name = "xz",
        .packer = pack_xz,
        .unpacker = unpack_xz,
    },
    {
        .name = "zip",
        .packer = pack_zip,
        .unpacker = unpack_zip,
    },
};

struct PACKER *get_packer(char *packfile)
{
  char suffix[10];
  char *filename = mallocex(strlen(packfile));
  if (filename == NULL)
  {
    exit(EXIT_FAILURE);
  }

  int ret = filesuffix(packfile, suffix, filename);
  if (ret == EXIT_SUCCESS)
  {
    for (int i = 0; i < sizeof(packers) / sizeof(struct PACKER); i++)
    {
      if (strcmp(suffix, packers[i].name) != 0)
      {
        continue;
      }

      if (packers[i].child != NULL)
      {
        struct PACKER *packer_info = get_packer(filename);
        if (packer_info != NULL)
        {
          free(filename);
          return packer_info;
        }
      }

      free(filename);
      return &packers[i];
    }
  }
  else
  {
    free(filename);
    return NULL;
  }

  free(filename);
  return NULL;
}

void usage_pack()
{
  outputln("Usage: t pack [-d] -f packfile.(tar|tar.gz|tgz|tar.bz2|bz2|gz|xz|zip) file1[,file2,file3...]");
}

void usage_unpack()
{
  outputln("Usage: t unpack [-d] packfile.(tar|tar.gz|tgz|tar.bz2|bz2|gz|xz|zip)");
}

void help_pack()
{
  outputln("pack files use multiple formats");
  outputln("-d: whether del the source files after pack");
  outputln("-f: specify the pack destination file");
  outputln("support tar, tar.gz, tgz, tar.bz2, bz2, gz, xz, zip");
}

void help_unpack()
{
  outputln("unpack files use multiple formats");
  outputln("-d: whether del the source files after unpack");
  outputln("support tar, tar.gz, tar.bz2, bz, bz2, gz, xz, zip");
}

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

  if (packfile == NULL)
  {
    outputln("pack: pack file (-f) must be specified");
    return EXIT_WRONG_USAGE;
  }

  if (optind == argc)
  {
    outputln("pack: source files must be specified");
    return EXIT_WRONG_USAGE;
  }

  char **filenames = (char **)mallocex((argc - optind) * sizeof(char *));
  if (filenames == NULL)
  {
    return EXIT_FAILURE;
  }

  for (int i = optind; i < argc; i++)
  {
    filenames[i - optind] = argv[i];
  }

  if (anystrcmp(argc - optind, filenames) == 0)
  {
    outputln("pack: packed files can't be duplicated");
    return EXIT_WRONG_USAGE;
  }

  struct PACKER *packer_info = get_packer(packfile);
  if (packer_info == NULL)
  {
    outputln("pack: packing file format is not supported");
    free(filenames);
    return EXIT_WRONG_USAGE;
  }

  int ret = (packer_info->packer(packfile, delfile, argc - optind, filenames));

  free(filenames);
  return ret;
}

int invoke_unpack(int argc, char *argv[])
{
  char optstr[] = "d";
  int c;

  int delfile = 0;

  while ((c = getopt(argc, argv, optstr)) != -1)
  {
    switch (c)
    {
    case 'd':
      delfile = 1;
      break;
    case '?':
      return EXIT_WRONG_USAGE;
    }
  }

  if (optind == argc)
  {
    outputln("unpack: unpack file must be specified");
    return EXIT_WRONG_USAGE;
  }

  if (argc - optind > 1)
  {
    outputln("unpack: support only ONE unpack file");
    return EXIT_WRONG_USAGE;
  }

  char *unpackfile = argv[optind];

  struct PACKER *packer_info = get_packer(unpackfile);
  if (packer_info == NULL)
  {
    outputln("unpack: unpack file format is not supported");
    return EXIT_WRONG_USAGE;
  }

  return (packer_info->unpacker(unpackfile, delfile));
}
