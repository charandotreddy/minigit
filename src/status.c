#include <stdio.h>
#include <sys/stat.h>

#define SUCCESS 0
#define FAILURE -1
#define REPOSITORY_PATH ".minigit"

int repository_exists(void);

int cmd_status()
{
    if(repository_exists() == SUCCESS)
    {
        printf("MiniGit repository detected.\n");
        return SUCCESS;
    }
    else
    {
        fprintf(stderr,
                "fatal: not a minigit repository\n");
        return FAILURE;
    }
}

int repository_exists(void)
{
    struct stat st;

    if(stat(REPOSITORY_PATH, &st) == SUCCESS)
    {
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}
