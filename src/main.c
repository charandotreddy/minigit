#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "init.h"
#include "status.h"
#include "common.h"

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
                "\tstatus\n");
}
