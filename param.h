enum COMMAND
{
  PACK=1, UNPACK, SSH
} command;

void usage();

void list_commands();

char *command_str(enum COMMAND cmd);
