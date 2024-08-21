main: main.o table.o entry_key.o
	gcc -o main main.o table.o entry_key.o
main.o: main.c entries/dns_entry.h table.o entry_key.o
	gcc -c main.c
table.o: table.c table.h
	gcc -c table.c
entry_key.o: entry_key.c entry_key.h
	gcc -c entry_key.c
clean:
	rm -f main *.o
# End of makefile
