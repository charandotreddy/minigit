#include <stdio.h>

#include "add.h"
#include "hash_object.h"
#include "index.h"
#include "common.h"


int cmd_add(const char *filename)
{
    if(filename == NULL)
    {
        return FAILURE;
    }

    char hex_hash[SHA1_HEX_SIZE];

    if(hash_object(filename,hex_hash) != SUCCESS)
    {
        return FAILURE;
    }

    if(index_add(filename,hex_hash) != SUCCESS)
    {
        return FAILURE;
    }
    
    printf("Added : %s\n",filename);

    return SUCCESS;
}
