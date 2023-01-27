#ifndef INSTRUCTIONS_6502_H
#define INSTRUCTIONS_6502_H

#include "6502_utils.h"

/* Group One */
Byte getGroupOneOperand(Byte addressMode) {
    Byte operand = 0;
    Byte tmp = 0;
    switch(addressMode) {
        case 0b000: // (zero,X)
            operand = getIndexedIndirectValue(registers.X);
            break;
        case 0b001: // zero
            operand = getZeroPageValue();
            break;
        case 0b010: // immediate
            operand = getImmediateValue();
            break;
        case 0b011: // absolute
            operand = getAbsoluteValue();
            break;
        case 0b100: // (zero),y
            operand = getIndirectIndexedValue(registers.Y);
            break;
        case 0b101: // zero,X
            operand = getZeroIndexedValue(registers.X);
            break;
        case 0b110: // absolute,Y
            operand = getAbsoluteIndexedValue(registers.Y);
            break;
        case 0b111: // absolute,X
            operand = getAbsoluteIndexedValue(registers.X);
            break;
        default:
            throwError("Invalid Group 1 addressing mode");
    }
    return operand;
}

void LDA(Byte addressMode) {
    registers.A = getGroupOneOperand(addressMode);
    registers.flags.Z = registers.A == 0;
    registers.flags.N = (registers.A & negativeBit) > 0;
}

void ORA(Byte addressMode) {
    registers.A = registers.A | getGroupOneOperand(addressMode);
    registers.flags.Z = registers.A == 0;
    registers.flags.N = (registers.A & negativeBit) > 0;
}

void AND(Byte addressMode) {
    registers.A = registers.A & getGroupOneOperand(addressMode);
    registers.flags.Z = registers.A == 0;
    registers.flags.N = (registers.A & negativeBit) > 0;
}

void EOR(Byte addressMode) {
    registers.A = registers.A ^ getGroupOneOperand(addressMode);
    registers.flags.Z = registers.A == 0;
    registers.flags.N = (registers.A & negativeBit) > 0;
}

void CMP(Byte addressMode) {
    Byte operand = getGroupOneOperand(addressMode);
    Byte result = registers.A - operand;
    registers.flags.C = registers.A >= operand;
    registers.flags.Z = registers.A == operand;
    registers.flags.N = (result & negativeBit) > 0;
}

void executeADC(Byte operand) {
    Byte input = registers.A;
    Word sum = input + operand + registers.flags.C;
    registers.A = (Byte)sum;
    registers.flags.C = sum > 0xFF;
    registers.flags.Z = registers.A == 0;
    registers.flags.N = (registers.A & negativeBit) > 0;
    registers.flags.V = ((input ^ sum) & (operand ^ sum) & 0x80) != 0;
}

void ADC(Byte addressMode) {
    executeADC(getGroupOneOperand(addressMode));
}

void SBC(Byte addressMode) {
    executeADC(getGroupOneOperand(addressMode) ^ 0xFF);
}

void STA(Byte addressMode) {
    Word address = 0;
    switch(addressMode) {
        case 0b000: // (zero,X)
            address = getIndexedIndirectAddress(registers.X);
            break;
        case 0b001: // zero
            address = getZeroPageAddress();
            break;
        case 0b011: // absolute
            address = getAbsoluteAddress();
            break;
        case 0b100: // (zero),y
            address = getIndirectIndexedAddress(registers.Y);
            break;
        case 0b101: // zero,X
            address = getZeroIndexedAddress(registers.X);
            break;
        case 0b110: // absolute,Y
            address = getAbsoluteIndexedAddress(registers.Y);
            break;
        case 0b111: // absolute,X
            address = getAbsoluteIndexedAddress(registers.X);
            break;
        default:
            throwError("Invalid addressing mode for STA");
    }
    writeMemory(address, registers.A);
}


