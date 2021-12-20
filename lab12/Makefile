CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE
LFLAGS=
LIBRARIES=-lpthread

all: 	soccorsi.exe

soccorsi.exe: soccorsi.o DBGpthread.o
	gcc ${LFLAGS} -o soccorsi.exe soccorsi.o DBGpthread.o ${LIBRARIES}

soccorsi.o: soccorsi.c DBGpthread.h printerror.h
	gcc ${CFLAGS} -c soccorsi.c

DBGpthread.o: DBGpthread.c printerror.h
	gcc ${CFLAGS} -c DBGpthread.c

.PHONY:	clean

clean:
	-rm -f soccorsi.o DBGpthread.o soccorsi.exe


