#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include "util.h"

void *mallocex(size_t size)
{
    void *p = malloc(size);
    if (p == NULL)
    {
        outputln("memory allocate error");
    }
    return p;
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

int anystrcmp(int num, char *strs[])
{
    if (num == 1)
    {
        return 1;
    }

    for (int i = 0; i < num; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (strcmp(strs[i], strs[j]) == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}

char *allstrcat(char *dest, char *dep, int num, char *strs[])
{
    for (int i = 0; i < num; i++)
    {
        strcat(dest, dep);
        strcat(dest, strs[i]);
    }

    return dest;
}

int allstrlen(int num, char *strs[])
{
    int len = 0;
    for (int i = 0; i < num; i++)
    {
        len += strlen(strs[i]);
    }

    return len;
}

int allremove(int num, char *filenames[])
{
    int retval = EXIT_SUCCESS;
    for (int i = 0; i < num; i++)
    {
        if (remove(filenames[i]) == -1)
        {
            retval = EXIT_FAILURE;
        }
    }

    return retval;
}

int fileexists(char *filename)
{
    if (access(filename, F_OK) != 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int allfileexist(int num, char *filenames[])
{
    for (int i = 0; i < num; i++)
    {
        if (access(filenames[i], F_OK) != 0)
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int isfolder(char *filename)
{
    struct stat stat_buff;
    stat(filename, &stat_buff);

    return S_ISDIR(stat_buff.st_mode);
}