/* Group Two */
Byte getGroupTwoThreeOperand(Byte addressMode, Byte index) {
    Byte operand = 0;
    switch(addressMode) {
        case 0b000: // immediate
            operand = getImmediateValue();
            break;
        case 0b001: // zero
            operand = getZeroPageValue();
            break;
        case 0b010: // accumulator
            operand = registers.A;
            break;
        case 0b011: // absolute
            operand = getAbsoluteValue();
            break;
        case 0b101: // zero,X
            operand = getZeroIndexedValue(index);
            break;
        case 0b111: // absolute,X : absolute,Y for LDX
            operand = getAbsoluteIndexedValue(index);
            break;
        default:
            throwError("Invalid Group 2 addressing mode");
    }
    return operand;
}

void LDX(Byte addressMode) {
    if (addressMode == 0b010) {
        throwError("Invalid address mode for LDX");
    }
    registers.X = getGroupTwoThreeOperand(addressMode, registers.Y);
    registers.flags.Z = registers.X == 0;
    registers.flags.N = (registers.X & negativeBit) > 0;
}

void ASL(Byte addressMode) {
    if (addressMode == 0b000) {
        throwError("Invalid address mode for ASL");
    }
    Byte operand = getGroupTwoThreeOperand(addressMode, registers.X);
    registers.A = (Byte)(operand << 1);
    registers.flags.C = operand >= 0x80;
    registers.flags.Z = registers.A == 0;
    registers.flags.N = (registers.A & negativeBit) > 0;
}

void LSR(Byte addressMode) {
    if (addressMode == 0b000) {
        throwError("Invalid address mode for LSR");
    }
    Byte operand = getGroupTwoThreeOperand(addressMode, registers.X);
    registers.A = operand >> 1;
    registers.flags.C = operand & 0x01;
    registers.flags.Z = registers.A == 0;
    registers.flags.N = (registers.A & negativeBit) > 0;
}

void ROL(Byte addressMode) {
    if (addressMode == 0b000) {
        throwError("Invalid address mode for ROL");
    }
    Byte operand = getGroupTwoThreeOperand(addressMode, registers.X);
    registers.A = (Byte)((operand << 1) | registers.flags.C);
    registers.flags.C = operand >= 0x80;
    registers.flags.Z = registers.A == 0;
    registers.flags.N = (registers.A & negativeBit) > 0;
}

void ROR(Byte addressMode) {
    if (addressMode == 0b000) {
        throwError("Invalid address mode for ROR");
    }
    Byte operand = getGroupTwoThreeOperand(addressMode, registers.X);
    registers.A = (operand >> 1) | (registers.flags.C << 7);
    registers.flags.C = operand & 0x01;
    registers.flags.Z = registers.A == 0;
    registers.flags.N = (registers.A & negativeBit) > 0;
}

void STX(Byte addressMode) {
    Word address = 0;
    switch(addressMode) {
        case 0b001: // zero
            address = getZeroPageAddress();
            break;
        case 0b011: // absolute
            address = getAbsoluteAddress();
            break;
        case 0b101: // zero,Y
            address = getZeroIndexedAddress(registers.Y);
            break;
        default:
            throwError("Invalid addressing mode for STX");
    }
    writeMemory(address, registers.X);
}

void INC(Byte addressMode) {
    Word address = 0;
    switch(addressMode) {
        case 0b001: // zero
            address = getZeroPageAddress();
            break;
        case 0b011: // absolute
            address = getAbsoluteAddress();
            break;
        case 0b101: // zero,X
            address = getZeroIndexedAddress(registers.X);
            break;
        case 0b111: // absolute,X
            address = getAbsoluteIndexedAddress(registers.X);
            break;
        default:
            throwError("Invalid addressing mode for INC");
    }
    Byte value = (Byte)(readMemory(address) + 1);
    writeMemory(address, value);
    registers.flags.Z = value == 0;
    registers.flags.N = (value & negativeBit) > 0;
}

