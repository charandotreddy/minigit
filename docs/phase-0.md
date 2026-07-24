# minigit

MiniGit is a simplified version of git written entirely in C.

---

# phase-0 "Repository Initialization"

## objective
    Implement the "minigit inint" command.

---

## What was implemented.

### created the repository structure

    ```
    .minigit/
    ├── objects/
    ├── refs/
    │   └── heads/
    ├── HEAD
    └── config
    ```
### created repository metadata
    
    -created the `HEAD` file.
    -wrote the following content into`HEAD`:

    ```
    ref: refs/heads/main
    ```

    -created an empty config file.

---

## Design Decisions

    -used helper function instead of one large function.
    -used an array of directory paths and a loop to avoide repetitive code.
    -followed a fail-fast approach.
    -used 'errno' to distinguish 'EEXIST' from other errors.

---

## Concepts Learned

    -`mkdir()`
    -`fopen()`
    -`fprintf()`
    -`fclose()`
    -`perror()`
    -`errno`
    -File permissions.
    -Directory hierarchy.
    -error handling in file operations.

---

## Current Status

    -Repository initialization (`.minigit init`) is implemented successfully.
