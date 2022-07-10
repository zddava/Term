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

int filesuffix(char *fullname, char *suffix, char *filename)
{
    if ((NULL == fullname) || (NULL == suffix) || (NULL == filename))
    {
        return EXIT_FAILURE;
    }

    char *index = strrchr(fullname, '.');
    if (NULL == index)
    {
        return EXIT_FAILURE;
    }

    int namelen = strlen(fullname) - strlen(index);
    int extlen = strlen(index) - 1;
    outputln("fulllen: %ld", strlen(fullname));
    outputln("namelen: %d", namelen);
    outputln("extlen: %d", extlen);
    if (extlen > 0)
    {
        memcpy(suffix, index + 1, extlen);
        memcpy(filename, fullname, namelen);
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}
