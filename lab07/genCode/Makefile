all: main.exe

main.exe: main.o variabiliglobali.o
	gcc -ansi -Wpedantic -o main.exe main.o variabiliglobali.o

main.o: main.c variabiliglobali.h define.h
	gcc -c -ansi -Wpedantic main.c

variabiliglobali.o: variabiliglobali.c
	gcc -c -ansi -Wpedantic variabiliglobali.c

variabiliglobali.c: define.h
	./creaC.sh

variabiliglobali.h: define.h
	./creaH.sh

clean:
	rm *.exe *.o
