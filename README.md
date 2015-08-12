# tweetnacl-tools

These are some command line tools for using [TweetNaCl](http://tweetnacl.cr.yp.to/index.html) by Prof Daniel J. Bernstein et al. The only tool implemented at the moment is `tweetnacl-keypair` which generates Curve25519 public and secret keys.

Type `make` to compile the tools using `gcc`. The scripts go in `bin/`.

## tweetnacl-keypair

Generates Curve25519 public and secret keys.

Usage:

```shell
$ tweetnacl-keypair public.key secret.key
```

The `public.key` and `secret.key` files will contain 32 bytes each of the public and secret Curve25519 keys respectively. If either or both of the file names are given as `-` then the key will be printed as hexadecimal (64 bytes) with a trailing line feed (`"\n"`) to stdout instead.

## Warning

Only the TweetNaCl portion of this library (`tweetnacl.h` and `tweetnacl.c`) was written by professional cryptographers. Use with caution, and the understanding that no professional security audit of this library has been conducted. Please contribute a professional security audit if you are able to.

## Acknowledgements

This library uses the `randombytes` implementation from [@ultramancool/tweetnacl-usable](https://github.com/ultramancool/tweetnacl-usable).
