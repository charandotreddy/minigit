# Phase 5 – Commit Object Implementation

## Objective

Implement the `commit` command by creating Git-compatible commit objects and maintaining repository history through the branch reference (`HEAD`).

---

## Features Implemented

### 1. Commit Command

Added support for:

```bash
./minigit commit -m "Commit message"
```

The command:

- Creates a tree object from the staging area.
- Reads the current HEAD commit (if any).
- Builds a commit object.
- Computes its SHA-1.
- Stores the commit object in `.minigit/objects/`.
- Updates the current branch reference.

---

## Commit Object Format

The generated commit follows the same structure used by Git.

Example:

```text
tree <tree_hash>
parent <parent_hash>

author charandotreddy
committer charandotreddy

Initial commit
```

For the first commit, the `parent` field is omitted.

---

## Reading the Parent Commit

Implemented:

```c
get_head_commit()
```

Responsibilities:

- Read `.minigit/refs/heads/main`
- Return the latest commit hash.
- Handle the initial commit by returning an empty parent.

---

## Building Commit Contents

Constructed the commit body using:

```
tree
parent (optional)
author
committer

commit message
```

The commit body is accumulated into an in-memory buffer before hashing.

---

## Creating the Commit Object

Similar to blob and tree objects:

1. Create commit contents.
2. Build object header:

```
commit <size>\0
```

3. Concatenate:

```
header + commit contents
```

---

## SHA-1 Generation

Computed SHA-1 over the complete commit object:

```
commit <size>\0 + commit contents
```

Converted the binary digest into a hexadecimal commit hash.

---

## Object Storage

Stored the commit object using the existing object storage implementation.

Objects are compressed using zlib and written to:

```
.minigit/objects/xx/yyyyyyyy...
```

---

## Updating HEAD

Implemented:

```c
update_head()
```

Responsibilities:

- Open:

```
.minigit/refs/heads/main
```

- Write the latest commit hash.
- Advance the branch to the new commit.

---

## Files Added

### Source

- `src/commit.c`

### Headers

- `include/commit.h`

---

## Learning Outcomes

- Understood Git commit object format.
- Learned parent-child commit relationships.
- Built commit objects compatible with Git's object model.
- Implemented branch reference updates.
- Reused the common object creation pipeline developed in previous phases.

---

## Current MiniGit Commands

- `init`
- `status`
- `hash-object`
- `add`
- `write-tree`
- `commit`

---

## Next Phase

Phase 6 will implement:

```
git log
```

using parent commit traversal starting from `HEAD`.
