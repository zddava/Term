#include <stdio.h>
#include "param.h"

#define ENUM_COMMAND_TYPE_CASE(x)     case x: return(#x);

inline char *command_type_to_string(enum COMMAND command)
{
  switch(command)
  {
    ENUM_COMMAND_TYPE_CASE(PACK)
    ENUM_COMMAND_TYPE_CASE(UNPACK)
    ENUM_COMMAND_TYPE_CASE(SSH)
  }

  return "none";
}

inline char *command_str(enum COMMAND cmd)
{
  switch(cmd)
  {
    ENUM_COMMAND_TYPE_CASE(PACK)
    ENUM_COMMAND_TYPE_CASE(UNPACK)
    ENUM_COMMAND_TYPE_CASE(SSH)
  }

  return "none";
}

void list_commands()
{

}
