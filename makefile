main: main.o table.o entry_key.o
	gcc -o main main.o table.o entry_key.o
main.o: main.c
	gcc -c main.c
table.o: table.c
	gcc -c table.c
entry_key.o: entry_key.c
	gcc -c entry_key.c
clean:
	rm -f main *.o
# End of makefile
