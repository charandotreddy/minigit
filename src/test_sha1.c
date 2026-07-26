#include <stdio.h>
#include <string.h>
#include "sha1.h"
#include "common.h"

int main(void)
{
    const unsigned char data[] = "Hello";
    unsigned char digest[SHA_DIGEST_LENGTH];

    if(compute_sha1(data,
                        strlen((const char *)data),
                            digest) != SUCCESS)
    {
        fprintf(stderr,"SHA-1 computation failed\n");
        return FAILURE;
    }

    for(int i = 0; i<SHA_DIGEST_LENGTH; i++)
    {
        printf("%02x",digest[i]);
    }

    printf("\n");

    return SUCCESS;
}
