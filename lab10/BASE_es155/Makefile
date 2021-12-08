LIBRARIES=-lpthread
CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L

all: vacche.exe

vacche.exe: vacche.o DBGpthread.o
	gcc -o vacche.exe vacche.o DBGpthread.o ${LIBRARIES}


vacche.o: vacche.c printerror.h DBGpthread.h
	gcc ${CFLAGS} -c vacche.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc -c DBGpthread.c

.PHONY: clean

clean:
	rm -f *.exe *.o
