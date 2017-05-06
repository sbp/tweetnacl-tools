#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "tweetnacl.h"

void output_key(char filename[], unsigned char key[], int key_size) {
    if (strcmp(filename, "-") != 0) {
        FILE *out = create_file(filename);
        fwrite(key, key_size, 1, out);
        fclose(out);
     } else {
        fwrite(bytes_to_hex(key, key_size), key_size * 2, 1, stdout);
        fputs("\n", stdout);
     }
}

// derives the public key from a given secret key
int main(int argc, char *argv[]) {
    if (argc != 3) error(2,
        "Usage: tweetnacl-derivepubkey key.sec key.pub");

    unsigned char public_key[crypto_box_PUBLICKEYBYTES];
    unsigned char secret_key[crypto_box_SECRETKEYBYTES];

    read_key(argv[1], secret_key, crypto_box_SECRETKEYBYTES);

    crypto_scalarmult_base(public_key, secret_key);

    output_key(argv[2], public_key, crypto_box_SECRETKEYBYTES);

    return 0;
}

