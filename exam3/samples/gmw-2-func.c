#include <string.h>
int filter (char * prefix, char extension)
{
  int len = strlen(prefix);
  return (len == 0 || prefix[len-1] < extension);
}
