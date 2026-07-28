#ifndef OBJECT_H
#define OBJECT_H

#include <stddef.h>

int build_blob(const unsigned char *data,
                size_t data_size,
                unsigned char **blob,
                size_t *blob_size);

#endif
