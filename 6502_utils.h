#ifndef UTILS_6502_H
#define UTILS_6502_H

#define MAX_MEM 65536
#define true 1
#define false 0
#define ROM_START 0xA000
#define negativeBit 0b10000000
#define overflowBit 0b01000000
#define unusedBit   0b00100000
#define breakBit    0b00010000
#define decimalBit  0b00001000
#define interuptBit 0b00000100
#define zeroBit     0b00000010
#define carryBit    0b00000001

typedef unsigned char Byte;
typedef unsigned short Word;

struct Flags {              // Index:
        Byte C : 1;         // 0
        Byte Z : 1;         // 1
        Byte I : 1;         // 2    
        Byte D : 1;         // 3    
        Byte B : 1;         // 4    
        Byte unused : 1;    // 5
        Byte V : 1;         // 6
        Byte N : 1;         // 7
    };

struct registersStruct {
    Byte A, X, Y, SP;
    Word PC;

    // access individual `flags` or register `PS`
    union {
        Byte PS;
        struct Flags flags;
    };
} registers;

Byte ram[MAX_MEM];


void throwError(char *message) {
    printf("%s\n", message);
    exit(1);
}

Byte readMemory(Word address) {
    assert(address >= 0x00);
    assert(address < MAX_MEM);
    return ram[address];
}

void writeMemory(Word address, Byte value) {
    assert(address >= 0x00);
    assert(address < MAX_MEM);
    ram[address] = value;
}

Byte fetchInstruction() {
    return readMemory(registers.PC++);
}

/* Read Memory Addresses */
Word getAbsoluteAddress() {
    return ((fetchInstruction()) | (fetchInstruction() << 8));
}

Word getAbsoluteIndexedAddress(Byte index) {
    return ((fetchInstruction()) | (fetchInstruction() << 8)) + index;
}

Word getZeroPageAddress() {
    return (0 << 8) | fetchInstruction();
}

Word getZeroIndexedAddress(Byte index) {
    return (0 << 8) | (fetchInstruction() + index);
}

Word getIndexedIndirectAddress(Byte index) {
    Word address = getZeroIndexedAddress(index);
    return readMemory(address) | (readMemory(address + 1) << 8);
}

Word getIndirectIndexedAddress(Byte index) {
    Word address = getZeroPageAddress();
    return (readMemory(address) | (readMemory(address + 1) << 8)) + index;
}

/* Read Memory Values */
Byte getImmediateValue() {
    return fetchInstruction();
}

Byte getAbsoluteValue() {
    return readMemory(getAbsoluteAddress());
}

Byte getAbsoluteIndexedValue(Byte index) {
    return readMemory(getAbsoluteIndexedAddress(index));
}

Byte getZeroPageValue() {
    return readMemory(getZeroPageAddress());
}

Byte getZeroIndexedValue(Byte index) {
    return readMemory(getZeroIndexedAddress(index));
}

Byte getIndexedIndirectValue(Byte index) {
    return readMemory(getIndexedIndirectAddress(index));
}

Byte getIndirectIndexedValue(Byte index) {
    return readMemory(getIndirectIndexedAddress(index));
}

/* Stack */
void pushByteToStack(Byte value) {
    Word address = registers.SP-- | 0x0100;
    assert(address < 0x0200);
    assert(address >= 0x0100);
    writeMemory(address, value);
}

Byte popByteFromStack() {
    Word address = ++registers.SP | 0x0100;
    assert(address < 0x0200);
    assert(address >= 0x0100);
    return readMemory(address);
}

void pushPCtoStack() {
    pushByteToStack(registers.PC >> 8);
    pushByteToStack((Byte)registers.PC);
}

void popPCfromStack() {
    Byte PCL = popByteFromStack();
    Byte PCH = popByteFromStack();
    registers.PC = (PCH << 8) | PCL;
}

/* Printing */
void printByteBinary(Byte n) {
    for (int i = sizeof(n) * 7; i >= 0; i--) {
        printf("%d", (n & (1 << i)) >> i);
    }
    printf("\n");
}

void printWordBinary(Word n) {
    for (int i = sizeof(n) * 7; i >= 0; i--) {
        printf("%d", (n & (1 << i)) >> i);
    }
    printf("\n");
}

void printMemory(Word startAddress, int length) {
    startAddress = startAddress / 16 * 16;
    length = (length + 16) / 16 * 16;

    for (int row = 0; row < length / 0x10; row++) {
        printf("%04x:  ", startAddress);
        for (int address = startAddress; address < startAddress + 0x10; address++) {
            printf("%02x ", readMemory(address));
        }
        printf("\n");
        startAddress += 0x10;
    }
}

void printRegisters() {
    printf("A:  %04x ", registers.A);
    printByteBinary(registers.A);
    printf("X:  %04x ", registers.X);
    printByteBinary(registers.X);
    printf("Y:  %04x ", registers.Y);
    printByteBinary(registers.Y);
    printf("SP: %04x ", registers.SP);
    printByteBinary(registers.SP);
    printf("PC: %04x ", registers.PC);
    printWordBinary(registers.PC);
    printf("PS: %04x ", registers.PS);
    printByteBinary(registers.PS);
    printf("C: %d, Z: %d, I: %d, D: %d, B: %d, V: %d, N: %d\n", 
        registers.flags.C, registers.flags.Z, registers.flags.I, 
        registers.flags.D, registers.flags.B, registers.flags.V, 
        registers.flags.N);
}

#endif