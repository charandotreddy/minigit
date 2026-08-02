#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "commit.h"
#include "common.h"
#include "tree.h"
#include "sha1.h"
#include "object_store.h"

int cmd_commit(const char *message)
{
    if(message == NULL)
    {
        return FAILURE;
    }

    char tree_hash[SHA1_HEX_SIZE];
    if(write_tree(tree_hash) != SUCCESS)
    {
        return FAILURE;
    }
    
    char parent_hash[SHA1_HEX_SIZE];
    if(get_head_commit(parent_hash) != SUCCESS)
    {
        return FAILURE;
    }

    char commit_buffer[8192];
    size_t commit_size = 0;
    size_t bytes_written;

    bytes_written = snprintf(commit_buffer + bytes_written,
                            sizeof(commit_buffer) - commit_size,
                            "tree %s\n",
                            tree_hash);

    if((int)bytes_written < 0)
    {
        return FAILURE;
    }

    commit_size += bytes_written;
    
    if(parent_hash[0] != '\0')
    {
        bytes_written = snprintf(commit_buffer + bytes_written,
                                sizeof(commit_buffer) - commit_size,
                                "parent %s\n",
                                 parent_hash);

        if((int)bytes_written < 0)
        {
            return FAILURE;
        }

        commit_size += bytes_written;
    }

    bytes_written = snprintf(commit_buffer + bytes_written,
                            sizeof(commit_buffer) - commit_size,
                            "author charandotreddy\n");

    if((int)bytes_written < 0)
    {
        return FAILURE;
    }
    commit_size += bytes_written;


    bytes_written = snprintf(commit_buffer + bytes_written,
                            sizeof(commit_buffer) - commit_size,
                            "committer charandotreddy\n");

    if((int)bytes_written < 0)
    {
        return FAILURE;
    }
    
    commit_size += bytes_written;
    
    bytes_written = snprintf(commit_buffer + bytes_written,
                            sizeof(commit_buffer) - commit_size,
                            "\n%s",
                            message);

    if((int)bytes_written < 0)
    {
        return FAILURE;
    }
    
    commit_size += bytes_written;
    
    /*header*/
    char header[64];

    size_t header_size;
    /*calculating the header size*/
    header_size = snprintf(NULL,
                            0,
                            "commit %zu",
                            commit_size) +1;
    /*building header*/
    if(snprintf(header,
                sizeof(header),
                "commit %zu",
                commit_size) <0)
    {
        return FAILURE;
    }

    size_t object_size = header_size + commit_size;
    unsigned char *object_buffer = NULL;

    object_buffer = malloc(object_size);

    if(object_buffer == NULL)
    {
        return FAILURE;
    }

    memcpy(object_buffer,header,header_size);
    memcpy(object_buffer + header_size, commit_buffer, commit_size);
    
    char hex_hash[SHA1_HEX_SIZE];
    unsigned char digest[SHA_DIGEST_LENGTH];

    if(compute_sha1(object_buffer,
                    object_size,
                    digest) != SUCCESS)
    {
        free(object_buffer);
        return FAILURE;
    }
    
    for(int i = 0; i<SHA_DIGEST_LENGTH;i++)
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
    
    
    if(update_head(hex_hash) != SUCCESS)
    {
        free(object_buffer);
        return FAILURE;
    }

    printf("[%s] %s\n",hex_hash,message);
    free(object_buffer);
    return SUCCESS;
}





int get_head_commit(char parent_commit[SHA1_HEX_SIZE])
{
    if(parent_commit == NULL)
    {
        return FAILURE;
    }

    FILE *fp = NULL;

    fp = fopen(".minigit/refs/heads/main", "r");

    if(fp == NULL)
    {
        parent_commit[0] = '\0';
        return SUCCESS;
    }
    
    char line[SHA1_HEX_SIZE +2];
    
    if(fgets(line,
                sizeof(line),
                fp) == NULL)
    {
        fclose(fp);

        parent_commit[0] = '\0';
        return SUCCESS;
    }

    line[strcspn(line,"\n")] = '\0';
    
    strncpy(parent_commit,
            line,
            SHA1_HEX_SIZE-1);
    parent_commit[SHA1_HEX_SIZE -1] = '\0';

    fclose(fp);

    return SUCCESS;
}


int update_head(const char commit_hash[SHA1_HEX_SIZE])
{
    if(commit_hash == NULL)
    {
        return FAILURE;
    }

    FILE *fp = fopen(".minigit/refs/heads/main", "w");

    if(fp == NULL)
    {
        return FAILURE;
    }

    if(fprintf(fp, "%s\n",commit_hash) < 0)
    {
        fclose(fp);
        return FAILURE;
    }

    fclose(fp);

    return SUCCESS;
}
