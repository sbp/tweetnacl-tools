CC=gcc
CFLAGS=-O3
TWEETNACLC=randombytes.c tweetnacl.c
TWEETNACL=$(TWEETNACLC) randombytes.h tweetnacl.h

all: tweetnacl-keypair

bin: ;
	mkdir bin

clean: ;
	rm -rf bin

tweetnacl-keypair: bin $(TWEETNACL) tweetnacl-keypair.c
	$(CC) $(CFLAGS) $(TWEETNACLC) tweetnacl-keypair.c \
		-o bin/tweetnacl-keypair
