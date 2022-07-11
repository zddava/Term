#include <stdlib.h>

void usage();
int invoke(char *command, int argc, char *argv[]);

void usage_help();
void help_help();
int invoke_help(int argc, char *argv[]);

void usage_pack();
void help_pack();
int invoke_pack(int argc, char *argv[]);

void usage_unpack();
void help_unpack();
int invoke_unpack(int argc, char *argv[]);

void usage_ssh();
void help_ssh();
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
