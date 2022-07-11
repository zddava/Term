#include <stdlib.h>

void usage();
int invoke(char *command, int argc, char *argv[]);

// help
void usage_help();
void help_help();
int invoke_help(int argc, char *argv[]);

// pack
void usage_pack();
void help_pack();
int invoke_pack(int argc, char *argv[]);

// unpack
void usage_unpack();
void help_unpack();
int invoke_unpack(int argc, char *argv[]);

// ssh
void usage_ssh();
void help_ssh();
int invoke_ssh(int argc, char *argv[]);

#define EXIT_WRONG_USAGE 2
#define EXIT_NEED_HELP 3
