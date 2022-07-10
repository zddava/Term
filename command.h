#include <stdlib.h>

void usage();
void usage_help();
void usage_pack();
void usage_unpack();
void usage_ssh();

void help_help();
void help_pack();
void help_unpack();
void help_ssh();

int invoke(char *command, int argc, char *argv[]);
int invoke_help(int argc, char *argv[]);
int invoke_pack(int argc, char *argv[]);
int invoke_unpack(int argc, char *argv[]);
int invoke_ssh(int argc, char *argv[]);

struct COMMAND
{
  char *command;
  int (*invoker)(int, char *[]);
  void (*helper)(void);
  void (*usage)(void);
};

#define EXIT_WRONG_USAGE 2
#define EXIT_NEED_HELP 3
