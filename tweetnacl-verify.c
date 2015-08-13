#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "tweetnacl.h"

int main(int argc, char *argv[]) {
    if (argc != 4) error(2,
        "Usage: tweetnacl-verify sign.pub message.signed message.txt");

    // This will also erroneously fail if the file "-" exists
    if (file_exists(argv[3])) errorf(1, "File <%s> exists", argv[3]);

    unsigned char public_key[crypto_sign_PUBLICKEYBYTES];
    read_key(argv[1], public_key, crypto_sign_PUBLICKEYBYTES);

    Content c = read_file(argv[2]);
    unsigned char *m = malloc(c.size);
    // printf("%zu\n", c.size);
    unsigned long long msize;
    int result = crypto_sign_open(m, &msize, c.bytes, c.size, public_key);
    free(c.bytes);
    // printf("%i\n", result);
    if (result == -1) error(1, "Signature failed verification");

    if (strcmp(argv[3], "-") != 0) {
        FILE *out = create_file(argv[3]);
        fwrite(m, msize, 1, out);
        fclose(out);
    } else {
        fwrite(m, msize, 1, stdout);
    }

    free(m);
    return 0;
}
