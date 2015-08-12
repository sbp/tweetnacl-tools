# tweetnacl-tools

These are some command line tools for using [TweetNaCl](http://tweetnacl.cr.yp.to/index.html) by Prof Daniel J. Bernstein et al. There is a tool to generate public and secret Curve25519 keys called `tweetnacl-keypair`, one to encrypt data with these keys called `tweetnacl-encrypt`, and one to decrypt data with these keys called `tweetnacl-decrypt`.

Type `make` to compile the tools using `gcc`. The scripts go in `bin/`.

## tweetnacl-keypair

Generates Curve25519 public and secret keys.

Usage:

```shell
$ tweetnacl-keypair public.key secret.key
```

The `public.key` and `secret.key` files will contain 32 bytes each of the public and secret Curve25519 keys respectively. If either or both of the file names are given as `-` then the key will be printed as hexadecimal (64 bytes) with a trailing line feed (`"\n"`) to stdout instead.

## tweetnacl-encrypt

Encrypts data using Curve25519 public and secret keys.

Usage:

```shell
$ tweetnacl-encrypt sender.sec recipient.pub input.txt output.enc
```

The `sender.sec` file is the Curve25519 secret key of the person sending the message. The `recipient.pub` file is the Curve25519 secret key of the person receiving the message. `input.txt` contains the content of the message to be encrypted, and `output.enc` will be created to contain the encrypted message. Using `-` for the output filename will mean hexadecimal encrypted message content will be printed instead to stdout.

## tweetnacl-decrypt

Decrypts data using Curve25519 public and secret keys.

Usage:

```shell
$ tweetnacl-decrypt sender.pub recipient.sec input.enc output.txt
```

The `sender.pub` file is the Curve25519 public key of the person who sent the message. The `recipient.sec` file is the Curve25519 secret key of the person who received the message. `input.enc` contains the encrypted message, and `output.txt` will be created to contain the decrypted message. Using `-` for the output fulename will mean that the decrypted message content will be printed to stdout, verbatim.

## Example

```shell
$ tweetnacl-keypair alice.pub alice.sec
$ tweetnacl-keypair bob.pub bob.sec
$ echo 'Secret message!' > message.txt
$ tweetnacl-encrypt alice.sec bob.pub message.txt secret.enc
$ tweetnacl-decrypt alice.pub bob.sec secret.enc -
Secret message!
```

## Warning

Only the TweetNaCl portion of this software (`tweetnacl.h` and `tweetnacl.c`) was written by professional cryptographers. Use with caution, and the understanding that no professional security audit of this software has been conducted. This software comes with NO WARRANTY.

Please contribute a professional security audit if you are able to.

## Acknowledgements

This software uses TweetNaCl version 20140427.

This software uses the `randombytes` implementation from [@ultramancool/tweetnacl-usable](https://github.com/ultramancool/tweetnacl-usable).
