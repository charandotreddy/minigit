# phase-1: Command dispatcher and Repository Detection

## Objective

Implement a basic CLI dispatcher and 'status' command

---

## Implemented

    -main.c
    -command dispatching using strcmp()
    -usage/help output
    -module command structure
    -status command
    -repository detection using stat()

---

## Design Decisions

    -each command owns it's own source/header pair
    -main.c only dispatches commands
    -helper functions remains private to their source files
    -fail-fast error handling.

---

## Concepts Learned

    -agrc / argv
    -strcmp()
    -stat()
    -struct stat
    -modular C project layout
    -Makefile basics
