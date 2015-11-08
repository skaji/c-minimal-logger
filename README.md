# minimal logger for c

## Usage

```c
// example.c
#include "logger.h"

int main(void) {
  LOG_DEBUG("debug");
  LOG_INFO("hello %s!", "John");
  LOG_ERROR("failed %d tests", 100);
  return 0;
}
```

```
$ ./example
2015-11-08 18:22:53 [INFO] hello John! at example.c line 5
2015-11-08 18:22:53 [ERROR] failed 100 tests at example.c line 6
```
```
$ LOG_DEBUG=1 ./example
2015-11-08 18:23:36 [DEBUG] debug at example.c line 4
2015-11-08 18:23:36 [INFO] hello John! at example.c line 5
2015-11-08 18:23:36 [ERROR] failed 100 tests at example.c line 6
```

## Available macros

* `LOG_DEBUG(const char* fmt, ...)` (prints only if LOG_DEBUG=1)
* `LOG_INFO(const char* fmt, ...)`
* `LOG_WARN(const char* fmt, ...)`
* `LOG_ERROR(const char* fmt, ...)`

## Customize

### change LOG_DEBUG environment variable

```
$ gcc -DLOG_DEBUG_ENV_NAME=\"MY_DEBUG\" -o example example.c
$ MY_DEBUG=1 ./example
```

### prints pid

```
$ gcc -DLOG_PRINT_PID -o example example.c
$ ./example
2015-11-08 18:58:28 [INFO][pid 62242] hello John! at example.c line 5
```

# Author

Shoichi Kaji
