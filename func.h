#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#if defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#define SO 'unix'
#elif _WIN32 || _WIN64
#define SO 'win'
#endif

void clear()
{
#if SO == 'unix'
  system("clear");
#elif SO == 'win'
  system("cls");
#endif
}

void pause(const char *msg)
{
#if SO == 'unix'
  printf("%s", msg);
  fflush(stdout); // Flush the output buffer
  system("read");
#elif SO == 'win'
  printf("%s", msg);
  fflush(stdout); // Flush the output buffer
  system("pause");
#else
  printf("%s", "Unsupported OS");
#endif
}