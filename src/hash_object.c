#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "hash_object.h"
#include "object.h"
#include "sha1.h"
#include "common.h"
#include "object_store.h"

int hash_object(const char *path,
                    char hex_hash[SHA1_HEX_SIZE])
{
    /*validation*/
    if(path == NULL || hex_hash == NULL)
    {
        return FAILURE;
    }
    
    struct stat st;
    FILE *fp = NULL;
    unsigned char *data = NULL;
    unsigned char *blob = NULL;
    size_t blob_size;
    unsigned char digest[SHA_DIGEST_LENGTH];
    size_t bytes_read;

    /*stat()*/
    if(stat(path,&st) == FAILURE)
    {
        return FAILURE;
    }

    fp = fopen(path,"rb");

    if(fp == NULL)
    {
        return FAILURE;
    }

    if(st.st_size > 0)
    {
        data = malloc(st.st_size);
        if(data == NULL)
        {
            fclose(fp);
            return FAILURE;
        }

        bytes_read = fread(data,1,st.st_size,fp);
        
        if(bytes_read != st.st_size)
        {
            free(data);
            fclose(fp);
            return FAILURE;
        }

    }

    fclose(fp);
    fp = NULL;

    /*build_blob()*/
    if(build_blob(data,st.st_size,&blob,&blob_size) != SUCCESS)
    {
        free(data);
        /*fclose(fp);*/
        return FAILURE;
    }
    /*compute_sha1()*/
    if(compute_sha1(blob,blob_size,digest) != SUCCESS)
    {
        free(blob);
        free(data);
        /*fclose(fp);*/

        return FAILURE;
    }

    /*convert_digest_to_hex*/
    for(int i = 0; i<SHA_DIGEST_LENGTH;i++)
    {
        snprintf(hex_hash + (i*2),3,"%02x",digest[i]);
    }

    /*write_objects to disc*/
    if(write_object(blob,
                    blob_size,
                    hex_hash) != SUCCESS)
    {
        free(blob);
        free(data);

        return FAILURE;
    }

    /*clean_up()*/
    free(blob);
    free(data);
    

    return SUCCESS;
}
