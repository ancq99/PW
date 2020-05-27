all: skorowidz.o tab_dyn.o main.c
	$(CC) tab_dyn.o skorowidz.o main.c -o a.out

tab_dyn.o: tab_dyn.h tab_dyn.c
	$(CC) tab_dyn.c -c -o tab_dyn.o

skorowidz.o: skorowidz.h skorowidz.c tab_dyn.h tab_dyn.c
	$(CC) skorowidz.c -c -o skorowidz.o
