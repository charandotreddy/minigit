#ifndef OBJECT_STORE_H
#define OBJECT_STORE_H

#include <stddef.h>
#include "common.h"

int write_object(const unsigned char *blob,
                size_t blob_size,
                const char hex_hash[SHA1_HEX_SIZE]);

#endif
