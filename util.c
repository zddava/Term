#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

void *mnalloc(int cnt, size_t size)
{
    void *p = malloc(cnt * size);
    if (p == NULL)
    {
        outputln("memory allocate error");
    }
}

char *upperstr(char str[])
{
    char *result = str;
    for (; *str != '\0'; str++)
    {
        *str = toupper(*str);
    }

    return result;
}

char *lowerstr(char str[])
{
    char *result = str;
    for (; *str != '\0'; str++)
    {
        *str = tolower(*str);
    }

    return result;
}