void DEC(Byte addressMode) {
    Word address = 0;
    switch(addressMode) {
        case 0b001: // zero
            address = getZeroPageAddress();
            break;
        case 0b011: // absolute
            address = getAbsoluteAddress();
            break;
        case 0b101: // zero,X
            address = getZeroIndexedAddress(registers.X);
            break;
        case 0b111: // absolute,X
            address = getAbsoluteIndexedAddress(registers.X);
            break;
        default:
            throwError("Invalid addressing mode for DEC");
    }
    Byte value = (Byte)(readMemory(address) - 1);
    writeMemory(address, value);
    registers.flags.Z = value == 0;
    registers.flags.N = (value & negativeBit) > 0;
}

/* Group Three */
void BIT(Byte addressMode) {
    Byte operand = 0;
    switch(addressMode) {
        case 0b001: // zero
            operand = getZeroPageValue();
            break;
        case 0b011: // absolute
            operand = getAbsoluteValue();
            break;
        default:
            throwError("Invalid addressing mode for BIT");
    }
    Byte result = registers.A & operand;
    registers.flags.Z = result == 0;
    registers.flags.V = (operand & overflowBit) > 0;
    registers.flags.N = (operand & negativeBit) > 0;
}

void executeJump(Byte indirect) {
    if (indirect) {
        Word address = getAbsoluteAddress();
        registers.PC = readMemory(address) | (readMemory(address + 1) << 8);
    } else {
        registers.PC = getAbsoluteAddress();
    }
}

void JMP(Byte addressMode) {
    if (addressMode != 0b011) {
        throwError("Invalid addressing mode for JMP");
    }
    executeJump(true);
}

void JMP_ABS(Byte addressMode) {
    if (addressMode != 0b011) {
        throwError("Invalid addressing mode for JMP absolute");
    }
    executeJump(false);
}

void STY(Byte addressMode) {
    Word address = 0;
    switch(addressMode) {
        case 0b001: // zero
            address = getZeroPageAddress();
            break;
        case 0b011: // absolute
            address = getAbsoluteAddress();
            break;
        case 0b101: // zero,X
            address = getZeroIndexedAddress(registers.X);
            break;
        default:
            throwError("Invalid addressing mode for STY");
    }
    writeMemory(address, registers.Y);
}

void LDY(Byte addressMode) {
    if (addressMode == 0b010) {
        throwError("Invalid address mode for LDY");
    }
    registers.Y = getGroupTwoThreeOperand(addressMode, registers.X);
    registers.flags.Z = registers.Y == 0;
    registers.flags.N = (registers.Y & negativeBit) > 0;
}

void CPY(Byte addressMode) {
    if(addressMode != 0b000 && addressMode != 0b001 && addressMode != 0b011) {
        throwError("Invalid address mode for CPY");
    }
    Byte operand = getGroupTwoThreeOperand(addressMode, 0);
    Byte result = registers.Y - operand;
    registers.flags.C = registers.Y >= operand;
    registers.flags.Z = registers.Y == operand;
    registers.flags.N = (result & negativeBit) > 0;
}

void CPX(Byte addressMode) {
    if(addressMode != 0b000 && addressMode != 0b001 && addressMode != 0b011) {
        throwError("Invalid address mode for CPX");
    }
    Byte operand = getGroupTwoThreeOperand(addressMode, 0);
    Byte result = registers.X - operand;
    registers.flags.C = registers.X >= operand;
    registers.flags.Z = registers.X == operand;
    registers.flags.N = (result & negativeBit) > 0;
}


/* Stack */
void PHA() {
    pushByteToStack(registers.A);
}

void PLA() {
    registers.A = popByteFromStack();
    registers.flags.Z = registers.A == 0;
    registers.flags.N = (registers.A & negativeBit) > 0;
}

void PHP() {
    // B & unused are set in memory
    pushByteToStack(registers.PS | unusedBit | breakBit);
}

void PLP() {
    registers.PS = popByteFromStack();
    registers.flags.B = 0;
    registers.flags.unused = 0;
}


