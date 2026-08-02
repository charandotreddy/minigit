#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"
#include "common.h"
#include "sha1.h"
#include "object_store.h"

int write_tree(char hex_hash[SHA1_HEX_SIZE])
{

    if(hex_hash == NULL)
    {
        return FAILURE;
    }

    FILE *fp = NULL;

    fp = fopen(".minigit/index", "r");
    if(fp == NULL)
    {
        return FAILURE;
    }
    
    char line[512];
    char stored_hash[SHA1_HEX_SIZE];
    char stored_filename[256];

    char tree_buffer[8192];
    size_t tree_size = 0;
    
    /*read index line by line */
    while(fgets(line,sizeof(line),fp) != NULL)
    {
        if(sscanf(line,
                    "%40s %255s",
                    stored_hash,
                    stored_filename) != 2)
        {
            continue;
        }

        /* converting hex SHA1 -> binary SHA1 */

        unsigned char binary_hash[SHA_DIGEST_LENGTH];

        for(int i = 0; i<SHA_DIGEST_LENGTH; i++)
        {
            unsigned int value;
            if(sscanf(&stored_hash[i*2],
                        "%2x",
                        &value) != 1)
            {
                fclose(fp);
                return FAILURE;
            }

            binary_hash[i] = (unsigned char)value;
        }

        /* Build tree entry
         * 100644 <filename>\0<20-byte binary SHA1>"
         */
        size_t entry_size;
        entry_size = snprintf(tree_buffer + tree_size,
                                sizeof(tree_buffer) - tree_size,
                                "100644 %s",
                                stored_filename);
    
        if((int)entry_size < 0)
        {
            fclose(fp);
            return FAILURE;
        }

        if(tree_size + entry_size + 1+ SHA_DIGEST_LENGTH > sizeof(tree_buffer))
        {
            fclose(fp);
            return FAILURE;
        }

        tree_buffer[tree_size + entry_size] = '\0';
        
        memcpy(tree_buffer + 
                tree_size + 
                entry_size + 
                1, 
                binary_hash,
                20);

        tree_size += entry_size + 1+ SHA_DIGEST_LENGTH;
    }
    

    fclose(fp);

    /*objece header*/
    char header[64];

    size_t header_size;
    /*it only counts the header size*/ 
    header_size = snprintf(NULL,
                            0,
                            "tree %zu",
                            tree_size) +
                            1;

    if(snprintf(header,
                sizeof(header),
                "tree %zu",
                tree_size) 
                <0)
    {
        return FAILURE;
    }

    size_t object_size = header_size + tree_size;
    unsigned char *object_buffer = NULL;

    object_buffer = malloc(object_size);
    if(object_buffer == NULL )
    {
        return FAILURE;
    }

    memcpy(object_buffer,header,header_size);
    memcpy(object_buffer+header_size,tree_buffer,tree_size);
   
    unsigned char digest[SHA_DIGEST_LENGTH];

    if(compute_sha1(object_buffer,
                    object_size,
                    digest) != SUCCESS)
    {
        free(object_buffer);
        return FAILURE;
    }

    for(int i=0;i<SHA_DIGEST_LENGTH; i++)
    {
        snprintf(hex_hash + (i*2),
                3,
                "%02x",
                digest[i]);
    }

    if(write_object(object_buffer,
                    object_size,
                    hex_hash) != SUCCESS)
    {
        free(object_buffer);
        return FAILURE;
    }

    free(object_buffer);
    return SUCCESS;
}

int cmd_write_tree(void)
{
    char hex_hash[SHA1_HEX_SIZE];

    if(write_tree(hex_hash) != SUCCESS)
    {
        fprintf(stderr,"Failed to write tree object.\n");
        return FAILURE;
    }
    printf("%s\n",hex_hash);

    return SUCCESS;
}

