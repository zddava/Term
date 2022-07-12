#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include "util.h"

// Usage t command [command args]

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    usage();
    return EXIT_FAILURE;
  }

  char *command = argv[1];
  int cmd_argc = argc - 1;
  char **cmd_argv = NULL;

  if (argc > 1) // command args
  {
    cmd_argv = (char **)mallocex((argc - 1) * sizeof(char *));
    if (cmd_argv == NULL)
    {
      return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++)
    {
      cmd_argv[i - 1] = argv[i];
    }
  }

  int retval = invoke(command, cmd_argc, cmd_argv);

  if (cmd_argv != NULL)
  {
    free(cmd_argv);
  }

  return retval;
}