/* Flag */
void CLC() {
    registers.flags.C = 0;
}

void SEC() {
    registers.flags.C = 1;
}

void CLI() {
    registers.flags.I = 0;
}

void SEI() {
    registers.flags.I = 1;
}

void CLV() {
    registers.flags.V = 0;
}

void CLD() {
    registers.flags.D = 0;
}

void SED() {
    registers.flags.D = 1;
}

/* Other */
void INX() {
    registers.X++;
    registers.flags.Z = registers.X == 0;
    registers.flags.N = (registers.X & negativeBit) > 0;
}

void INY() {
    registers.Y++;
    registers.flags.Z = registers.Y == 0;
    registers.flags.N = (registers.Y & negativeBit) > 0;
}

void DEX() {
    registers.X--;
    registers.flags.Z = registers.X == 0;
    registers.flags.N = (registers.X & negativeBit) > 0;
}

void DEY() {
    registers.Y--;
    registers.flags.Z = registers.Y == 0;
    registers.flags.N = (registers.Y & negativeBit) > 0;
}

void TAX() {
    registers.X = registers.A;
    registers.flags.Z = registers.X == 0;
    registers.flags.N = (registers.X & negativeBit) > 0;
}

void TAY() {
    registers.Y = registers.A;
    registers.flags.Z = registers.Y == 0;
    registers.flags.N = (registers.Y & negativeBit) > 0;
}

void TSX() {
    registers.X = registers.SP;
    registers.flags.Z = registers.X == 0;
    registers.flags.N = (registers.X & negativeBit) > 0;
}

void TXA() {
    registers.A = registers.X;
    registers.flags.Z = registers.A == 0;
    registers.flags.N = (registers.A & negativeBit) > 0;
}

void TXS() {
    registers.SP = registers.X;
}

void TYA() {
    registers.A = registers.Y;
    registers.flags.Z = registers.A == 0;
    registers.flags.N = (registers.A & negativeBit) > 0;
}

void NOP() {
    return;
}


/* Branching */
void BEQ() {
    char offset = (char)fetchInstruction();
    if(registers.flags.Z) {
        registers.PC += offset;
    }
}

void BNE() {
    char offset = (char)fetchInstruction();
    if(!registers.flags.Z) {
        registers.PC += offset;
    }
}

void BCS() {
    char offset = (char)fetchInstruction();
    if(registers.flags.C) {
        registers.PC += offset;
    }
}

void BCC() {
    char offset = (char)fetchInstruction();
    if(!registers.flags.C) {
        registers.PC += offset;
    }
}

void BVS() {
    char offset = (char)fetchInstruction();
    if(registers.flags.V) {
        registers.PC += offset;
    }
}

void BVC() {
    char offset = (char)fetchInstruction();
    if(!registers.flags.V) {
        registers.PC += offset;
    }
}

void BMI() {
    char offset = (char)fetchInstruction();
    if(registers.flags.N) {
        registers.PC += offset;
    }
}

void BPL() {
    char offset = (char)fetchInstruction();
    if(!registers.flags.N) {
        registers.PC += offset;
    }
}


/* Subroutines */
void JSR() {
    Word jumpAddress = getAbsoluteAddress();
    pushPCtoStack();
    registers.PC = jumpAddress;
}

void RTS() {
    popPCfromStack();
}

void BRK() {
    // https://www.c64-wiki.com/wiki/BRK
    // PC+1 is pushed onto the stack
    registers.PC++;
    pushPCtoStack();
    // B & unused are set in memory
    pushByteToStack(registers.PS | unusedBit | breakBit);
    registers.flags.B = 1;
    registers.flags.I = 1;
    registers.PC = readMemory(0xFFFE) | (readMemory(0xFFFF) << 8);
}

void RTI() {
    registers.PS = popByteFromStack();
    registers.flags.B = 0;
    registers.flags.unused = 0;
    popPCfromStack();
}

#endif