# Phase 3 — Staging Area (Git Index)

## Objective

Implement Git's staging area by introducing:

- `add` command
- Git index (`.minigit/index`)
- Index management
- Object reuse
- Index update logic

After this phase, MiniGit can stage files similarly to Git.

---

# Overview

Git separates **objects** from the **staging area**.

The object database stores the actual file contents.

The index stores **which version** (SHA-1) of every file is currently staged.

Example:

```
hello.txt
        │
        ▼
SHA1 = 0155cf1965d172dc533725ec829ccd5cece74468
        │
        ▼
.minigit/index

0155cf1965d172dc533725ec829ccd5cece74468 hello.txt
```

The index never stores the file contents.

It only maps

```
filename
        ↓
SHA1
```

---

# Why do we need an Index?

Suppose we have

```
hello.txt
```

After running

```
minigit add hello.txt
```

MiniGit performs two operations.

## Step 1

Create a blob object.

```
blob
 │
 ▼
SHA1
 │
 ▼
.minigit/objects/01/55cf...
```

## Step 2

Record that object inside the staging area.

```
.minigit/index

0155cf1965d172dc533725ec829ccd5cece74468 hello.txt
```

Without the index, MiniGit would know that an object exists but would have no idea which file it belongs to.

---

# Index Format

Current format:

```
<SHA1> <filename>
```

Example:

```
0155cf1965d172dc533725ec829ccd5cece74468 hello.txt
```

Each staged file occupies exactly one line.

---

# Implemented Components

## add.c

Implemented

```
cmd_add()
```

Responsibilities:

- Validate filename
- Create blob object
- Generate SHA-1
- Store compressed object
- Update staging area

Workflow

```
cmd_add()
    │
    ▼
hash_object()
    │
    ▼
write_object()
    │
    ▼
index_add()
```

---

## index.c

Implemented

```
index_add()
```

Responsibilities:

- Create index if missing
- Search existing entries
- Append new files
- Update already staged files

---

# Index Update Logic

Two cases are handled.

---

## Case 1

File not present.

Current index

```
abc123 file1.txt
```

Adding

```
hello.txt
```

Result

```
abc123 file1.txt
0155cf... hello.txt
```

The new entry is appended.

---

## Case 2

File already staged.

Current index

```
0e2d31... hello.txt
```

File modified.

```
hello.txt
```

New SHA

```
0155cf...
```

Result

```
0155cf... hello.txt
```

Only the hash changes.

The filename remains the same.

---

# Updating an Existing Entry

Files cannot be modified in-place easily.

Instead MiniGit performs:

```
Read index
      │
      ▼
Create temporary file
      │
      ▼
Copy every entry
      │
      ▼
Replace matching entry
      │
      ▼
Delete old index
      │
      ▼
Rename temporary file
```

This is the same strategy used by Git for safely updating many metadata files.

---

# Design Decisions

## Content-addressed storage

Objects are identified only by their contents.

Changing even one byte creates a completely different SHA-1.

---

## Immutable objects

Objects are never modified.

If a file changes:

```
Old Object
```

remains

and

```
New Object
```

is created.

Only the index is updated.

---

## Separation of responsibilities

```
cmd_add()
```

coordinates the workflow.

```
hash_object()
```

creates objects.

```
write_object()
```

stores compressed blobs.

```
index_add()
```

maintains the staging area.

Each module has a single responsibility.

---

# Testing

## Build

```
make clean
make
```

---

## Initialize repository

```
./minigit init
```

---

## Create file

```
echo "hello charan" > hello.txt
```

---

## Stage file

```
./minigit add hello.txt
```

Output

```
Added : hello.txt
```

---

## Verify index

```
cat .minigit/index
```

Example

```
0e2d316fa3993959c4e29fdb4a569c68fd70d89e hello.txt
```

---

## Verify object database

```
find .minigit/objects -type f
```

Example

```
.minigit/objects/0e/2d316fa3993959c4e29fdb4a569c68fd70d89e
```

---

## Modify file

```
echo "hello charan update" > hello.txt
```

---

## Stage again

```
./minigit add hello.txt
```

---

## Verify updated index

```
cat .minigit/index
```

Output

```
0155cf1965d172dc533725ec829ccd5cece74468 hello.txt
```

Only one entry exists.

---

## Verify object database

```
find .minigit/objects -type f
```

Example

```
.minigit/objects/58/e75e442d0da8d5dd2c8fb5ac21d017a13efc63
.minigit/objects/0e/2d316fa3993959c4e29fdb4a569c68fd70d89e
.minigit/objects/01/55cf1965d172dc533725ec829ccd5cece74468
```

Notice that previous objects remain unchanged.

---

# Current Repository Layout

```
.minigit/
├── HEAD
├── index
├── refs/
│   └── heads/
│       └── master
└── objects/
    ├── 01/
    ├── 0e/
    └── 58/
```

---

# Phase Summary

Completed:

- Command dispatcher for `add`
- Staging area implementation
- Git index
- Index append logic
- Index update logic
- Temporary file replacement
- Object reuse
- Immutable object storage
- End-to-end staging pipeline

MiniGit can now stage files similarly to Git.

The next phase will use the index to construct **Tree Objects**, representing snapshots of the project's directory structure.
