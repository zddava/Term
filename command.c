#include <stdio.h>
#include <string.h>
#include "command.h"
#include "util.h"

struct COMMAND commands[] = {
    {
        .command = "help",
        .invoker = invoke_help,
        .helper = help_help,
        .usage = usage_help,
    },
    {
        .command = "pack",
        .invoker = invoke_pack,
        .helper = help_pack,
        .usage = usage_pack,
    },
    {
        .command = "unpack",
        .invoker = invoke_unpack,
        .helper = help_unpack,
        .usage = usage_unpack,
    },
    {
        .command = "ssh",
        .invoker = invoke_ssh,
        .helper = help_ssh,
        .usage = usage_ssh,
    },
    {
        .command = "md5", // md5加密，支持字符串和文件
    },
    {
        .command = "base64", // base64加解密
    },
    {
        .command = "ts", // 时间戳转换
    },
};

int (*get_invoker(char *command))(int, char *[])
{
    for (int i = 0; i < sizeof(commands) / sizeof(struct COMMAND); i++)
    {
        if (strcmp(command, commands[i].command) != 0)
        {
            continue;
        }

        return commands[i].invoker;
    }

    return NULL;
}

struct COMMAND *get_command(char *command)
{
    for (int i = 0; i < sizeof(commands) / sizeof(struct COMMAND); i++)
    {
        if (strcmp(command, commands[i].command) != 0)
        {
            continue;
        }

        return &commands[i];
    }

    return NULL;
}

void usage()
{
    output("Usage: t command(");
    int len = sizeof(commands) / sizeof(struct COMMAND);
    for (int i = 0; i < len; i++)
    {
        output(i < len - 1 ? "%s|" : "%s", commands[i].command);
    }
    outputln(") [command args]");
}

int invoke(char *command, int argc, char *argv[])
{
    struct COMMAND *command_info = get_command(command);
    if (command_info == NULL)
    {
        usage();
        return EXIT_FAILURE;
    }

    int retval = (command_info->invoker)(argc, argv);

    switch (retval)
    {
    case EXIT_WRONG_USAGE:
        (command_info->usage)();
        return EXIT_FAILURE;
    case EXIT_NEED_HELP:
        (command_info->helper)();
        return EXIT_FAILURE;
    default:
        return retval;
    }
}

void usage_help()
{
    output("Usage: t help ");
    int len = sizeof(commands) / sizeof(struct COMMAND);
    for (int i = 0; i < len; i++)
    {
        output(i < len - 1 ? "%s|" : "%s", commands[i].command);
    }
    linefeed();
}

void help_help()
{
    usage_help();
}

int invoke_help(int argc, char *argv[])
{
    switch (argc)
    {
    case 0:
        usage();
        return EXIT_SUCCESS;
    case 1:
    {
        struct COMMAND *command_info = get_command(argv[0]);
        if (command_info == NULL)
        {
            outputln("Command \"%s\" not found!", argv[0]);
            usage_help();
            return EXIT_FAILURE;
        }
        (command_info->helper)();
        return EXIT_SUCCESS;
    }
    default:
        outputln("Wrong parameter!");
        return EXIT_WRONG_USAGE;
    }
}
