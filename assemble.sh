#!/bin/bash

# ======================================================
# Takes in an assembly file, assembles into a binary and
# an lst file, then creates a text file from the hexdump
# * assumes dasm is in the current directory
# ======================================================

if [ $# -ne 1 ]; then
    echo "Usage: assemble.sh <asm_file_path>"
    exit 1
fi

binary_file_name="hexfile.out"
list_file_name="hexfile.lst"
text_file_name="hexfile.txt"

# -f3 : no header
# -o : binary file name
# -l : list file name
./dasm/dasm $1 -f3 -o$binary_file_name -l$list_file_name

if [ $? -eq 0 ]; then
    hexdump -e '16/1 "%02X " "\n"' $binary_file_name > $text_file_name
else
    echo "Error assembly $?"
fi
