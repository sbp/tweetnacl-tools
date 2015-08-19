# tweetnacl-tools

These are some command line tools for using [TweetNaCl](http://tweetnacl.cr.yp.to/index.html) by Prof Daniel J. Bernstein et al. There are three tools for encryption (make keys, encrypt, and decrypt), and three tools for signatures (make keys, sign, and verify).

Type `make` to compile the tools using `gcc`. The scripts go in `bin/`.

## Encryption

### tweetnacl-keypair

Generates Curve25519 public and secret keys.

Usage:

```shell
$ tweetnacl-keypair public.key secret.key
```

The `public.key` and `secret.key` files will contain 32 bytes each of the public and secret Curve25519 keys respectively. If either or both of the file names are given as `-` then the key will be printed as hexadecimal (64 bytes) with a trailing line feed (`"\n"`) to stdout instead.

### tweetnacl-encrypt

Encrypts data using Curve25519 public and secret keys.

Usage:

```shell
$ tweetnacl-encrypt sender.sec recipient.pub input.txt output.enc
```

The `sender.sec` file is the Curve25519 secret key of the person sending the message. The `recipient.pub` file is the Curve25519 secret key of the person receiving the message. `input.txt` contains the content of the message to be encrypted, and `output.enc` will be created to contain the encrypted message. Using `-` for the output filename will mean hexadecimal encrypted message content will be printed instead to stdout.

### tweetnacl-decrypt

Decrypts data using Curve25519 public and secret keys.

Usage:

```shell
$ tweetnacl-decrypt sender.pub recipient.sec input.enc output.txt
```

The `sender.pub` file is the Curve25519 public key of the person who sent the message. The `recipient.sec` file is the Curve25519 secret key of the person who received the message. `input.enc` contains the encrypted message, and `output.txt` will be created to contain the decrypted message. Using `-` for the output filename will mean that the decrypted message content will be printed to stdout, verbatim.

## Signatures

### tweetnacl-sigpair

Creates public and secret keys suitable for signing.

Usage:

```shell
$ tweetnacl-sigpair sign.pub sign.sec
```

The `sign.pub` file is a public signature key, used for verification; and the `sign.sec` file is the counterpart private signature key, used for signing. Using `-` for either output filename will mean that the key is printed as hexadecimal with a trailing newline to stdout.

### tweetnacl-sign

Signed a message using a secret signing key.

Usage:

```shell
$ tweetnacl-sign sign.sec message.txt message.signed
```

The `sign.sec` secret signature key is used to sign the message in `message.txt` and the output is placed into `message.signed`. If `-` is used for the output filename then it is printed verbatim to stdout.

### tweetnacl-verify

Verifies a signed message relative to its public signature key.

Usage:

```shell
$ tweetnacl-verify sign.pub message.signed message.txt
```

The `sign.pub` public signature key is used to verify the signed message in `message.signed`. If the signature is verified, the message is placed into `message.txt` and the program exits with successful status 0. If the signature is not verified, an error message is printed to stderr and the program exists with the unsuccessful status 0. If the signature is verified and the message output file is `-` then the message is printed to stdout.

## Example

Encrypting and decrypting:

```shell
$ tweetnacl-keypair alice.pub alice.sec
$ tweetnacl-keypair bob.pub bob.sec
$ echo 'Secret message!' > message.txt
$ tweetnacl-encrypt alice.sec bob.pub message.txt secret.enc
$ tweetnacl-decrypt alice.pub bob.sec secret.enc -
Secret message!
```

Signing:

```shell
$ tweetnacl-sigpair sign.pub sign.sec
$ echo 'Verified message!' > message.txt
$ tweetnacl-sign sign.sec message.txt message.signed
$ tweetnacl-verify sign.pub message.signed -
Verified message!
```

## Warning

Only the TweetNaCl portion of this software (`tweetnacl.h` and `tweetnacl.c`) was written by professional cryptographers. Use with caution, and the understanding that no professional security audit of this software has been conducted. This software comes with NO WARRANTY.

Please contribute a professional security audit if you are able to.

## Acknowledgements

This software uses TweetNaCl version 20140427.

This software uses the `devurandom` flavour of the `randombytes` implementation from [NaCl](http://nacl.cr.yp.to/) version 20110221.
