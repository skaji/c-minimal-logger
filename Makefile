WARN = -Wall -Wextra -Werror

ifeq ($(LOG_PRINT_PID), 1)
	DEFINE = -DLOG_PRINT_PID
endif

example: example.o
	gcc -o example example.o

example.o: example.c logger.h
	gcc $(WARN) $(DEFINE) -c example.c

clean:
	git clean -xfd
