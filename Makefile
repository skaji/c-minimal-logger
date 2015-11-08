ifeq ($(LOG_PRINT_PID), 1)
	DEFINE = -DLOG_PRINT_PID
endif

example: example.o
	gcc -o example example.o

example.o: example.c
	gcc $(DEFINE) -c example.c

clean:
	git clean -xfd
