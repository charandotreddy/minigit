#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include "init.h"

/*#define MINIGIT_DIR ".minigit"*/
#define DIR_PERMISSION 0755

const char *dirs[] = {".minigit",".minigit/objects", ".minigit/refs", ".minigit/refs/heads"};
#define SIZE (sizeof(dirs)/sizeof(dirs[0]))
#define HEAD_PATH ".minigit/HEAD"
#define CONFIG_PATH ".minigit/config"
#define HEAD_CONTENT "ref: refs/heads/main\n"
#define SUCCESS 0
#define FAILURE -1

int create_directories(void);
int create_head(const char *file_path);
int create_config(const char *file_path);

int cmd_init(void)
{

    if(create_directories() == FAILURE)
    {
       return FAILURE;
    }
    
    if(create_head(HEAD_PATH) != SUCCESS)
    {
        return FAILURE;
    }

    if(create_config(CONFIG_PATH) != SUCCESS)
    {
        return FAILURE;
    }

    printf("Initialized empty MiniGit repository in .minigit\n");
    
    return SUCCESS;
}

int create_directories(void)
{
    int i;

    for(i = 0; i<SIZE; i++)
    {
        if(mkdir(dirs[i],DIR_PERMISSION) == FAILURE)
        {
            if(errno == EEXIST)
            {
                fprintf(stderr,"MiniGit repository already exists.\n");
            }
            else
            {
                perror("mkdir");
            }
            return FAILURE;
        }
    }
    return SUCCESS;
}

int create_head(const char *file_path)
{
    FILE *fp = fopen(file_path, "w");

    if(fp == NULL)
    {
        perror("fopen");
        return FAILURE;
    }

    /*writing on disc can also fail*/
    if(fprintf(fp,"%s",HEAD_CONTENT)<0) 
    {
        perror("fprintf");
        fclose(fp);
        return FAILURE;
    }

    /*as fclose() flushes the buffer data*/
    if(fclose(fp) == EOF)
    {
        perror("fclose");
        return FAILURE;  
    }
    
    
    return SUCCESS;
}

int create_config(const char *file_path)
{
    FILE *fp = fopen(file_path,"w");

    if(fp == NULL)
    {
        perror("fopen");
        return FAILURE;
    }

    if(fclose(fp) == EOF)
    {
        perror("fclose");
        return FAILURE;
    }

    return SUCCESS;
}
