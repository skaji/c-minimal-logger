/*
The MIT License (MIT)

Copyright (c) 2015 Shoichi Kaji

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

#ifndef LOG_DEBUG_ENV_NAME
  #define LOG_DEBUG_ENV_NAME "LOG_DEBUG"
#endif

#define LOG_DEBUG(...) logger__(__FILE__, __LINE__, 0, __VA_ARGS__)
#define LOG_INFO(...)  logger__(__FILE__, __LINE__, 1, __VA_ARGS__)
#define LOG_WARN(...)  logger__(__FILE__, __LINE__, 2, __VA_ARGS__)
#define LOG_ERROR(...) logger__(__FILE__, __LINE__, 3, __VA_ARGS__)

static void logger__(const char* file,
                     unsigned int line,
                     unsigned int level,
                     const char* fmt,
                     ...)
{
  if (level == 0) {
    char* is_debug = getenv(LOG_DEBUG_ENV_NAME);
    if (is_debug == NULL) {
      return;
    }
  }
  char time_string[30];
  time_t t = time(NULL);
  struct tm *tmp;
  tmp = localtime(&t);
  strftime(time_string, 30, "%Y-%m-%d %H:%M:%S", tmp);
  char line_string[10];
  snprintf(line_string, sizeof line_string, "%d", line);
#ifdef LOG_PRINT_PID
  char pid_string[10];
  snprintf(pid_string, sizeof pid_string, "%d", getpid());
#endif
  size_t len = strlen(time_string)
             + 2
             + 5
#ifdef LOG_PRINT_PID
             + 6
             + strlen(pid_string)
#endif
             + 2
             + strlen(fmt)
             + 4
             + strlen(file)
             + 6
             + strlen(line_string)
             + 1
             + 1; // '\0'
  char *str = (char*)malloc(len);
  if (str == NULL) {
    fprintf(stderr, "failed to malloc");
    return;
  }
  strcpy(str, time_string);
  strcat(str, " [");
  strcat(str, level == 0 ? "DEBUG"
            : level == 1 ? "INFO"
            : level == 2 ? "WARN"
            :              "ERROR");
#ifdef LOG_PRINT_PID
  strcat(str, "][pid ");
  strcat(str, pid_string);
#endif
  strcat(str, "] ");
  strcat(str, fmt);
  strcat(str, " at ");
  strcat(str, file);
  strcat(str, " line ");
  strcat(str, line_string);
  strcat(str, "\n");
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, str, args);
  free(str);
  va_end(args);
}

#endif
