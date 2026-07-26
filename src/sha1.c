#include "sha1.h"
#include "common.h"

int compute_sha1(const unsigned char *data, size_t len, unsigned char digest[SHA_DIGEST_LENGTH])
{
    if(SHA1(data,len,digest) == NULL)
    {
        return FAILURE;   
    }

    return SUCCESS;
}


