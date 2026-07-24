#include <stdio.h>
#include <sys/stat.h>

/*#define MINIGIT_DIR ".minigit"*/
#define PERMISSION 0755

const char *dirs[] = {".minigit",".minigit/objects", ".minigit/refs", ".minigit/refs/heads"};
#define SIZE (sizeof(dirs)/sizeof(dirs[0]))
#define HEAD_PATH ".minigit/HEAD"
#define CONFIG_PATH ".minigit/config"
#define HEAD_CONTENT "ref: refs/heads/main\n"
#define SUCCESS 0
#define FAILURE -1

int create_dir(void);
int create_head(const char *file_path);
int create_config(const char *file_path);

int cmd_init(void)
{
    int status;

    status = create_dir();
    if(status == -1)
    {
       return FAILURE;
    }
    
    status = create_head(HEAD_PATH);
    if(status != SUCCESS)
    {
        perror("create_head");
        return FAILURE;
    }

    status = create_config(CONFIG_PATH);

    if(status != SUCCESS)
    {
        perror("create_config");
        return FAILURE;
    }

    printf("Initialized empty mini git repository in .minigit\n");
    
    return SUCCESS;
}

int create_dir(void)
{
    int i,status;

    for(i = 0; i<SIZE; i++)
    {
        status = mkdir(dirs[i],PERMISSION);

        if(status == FAILURE)
        {
            perror("mkdir");
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
        perror("fprintf()");
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
        perror("fclose(fp)");
        return FAILURE;
    }

    return SUCCESS;
}
