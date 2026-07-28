#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <zlib.h>

#include "object_store.h"
#include "common.h"

int write_object(const unsigned char *blob,
                size_t blob_size,
                const char hex_hash[SHA1_HEX_SIZE])
{
    /*validation*/
    if(blob == NULL || blob_size == 0 || hex_hash == NULL)
    {
        return FAILURE;
    }
    
    struct stat st;
    char dir_name[3];
    char file_name[39];
    char dir_path[256];
    char path[256];
    uLongf compressed_size;
    unsigned char *compressed_blob = NULL;
    FILE *fp = NULL;
    size_t bytes_written;

    /*splitting hash*/
    memcpy(dir_name,hex_hash,2);
    dir_name[2] = '\0';

    memcpy(file_name,hex_hash +2 ,38);
    file_name[38] = '\0';
    
    snprintf(dir_path,sizeof(dir_path),".minigit/objects/%s",dir_name);
    snprintf(path,sizeof(path),".minigit/objects/%s/%s",dir_name,file_name);
    
    if(stat(path,&st) == SUCCESS)
    {
        return SUCCESS;
    }

    if(mkdir(dir_path,0777)  == FAILURE)
    {
        if(errno != EEXIST)
        {
            return FAILURE;
        }
    }

    
    compressed_size = compressBound(blob_size);
    compressed_blob = (unsigned char *)malloc(compressed_size);
    if(compressed_blob == NULL)
    {
        return FAILURE;
    }

    if(compress2(compressed_blob,
              &compressed_size,
              blob,
              blob_size,
              Z_BEST_COMPRESSION) != Z_OK)
    {
        free(compressed_blob);
        return FAILURE;
    }

    fp = fopen(path,"wb");

    if(fp == NULL)
    {
        free(compressed_blob);
        return FAILURE;
    }

    bytes_written = fwrite(compressed_blob,1,compressed_size,fp);

    if(bytes_written != compressed_size)
    {
        fclose(fp);
        free(compressed_blob);
        return FAILURE;
    }

    fclose(fp);
    free(compressed_blob);

    return SUCCESS;
}
