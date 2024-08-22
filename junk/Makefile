CC		= gcc
PROG	= testParser 

$(PROG): main.o scanner.o parser.o
	$(CC) -o $(PROG) main.o scanner.o parser.o

main.o : main.c token.h scanner.h parser.h
	$(CC) -c main.c -fno-stack-protector

scanner.o : scanner.c token.h scanner.h symdef.h
	$(CC) -c scanner.c -fno-stack-protector

parser.o : parser.c parser.h token.h 
	$(CC) -c parser.c -fno-stack-protector

.PHONY: clean

clean:
	/usr/bin/rm -rf core $(PROG) *.o
