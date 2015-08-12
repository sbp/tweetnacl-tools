#include <stdio.h>
#include <string.h>

#include "randombytes.h"
#include "tools.h"
#include "tweetnacl.h"

void output_key(char filename[], unsigned char key[], int key_size) {
    // http://stackoverflow.com/a/8004250
    if (strcmp(filename, "-") != 0) {
        FILE *out = create_file(filename);
        fwrite(key, key_size, 1, out);
        fclose(out);
    } else {
        fwrite(bytes_to_hex(key, key_size), key_size * 2, 1, stdout);
        fputs("\n", stdout);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) error(2, "Expected %s filenames as arguments", "2");

    unsigned char public_key[crypto_box_PUBLICKEYBYTES];
    unsigned char secret_key[crypto_box_SECRETKEYBYTES];
    crypto_box_keypair(public_key, secret_key);

    if (file_exists(argv[1])) error(1, "File <%s> exists", argv[1]);
    if (file_exists(argv[2])) error(1, "File <%s> exists", argv[2]);

    output_key(argv[1], public_key, crypto_box_PUBLICKEYBYTES);
    output_key(argv[2], secret_key, crypto_box_SECRETKEYBYTES);

    return 0;
}
