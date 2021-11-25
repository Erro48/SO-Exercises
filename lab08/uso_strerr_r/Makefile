CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L
LIBRARIES=-pthread

all: uso_strerr_r.exe

uso_strerr_r.exe: uso_strerr_r.o
	gcc -o uso_strerr_r.exe uso_strerr_r.o ${LIBRARIES}

uso_strerr_r.o: uso_strerr_r.c
	gcc ${CFLAGS} -c uso_strerr_r.c

.PHONY: clean


clean:
	-rm uso_strerr_r.exe *.o
