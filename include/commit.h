#ifndef COMMIT_H
#define COMMIT_H

#include "common.h"

int cmd_commit(const char *message);
int get_head_commit(char parent_hash[SHA1_HEX_SIZE]);
int update_head(const char commit_hash[SHA1_HEX_SIZE]);

#endif
