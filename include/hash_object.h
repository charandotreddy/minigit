#ifndef HASH_OBJECT_H
#define HASH_OBJECT_H

#define SHA1_HEX_SIZE 41

int hash_object(const char *path,
                    char hex_hash[SHA1_HEX_SIZE]);


#endif
