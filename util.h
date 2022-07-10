#include <stdio.h>

#define output(format, ...) printf(format, ##__VA_ARGS__);
#define outputln(format, ...)    \
  printf(format, ##__VA_ARGS__); \
  printf("\n");
#define linefeed() printf("\n");

void *mnalloc(int cnt, size_t size);

char *upperstr(char str[]);
char *lowerstr(char str[]);

int filesuffix(char *fullname, char *suffix, char *filename);
