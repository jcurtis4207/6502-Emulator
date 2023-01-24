#!/bin/bash

gcc 6502_emulator.c -o 6502_emulator.bin

if [ $? -eq 0 ]; then
    ./6502_emulator.bin
fi
