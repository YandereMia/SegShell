#!/bin/bash
TARGET="$HOME/.myshellos/bin"
read -p "file to compile (without cmd_ and .c): " FILE
gcc -O3 "cmd_$FILE.c" -o "$TARGET/$FILE"
echo "Compiled $FILE → $TARGET/$FILE"
