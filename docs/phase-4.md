# Phase 4 – Tree Object Implementation

## Objective
Implement Git's tree object to represent the contents of the staging area (index).

---

## What was implemented

### 1. Tree Builder
- Implemented `write_tree()`.
- Reads every staged entry from `.minigit/index`.
- Parses:
  - Blob SHA-1
  - Filename

### 2. SHA-1 Conversion
- Converts each 40-character hexadecimal SHA-1 into its 20-byte binary representation.

### 3. Tree Entry Format
Constructs every tree entry in Git's canonical format:

```
100644 <filename>\0<20-byte binary SHA1>
```

### 4. Tree Object
Builds the complete Git tree object:

```
tree <size>\0
<tree entries>
```

### 5. Tree Hash
- Computes SHA-1 of the complete tree object.
- Converts the binary digest into hexadecimal.

### 6. Object Storage
- Reuses the existing object storage layer.
- Compresses the tree object.
- Stores it inside:

```
.minigit/objects/
```

using its SHA-1 as the filename.

---

## Design Decisions

- Reused `compute_sha1()`.
- Reused `write_object()`.
- Followed fail-fast error handling.
- Avoided duplicating compression and storage logic.
- Tree generation is completely independent from object storage.

---

## Git Object Flow

```
Index
   │
   ▼
Tree Entries
   │
   ▼
tree <size>\0
   │
   ▼
Tree Object
   │
   ▼
SHA-1
   │
   ▼
Compressed Object
   │
   ▼
.minigit/objects/
```

---

## Current Project Status

Implemented commands:

- init
- status
- hash-object
- add

Implemented internal modules:

- Blob object creation
- Object storage
- SHA-1 hashing
- Index (staging area)
- Tree object creation

Next Phase:

- Commit object
- HEAD update
- Branch references
