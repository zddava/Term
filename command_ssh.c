#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>
#include "command.h"
#include "util.h"

#define MIN_LINES 20
#define MIN_COLS 80

void usage_ssh() {}

void help_ssh() {}

int invoke_ssh(int argc, char *argv[])
{
  // 判断有没有带1个参数
  // 带1个参数：读取配置文件，连接对应的主机
  // 带多于1个参数，报错
  // 不带参数，选择
  if (LINES <= MIN_LINES || COLS <= MIN_COLS)
  {
    outputln("ssh: tt must be at least 20 lines by 80 columns");
    return EXIT_FAILURE;
  }

  initscr();

  printw("%d, %d", LINES, COLS);
  move(1, 1);
  printw("%s", "Hello World");

  move(2, 1);
  printw("%s", "Hello World");
  refresh();

  sleep(10);

  endwin();

  // printf("\033[47;31mhello world\033[5m");

  return EXIT_SUCCESS;
}
