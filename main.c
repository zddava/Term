#include <stdio.h>
#include "command.h"

// Usage t command [command args]

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    usage();
    return 1;
  }

  char *command = argv[1];
  if (argc > 2) // has command args
  {
  }
  else
  {
  }

  return 0;
}
