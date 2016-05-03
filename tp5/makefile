CC=gcc
CFLAGS= -W -Wall -ansi -g

marquage: L_ADJ.o fileCirculaire.o
	$(CC) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o marquage exe

