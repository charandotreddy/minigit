# MiniGit

MiniGit is a Git-inspired version control system implemented in C to understand Git's internal architecture from the ground up. Instead of replicating Git commands directly, this project focuses on recreating Git's core object model, storage mechanism, and repository structure while following a modular, fail-fast implementation strategy.

## Project Goals

- Understand Git internals by implementing them from scratch.
- Learn content-addressable storage using SHA-1.
- Implement Git object types incrementally.
- Build a modular and maintainable C codebase.
- Follow defensive programming and fail-fast error handling.

---

## Current Features

### Repository Initialization

```bash
./minigit init
```

Creates the complete repository structure:

```
.minigit/
├── HEAD
├── index
├── objects/
├── refs/
│   └── heads/
└── config
```

---

### Repository Status

```bash
./minigit status
```

Checks whether the current directory contains a valid MiniGit repository.

---

### Blob Object Creation

```bash
./minigit hash-object <file>
```

- Reads file contents.
- Builds Git-compatible blob objects.
- Generates SHA-1 hashes.
- Compresses objects using zlib.
- Stores objects under:

```
.minigit/objects/xx/yyyyyyyy...
```

---

### Staging Area

```bash
./minigit add <file>
```

Implements Git's staging mechanism.

Features:

- Generates blob objects.
- Updates the index.
- Prevents duplicate entries.
- Replaces outdated hashes when files change.

---

### Tree Object Creation

```bash
./minigit write-tree
```

Builds Git-compatible tree objects from the staging index.

Workflow:

- Reads the index.
- Converts staged SHA-1 hashes into binary.
- Constructs tree entries.
- Creates a tree object.
- Computes SHA-1.
- Stores the object.

---

### Commit Creation

```bash
./minigit commit -m "Commit message"
```

Implements Git-style commit objects.

Workflow:

1. Generate tree object.
2. Read current HEAD.
3. Build commit contents.
4. Create commit object.
5. Compute SHA-1.
6. Store commit object.
7. Update branch reference.

Commit format:

```
tree <tree_hash>
parent <parent_hash>

author charandotreddy
committer charandotreddy

Commit message
```

---

## Design Principles

### Bottom-Up Development

The project is implemented layer by layer:

```
Repository
    ↓
Blob Objects
    ↓
Index
    ↓
Tree Objects
    ↓
Commit Objects
```

Each layer is completed and tested before building the next.

---

### Fail-Fast Error Handling

Every operation validates:

- File operations
- Memory allocation
- SHA-1 computation
- Compression
- Object storage
- Buffer sizes

Any failure immediately aborts the operation to prevent repository corruption.

---

## Technologies

- Language: C
- Cryptography: OpenSSL (SHA-1)
- Compression: zlib
- Build System: Make
- Platform: Linux

---

## Implemented Commands

- `init`
- `status`
- `hash-object`
- `add`
- `write-tree`
- `commit`

---

## Current Project Structure

```
src/
include/
docs/
Makefile
README.md
```

---

## Roadmap

- Log traversal
- Checkout
- Branch management
- Restore
- Diff
- Merge
- Reference handling
- Object traversal
- Pack file exploration

---

## Learning Outcomes

This project focuses on understanding Git's internal architecture rather than simply reproducing its command-line interface. Every feature is implemented from first principles to gain practical knowledge of object storage, hashing, repository management, and version control internals.
