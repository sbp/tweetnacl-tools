CC=gcc
CFLAGS=-O3 -std=c99 -D_POSIX_C_SOURCE=1
TWEETNACLC=randombytes.c tools.c tweetnacl.c
TWEETNACL=$(TWEETNACLC) randombytes.h tools.h tweetnacl.h

all: tweetnacl-decrypt tweetnacl-encrypt tweetnacl-keypair

bin: ;
	mkdir bin

clean: ;
	rm -rf bin

tweetnacl-decrypt: bin $(TWEETNACL) tweetnacl-decrypt.c
	$(CC) $(CFLAGS) $(TWEETNACLC) tweetnacl-decrypt.c \
		-o bin/tweetnacl-decrypt

tweetnacl-encrypt: bin $(TWEETNACL) tweetnacl-encrypt.c
	$(CC) $(CFLAGS) $(TWEETNACLC) tweetnacl-encrypt.c \
		-o bin/tweetnacl-encrypt

tweetnacl-keypair: bin $(TWEETNACL) tweetnacl-keypair.c
	$(CC) $(CFLAGS) $(TWEETNACLC) tweetnacl-keypair.c \
		-o bin/tweetnacl-keypair

test: ;
	mkdir tmp
	bin/tweetnacl-keypair tmp/a.pub tmp/a.sec
	bin/tweetnacl-keypair tmp/b.pub tmp/b.sec
	echo 'Secret message!' > tmp/message
	bin/tweetnacl-encrypt tmp/a.sec tmp/b.pub tmp/message tmp/encrypted
	bin/tweetnacl-decrypt tmp/a.pub tmp/b.sec tmp/encrypted -
	rm -rf tmp
