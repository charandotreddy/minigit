# Phase-2 : Git blob objects and Object storage

## Goal

Implement Git-compitable blob object creation and store compressed objects instide the MiniGit object database.

---

## Feature Implementation
    -Read file content
    -Builtd Git blob (`blob <size>\0<data>`)
    -Generate SHA-1 hash using OpenSSL
    -Converst SHA-1 digest to Hexadecimal
    -Compress blob using zlib
    -Store objects in Git-compitable layout

---

```
.minigit/
|--objects/
    |--<first-2-hash-chars>
        |-- <remaining-38-hash-chars>
```

-Added 'hash-object' command


## Files added:

-src/hash-object.c
-src/object.c
-src/object_store.c

-include/hash-object.h
-include/object.h
-include/object-store.h

## Usage:

<bash\>
    './minigit hash-object hello.txt'


## verification

Check that the object was created:


<bash\>
    'find .minigit/objects -type f'


Example:

<text\>
    '.minigit/objects/58/e75e442d0da8d5dd2c8fb5ac21d017a13efc63'


Verify the object using Git:

<bash\>
    GIT_OBJECT_DIRECTORY=.minigit/objects \
    git cat-file -t 58e75e442d0da8d5dd2c8fb5ac21d017a13efc63


Expected output:

    text
    blob


---

---

## Observations

- Git blob format is:
  
    blob <size>\0<data>
  
- SHA-1 is calculated over the complete blob, not just the file contents.
- Objects are compressed before being stored.
- Object filenames are the SHA-1 hash.
- The first two hash characters form the directory name.
- The remaining 38 characters form the object filename.
- MiniGit objects are compatible with Git.
