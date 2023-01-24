#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

#include "6502_decode.h"

/*
    -- Helpful Docs --
    http://6502.org/users/obelisk/
    https://llx.com/Neil/a2/opcodes.html
    https://wiki.cdot.senecacollege.ca/wiki/6502_Addressing_Modes
    http://www.emulator101.com/6502-addressing-modes.html
    https://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
    wiki.nesdev.com/w/index.php/Status_flags

    -- Online assembler --
    https://www.masswerk.at/6502/assembler.html

    -- Python assmbler --
    https://github.com/SYSPROG-JLS/6502Asm

    -- Assembly examples --
    https://skilldrick.github.io/easy6502/
*/

void reset() {
    // set init vector to rom address - 0xA000
    writeMemory(0xFFFC, (Byte)ROM_START);
    writeMemory(0xFFFD, ROM_START >> 8);
    // set BRK vector - 0xFFFA -> calls printRegisters and Exits
    writeMemory(0xFFFE, 0xFA);
    writeMemory(0xFFFF, 0xFF);
    writeMemory(0xFFFA, 0xFF);
    // intialize registers
    registers.PC = readMemory(0xFFFC) | (readMemory(0xFFFD) << 8);
    registers.SP = 0xFF;
}

void readROM(int startAddress, char* filePath) {
    // get file stats
    struct stat fileStats;
    if (stat(filePath, &fileStats) == -1) {
        throwError("ROM File Not Found");
    }
    // read file into ROM space
    FILE* filePointer = fopen(filePath, "rb");
    fread(&ram[startAddress], fileStats.st_size, 1, filePointer);
    fclose(filePointer);
}

int main() {
    reset();
    readROM(ROM_START, "./hexfile.out");

    while (true) {
        executeInstruction(fetchInstruction());
    }
}
