#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "tweetnacl.h"

int main(int argc, char *argv[]) {
    if (argc != 4) error(2,
        "Usage: tweetnacl-sign sign.sec message.txt message.signed");

    // This will also erroneously fail if the file "-" exists
    if (file_exists(argv[3])) errorf(1, "File <%s> exists", argv[3]);

    unsigned char secret_key[crypto_sign_SECRETKEYBYTES];
    read_key(argv[1], secret_key, crypto_sign_SECRETKEYBYTES);

    Content c = read_file(argv[2]);
    unsigned char *sm = malloc(c.size + crypto_sign_BYTES);
    unsigned long long ssize;
    crypto_sign(sm, &ssize, c.bytes, c.size, secret_key);
    free(c.bytes);

    if (strcmp(argv[3], "-") != 0) {
        FILE *out = create_file(argv[3]);
        fwrite(sm, ssize, 1, out);
        fclose(out);
    } else {
        fwrite(bytes_to_hex(sm, ssize - c.size), 
            (ssize - c.size) * 2, 1, stdout);
        fputs("\n", stdout);
    }

    free(sm);
    return 0;
}
