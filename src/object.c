#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "common.h"

int build_blob(const unsigned char *data,
                size_t data_size,
                unsigned char **blob,
                size_t *blob_size)
{
    if((data_size > 0) && data == NULL || blob == NULL || blob_size == NULL)
    {
        return FAILURE;
    }

    size_t header_size,total_size;

    header_size = snprintf(NULL,
                            0,
                            "blob %zu",
                            data_size)
                            + 1;

    total_size = header_size + data_size;

    *blob = malloc(total_size);
    
    if(*blob == NULL)
    {
        return FAILURE;
    }

    snprintf((char *)*blob,header_size,"blob %zu",data_size);
    
    memcpy(*blob + header_size,
            data,
            data_size);

    *blob_size = total_size;

    return SUCCESS;
}
