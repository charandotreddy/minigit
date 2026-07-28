#include <stdio.h>
#include <string.h>

#include "index.h"
#include "common.h"

int index_add(const char *filename,
                const char hex_hash[SHA1_HEX_SIZE])
{

    /*validation*/
    if(filename == NULL || hex_hash == NULL)
    {
        return FAILURE;
    }

    FILE *fp = NULL;
    FILE *temp_fp = NULL; 
    int file_found = FAILURE;

    /*open/create index*/
    fp = fopen(".minigit/index","a+");
    if(fp == NULL)
    {
        return FAILURE;
    }

    fseek(fp,0,SEEK_SET);

    char line[512];
    char stored_hash[SHA1_HEX_SIZE];
    char stored_filename[256];

    /*read line by line*/

    while(fgets(line,sizeof(line),fp) != NULL)
    {

        if(sscanf(line,
                    "%40s %255s",
                    stored_hash,
                    stored_filename) !=2)
        {
            continue;
        }

        /*
        printf("hash: %s\n",stored_hash);
        printf("file: %s\n",stored_filename);
        */

        if(strcmp(stored_filename,filename) == 0)
        {
            /*printf("FOUND!\n");*/
            file_found = SUCCESS;
            break;
        }
    }

    fclose(fp);

    if(file_found == FAILURE)
    {
        fp = fopen(".minigit/index","a");
        
        if(fp == NULL)
        {
            return FAILURE;
        }
        
        if(fprintf(fp,"%s %s\n",hex_hash,filename) < 0)
        {
            fclose(fp);
            return FAILURE;
        }

        fclose(fp);
    }
    else
    {
        temp_fp = fopen(".minigit/index.tmp", "w");
        
        if(temp_fp == NULL)
        {
            return FAILURE;
        }

        fp = fopen(".minigit/index","r");

        if(fp == NULL)
        {
            fclose(temp_fp);
            return FAILURE;
        }

        while(fgets(line,sizeof(line),fp) != NULL)
        {
            if(sscanf(line,"%40s %255s",stored_hash,stored_filename) != 2)
            {
                continue;
            }

            if(strcmp(stored_filename,filename) == 0)
            {
                if(fprintf(temp_fp,
                            "%s %s\n",
                            hex_hash,
                            filename)<0)
                {
                    fclose(fp);
                    fclose(temp_fp);
                    remove(".minigit/index.tmp");
                    return FAILURE;
                }
            }
            else
            {
                if(fputs(line,temp_fp) == EOF)
                {
                    fclose(fp);
                    fclose(temp_fp);
                    remove(".minigit/index.tmp");
                    return FAILURE;
                }
            }
        }

        fclose(fp);
        fclose(temp_fp);

        if(remove(".minigit/index") != 0)
        {
            remove(".minigit/index.tmp");
            return FAILURE;
        }

        if(rename(".minigit/index.tmp",".minigit/index") != 0)
        {
            remove(".minigit/index.tmp");
            return FAILURE;
        }
    }

    return SUCCESS;
}
