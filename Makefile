all: sender receiver

CC = gcc
RM = rm -rf
sender : sender.c 
	$(CC) $^ -o $@
receiver : receiver.c
	$(CC) $^ -o $@

clean:
	$(RM) sender receiver
