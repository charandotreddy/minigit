#include <stdio.h>

#include "write_tree.h"
#include "tree.h"
#include "common.h"


int cmd_write_tree(void)
{
    char hex_hash[SHA1_HEX_SIZE];

    if(write_tree(hex_hash) != SUCCESS)
    {
        return FAILURE;
    }

    printf("%s\n",hex_hash);
    
    return SUCCESS;
}
