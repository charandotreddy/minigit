#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "init.h"
#include "status.h"
#include "common.h"
#include "hash_object.h"
#include "add.h"
#include "write_tree.h"
#include "tree.h"

void print_usage(void);

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        print_usage();
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1],"init") == 0)
    {
        if(argc != 2)
        {
            fprintf(stderr,
                    "Usage: minigit init\n\n");
            print_usage();
            return EXIT_FAILURE;
        }

        return cmd_init();
    }
    else if(strcmp(argv[1],"status") == 0)
    {
        if(argc != 2)
        {
            fprintf(stderr,
                    "Usage: minigit status\n\n");
            print_usage();
            return EXIT_FAILURE;
        }
        return cmd_status();
    }
    else if(strcmp(argv[1],"hash-object") == 0)
    {
        if(argc != 3)
        {
            fprintf(stderr,
                    "Usage: minigit hash-object <filename>\n\n");
            print_usage();
            return EXIT_FAILURE;
        }
        char hex_hash[SHA1_HEX_SIZE];

        if(hash_object(argv[2],hex_hash) != SUCCESS)
        {
            fprintf(stderr,
                    "failed to hash '%s'\n",argv[2]);
            return EXIT_FAILURE;
        }

        printf("%s\n",hex_hash);
        return EXIT_SUCCESS;
    }

    else if(strcmp(argv[1],"add") == 0)
    {
        if(argc <3)
        {
            fprintf(stderr,
                    "Usage: minigit add <filename>\n\n");
                    print_usage();
                    return EXIT_FAILURE;
        }
        for(int i = 2;i<argc;i++)
        {
            if(cmd_add(argv[i]) != SUCCESS)
            {
                return EXIT_FAILURE;
            }
        }
        return EXIT_SUCCESS;
    }

    else if(strcmp(argv[1], "write-tree") == 0)
    {
        if(argc != 2)
        {
            fprintf(stderr,
                    "Usage: minigit write-tree\n");
                    print_usage();
            return EXIT_FAILURE;
        }

        return cmd_write_tree();
    }

    fprintf(stderr,
            "Unknown command: %s\n\n",
            argv[1]);

    print_usage();
    return EXIT_FAILURE;
}

void print_usage(void)
{
    fprintf(stderr,
                "Usage:\n"
                "\tminigit <command>\n\n"
                "Commands:\n"
                "\tinit\n"
                "\tstatus\n"
                "\thash-object <filename>\n"
                "\tadd <filename> ...\n"
                "\t write-tree\n");
}
