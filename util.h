#include <stdio.h>

#define output(format, ...) printf(format, ##__VA_ARGS__);
#define outputln(format, ...)    \
  printf(format, ##__VA_ARGS__); \
  printf("\n");
#define linefeed() printf("\n");

void *mallocex(size_t size);

char *upperstr(char str[]);
char *lowerstr(char str[]);

int filesuffix(char *fullname, char *suffix, char *filename);

int anystrcmp(int num, char *strs[]);

char *allstrcat(char *dest, char *dep, int num, char *strs[]);

int allstrlen(int num, char *strs[]);

int allremove(int num, char *filenames[]);

int fileexists(char *filename);

int allfileexist(int num, char *filenames[]);

int isfolder(char *filename);
