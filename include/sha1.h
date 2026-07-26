#ifndef SHA1_H
#define SHA1_H

#include <stddef.h> /*size_t*/
#include <openssl/sha.h>

int compute_sha1(const unsigned char *data, size_t len, unsigned char digest[SHA_DIGEST_LENGTH]);

#endif
