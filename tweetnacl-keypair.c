#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "randombytes.h"
#include "tweetnacl.h"

// http://stackoverflow.com/a/1921557
typedef enum { false, true } bool;

bool file_exists(char arg[]) {
    // http://stackoverflow.com/a/230068
    // Not perfect, because e.g. it won't allow the use of /dev/stdout
    if (access(arg, F_OK) != -1) {
        fprintf(stderr, "Error: File already exists: <%s>\n", arg);
        return true;
    }
    return false;
}

void output_key(char arg[], unsigned char key[], int key_size) {
    FILE *out;

    // http://stackoverflow.com/a/8004250
    if (strcmp(arg, "-") == 0) {
        out = stdout;
    } else {
        // http://stackoverflow.com/a/230581
        int fd = open(arg, O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
        if (fd < 0) {
            fprintf(stderr, "Error: Could not write to <%s>\n", arg);
            exit(1);
        }
        // http://stackoverflow.com/a/1941472
        out = fdopen(fd, "wb");
    }

    if (out == stdout) {
        for (int i = 0; i < key_size; i++) {
            printf("%02x", key[i]);
        }
        printf("\n");
    } else {
        for (int i = 0; i < key_size; i++) {
            fputc(key[i], out);
        }
        fclose(out);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error: Expected two filenames as arguments\n");
        exit(2);
    }

    unsigned char public_key[crypto_box_PUBLICKEYBYTES];
    unsigned char secret_key[crypto_box_SECRETKEYBYTES];
    crypto_box_keypair(public_key, secret_key);

    bool one_exists = file_exists(argv[1]);
    bool two_exists = file_exists(argv[2]);
    if (one_exists || two_exists) exit(1);

    output_key(argv[1], public_key, crypto_box_PUBLICKEYBYTES);
    output_key(argv[2], secret_key, crypto_box_SECRETKEYBYTES);

    return 0;
}
