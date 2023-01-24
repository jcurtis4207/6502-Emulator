#!/bin/bash

gcc 6502_unit_tests.c -o 6502_unit_tests.bin

if [ $? -eq 0 ]; then
    ./6502_unit_tests.bin
fi
