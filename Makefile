CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -g
LDLIBS = 
talk: talk.o client.o server.o receive.o die.o
talk.o: talk.c
die.o: die.c
receive.o: receive.c
client.o: client.c
server.o: server.c

.PHONY: clean
clean:
	rm -f *.o *.out talk client server core

.PHONY: test-client
test-client: die.o receive.o client.o
	$(CC) $(CFLAGS) -o client die.o receive.o client.o

.PHONY: test-server
test-server: die.o receive.o server.o
	$(CC) $(CFLAGS) -o server die.o receive.o server.o
