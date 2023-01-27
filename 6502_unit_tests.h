#include "6502_utils.h"
#include "6502_instructions.h"

void clearRegisters() {
    registers.A = 0;
    registers.X = 0;
    registers.Y = 0;
    registers.SP = 0;
    registers.PC = 0;
    registers.PS = 0x00;
}


/* Group One */
void unitTestLDA() {
    // Immediate no flags: LDA #0x6C
    registers.PC = 0x300;
    writeMemory(0x300, 0x6C);
    LDA(0b010);
    assert(registers.A == 0x6C);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Immediate Negative flag: LDA #0xF9
    registers.PC = 0x300;
    writeMemory(0x300, 0xF9);
    LDA(0b010);
    assert(registers.A == 0xF9);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Immediate Zero flag: LDA #0x00
    registers.PC = 0x300;
    writeMemory(0x300, 0x00);
    LDA(0b010);
    assert(registers.A == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute: LDA $045B = 0x33
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    LDA(0b011);
    assert(registers.A == 0x33);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,X: LDA $045B (+2)= 0x44
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x44);
    LDA(0b111);
    assert(registers.A == 0x44);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,Y: LDA $045B (+1)= 0x55
    registers.PC = 0x300;
    registers.Y = 0x01;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045C, 0x55);
    LDA(0b110);
    assert(registers.A == 0x55);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero: LDA $08 = 0x11
    registers.PC = 0x300;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x11);
    LDA(0b001);
    assert(registers.A == 0x11);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero,X: LDA $(08 +2) = 0x34
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    LDA(0b101);
    assert(registers.A == 0x34);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // (Zero,X): LDA ($20,4) = LDA $2047 = 0x77
    registers.PC = 0x300;
    registers.X = 0x04;
    writeMemory(0x300, 0x20);
    writeMemory(0x24, 0x74);
    writeMemory(0x25, 0x20);
    writeMemory(0x2074, 0x77);
    LDA(0b000);
    assert(registers.A == 0x77);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // (Zero),Y: LDA ($86),10 = LDA $4028+10 = 0x71
    registers.PC = 0x300;
    registers.Y = 0x10;
    writeMemory(0x300, 0x86);
    writeMemory(0x86, 0x28);
    writeMemory(0x87, 0x40);
    writeMemory(0x4038, 0x71);
    LDA(0b100);
    assert(registers.A == 0x71);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All LDA unit tests passed\n");
}

void unitTestSTA() {
    // Absolute: STA $045B = 0x33
    registers.PC = 0x300;
    registers.A = 0x33;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    STA(0b011);
    assert(readMemory(0x045B) == 0x33);
    clearRegisters();
    // Absolute,X: STA $045B (+2)= 0x44
    registers.PC = 0x300;
    registers.A = 0x44;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    STA(0b111);
    assert(readMemory(0x045D) == 0x44);
    clearRegisters();
    // Absolute,Y: STA $045B (+1)= 0x55
    registers.PC = 0x300;
    registers.A = 0x55;
    registers.Y = 0x01;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    STA(0b110);
    assert(readMemory(0x045C) == 0x55);
    clearRegisters();
    // Zero: STA $08 = 0x11
    registers.PC = 0x300;
    registers.A = 0x11;
    writeMemory(0x300, 0x08);
    STA(0b001);
    assert(readMemory(0x08) == 0x11);
    clearRegisters();
    // Zero,X: STA $(08 +2) = 0x34
    registers.PC = 0x300;
    registers.A = 0x34;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    STA(0b101);
    assert(readMemory(0x0A) == 0x34);
    clearRegisters();
    // (Zero,X): STA ($20,4) = STA $2047 = 0x77
    registers.PC = 0x300;
    registers.A = 0x77;
    registers.X = 0x04;
    writeMemory(0x300, 0x20);
    writeMemory(0x24, 0x74);
    writeMemory(0x25, 0x20);
    STA(0b000);
    assert(readMemory(0x2074) == 0x77);
    clearRegisters();
    // (Zero),Y: STA ($86),10 = STA $4028+10 = 0x71
    registers.PC = 0x300;
    registers.A = 0x71;
    registers.Y = 0x10;
    writeMemory(0x300, 0x86);
    writeMemory(0x86, 0x28);
    writeMemory(0x87, 0x40);
    STA(0b100);
    assert(readMemory(0x4038) == 0x71);
    clearRegisters();
    printf("All STA unit tests passed\n");
}

void unitTestORA() {
    // Immediate no flags: ORA #0x6C = 0x6C | 1 = 0x6D
    registers.PC = 0x300;
    registers.A = 0x01;
    writeMemory(0x300, 0x6C);
    ORA(0b010);
    assert(registers.A == 0x6D);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Immediate Negative flag: ORA #0xF9 = 0xF9 | 2 = 0xFB
    registers.PC = 0x300;
    registers.A = 0x02;
    writeMemory(0x300, 0xF9);
    ORA(0b010);
    assert(registers.A == 0xFB);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Immediate Zero flag: ORA #0x00 = 0x00 | 0 = 0x00
    registers.PC = 0x300;
    registers.A = 0x00;
    writeMemory(0x300, 0x00);
    ORA(0b010);
    assert(registers.A == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute: ORA $045B = 0x33 | 4 = 0x37
    registers.PC = 0x300;
    registers.A = 0x04;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    ORA(0b011);
    assert(registers.A == 0x37);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,X: ORA $045B (+2)= 0x44 | 1 = 0x45
    registers.PC = 0x300;
    registers.A = 0x01;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x44);
    ORA(0b111);
    assert(registers.A == 0x45);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,Y: ORA $045B (+1)= 0x55 | 2 = 0x57
    registers.PC = 0x300;
    registers.A = 0x02;
    registers.Y = 0x01;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045C, 0x55);
    ORA(0b110);
    assert(registers.A == 0x57);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero: ORA $08 = 0x11 | 2 = 0x13
    registers.PC = 0x300;
    registers.A = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x11);
    ORA(0b001);
    assert(registers.A == 0x13);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero,X: ORA $(08 +2) = 0x34 | 1 = 0x35
    registers.PC = 0x300;
    registers.A = 0x01;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    ORA(0b101);
    assert(registers.A == 0x35);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // (Zero,X): ORA ($20,4) = ORA $2047 = 0x44 | 1 = 0x45
    registers.PC = 0x300;
    registers.A = 0x01;
    registers.X = 0x04;
    writeMemory(0x300, 0x20);
    writeMemory(0x24, 0x74);
    writeMemory(0x25, 0x20);
    writeMemory(0x2074, 0x44);
    ORA(0b000);
    assert(registers.A == 0x45);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // (Zero),Y: ORA ($86),10 = ORA $4028+10 = 0x71 | 2 = 0x73
    registers.PC = 0x300;
    registers.A = 0x02;
    registers.Y = 0x10;
    writeMemory(0x300, 0x86);
    writeMemory(0x86, 0x28);
    writeMemory(0x87, 0x40);
    writeMemory(0x4038, 0x71);
    ORA(0b100);
    assert(registers.A == 0x73);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All ORA unit tests passed\n");
}

void unitTestAND() {
    // Immediate no flags: AND #0x6C = 0x6C & 0xAA = 0x28
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0x6C);
    AND(0b010);
    assert(registers.A == 0x28);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Immediate Negative flag: AND #0xF9 = 0xF9 & 0xAA = 0xA8
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0xF9);
    AND(0b010);
    assert(registers.A == 0xA8);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Immediate Zero flag: AND #0x00 = 0x00 & 0xAA = 0x00
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0x00);
    AND(0b010);
    assert(registers.A == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute: AND $045B = 0x33 & 0xAA = 0x22
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    AND(0b011);
    assert(registers.A == 0x22);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,X: AND $045B (+2)= 0x6E & 0xAA= 0x2A
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x6E);
    AND(0b111);
    assert(registers.A == 0x2A);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,Y: AND $045B (+1)= 0x7C & 0xAA = 0x28
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.Y = 0x01;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045C, 0x7C);
    AND(0b110);
    assert(registers.A == 0x28);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero: AND $08 = 0x63 & 0xAA = 0x22
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x63);
    AND(0b001);
    assert(registers.A == 0x22);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero,X: AND $(08 +2) = 0x34 & 0xAA = 0x20
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    AND(0b101);
    assert(registers.A == 0x20);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // (Zero,X): AND ($20,4) = AND $2047 = 0x66 & 0xAA = 0x22
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.X = 0x04;
    writeMemory(0x300, 0x20);
    writeMemory(0x24, 0x74);
    writeMemory(0x25, 0x20);
    writeMemory(0x2074, 0x66);
    AND(0b000);
    assert(registers.A == 0x22);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // (Zero),Y: AND ($86),10 = AND $4028+10 = 0x73 & 0xAA = 0x22
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.Y = 0x10;
    writeMemory(0x300, 0x86);
    writeMemory(0x86, 0x28);
    writeMemory(0x87, 0x40);
    writeMemory(0x4038, 0x73);
    AND(0b100);
    assert(registers.A == 0x22);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All AND unit tests passed\n");
}

void unitTestEOR() {
    // Immediate no flags: EOR #0xEC = 0xEC ^ 0xAA = 0x46
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0xEC);
    EOR(0b010);
    assert(registers.A == 0x46);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Immediate Negative flag: EOR #0x79 = 0x79 ^ 0xAA = 0xD3
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0x79);
    EOR(0b010);
    assert(registers.A == 0xD3);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Immediate Zero flag: EOR #0xAA = 0xAA ^ 0xAA = 0x00
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0xAA);
    EOR(0b010);
    assert(registers.A == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute: EOR $045B = 0x33 ^ 0xAA = 0x99
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    EOR(0b011);
    assert(registers.A == 0x99);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Absolute,X: EOR $045B (+2)= 0x6E ^ 0xAA= 0xC4
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x6E);
    EOR(0b111);
    assert(registers.A == 0xC4);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Absolute,Y: EOR $045B (+1)= 0x7C ^ 0xAA = 0xD6
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.Y = 0x01;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045C, 0x7C);
    EOR(0b110);
    assert(registers.A == 0xD6);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero: EOR $08 = 0x63 ^ 0xAA = 0xC9
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x63);
    EOR(0b001);
    assert(registers.A == 0xC9);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero,X: EOR $(08 +2) = 0x34 ^ 0xAA = 0x9E
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    EOR(0b101);
    assert(registers.A == 0x9E);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // (Zero,X): EOR ($20,4) = EOR $2047 = 0x66 ^ 0xAA = 0xCC
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.X = 0x04;
    writeMemory(0x300, 0x20);
    writeMemory(0x24, 0x74);
    writeMemory(0x25, 0x20);
    writeMemory(0x2074, 0x66);
    EOR(0b000);
    assert(registers.A == 0xCC);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // (Zero),Y: EOR ($86),10 = EOR $4028+10 = 0x73 ^ 0xAA = 0xD9
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.Y = 0x10;
    writeMemory(0x300, 0x86);
    writeMemory(0x86, 0x28);
    writeMemory(0x87, 0x40);
    writeMemory(0x4038, 0x73);
    EOR(0b100);
    assert(registers.A == 0xD9);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    printf("All EOR unit tests passed\n");
}

void unitTestCMP() {
    // Immediate: 01 ? FF = ()
    registers.PC = 0x300;
    registers.A = 0x01;
    writeMemory(0x300, 0xFF);
    CMP(0b010);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Immediate: 7F ? 80 = N
    registers.PC = 0x300;
    registers.A = 0x7F;
    writeMemory(0x300, 0x80);
    CMP(0b010);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Immediate: AA ? 99 = C
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0x99);
    CMP(0b010);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Immediate: AA ? AA = Z,C
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0xAA);
    CMP(0b010);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute: CMP $045B = 0x33 >
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    CMP(0b011);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,X: CMP $045B (+2)= 0x6E >
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x6E);
    CMP(0b111);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,Y: CMP $045B (+1)= 0x7C >
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.Y = 0x01;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045C, 0x7C);
    CMP(0b110);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero: CMP $08 = 0xAA =
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0xAA);
    CMP(0b001);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero,X: CMP $(08 +2) = 0xB4 <
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0xB4);
    CMP(0b101);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // (Zero,X): CMP ($20,4) = CMP $2047 = 0x66 >
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.X = 0x04;
    writeMemory(0x300, 0x20);
    writeMemory(0x24, 0x74);
    writeMemory(0x25, 0x20);
    writeMemory(0x2074, 0x66);
    CMP(0b000);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // (Zero),Y: CMP ($86),10 = CMP $4028+10 = 0xE3 <
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.Y = 0x10;
    writeMemory(0x300, 0x86);
    writeMemory(0x86, 0x28);
    writeMemory(0x87, 0x40);
    writeMemory(0x4038, 0xE3);
    CMP(0b100);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    printf("All CMP unit tests passed\n");
}

void immediateADC(Byte m, Byte n, Byte result, Byte overflow, Byte carry, Byte negative) {
    registers.PC = 0x300;
    registers.A = m;
    writeMemory(0x300, n);
    ADC(0b010);
    assert(registers.A == result);
    assert(registers.flags.C == carry);
    assert(registers.flags.V == overflow);
    assert(registers.flags.N == negative);
    clearRegisters();
}

void unitTestADC() {
    // Immediate 50=10=60
    immediateADC(0x50, 0x10, 0x60, 0, 0, 0);
    // Immediate 50+50=A0, VN
    immediateADC(0x50, 0x50, 0xA0, 1, 0, 1);
    // Immediate 50+90=E0, N
    immediateADC(0x50, 0x90, 0xE0, 0, 0, 1);
    // Immediate 50+D0=20, C
    immediateADC(0x50, 0xD0, 0x20, 0, 1, 0);
    // Immediate D0+10=E0, N
    immediateADC(0xD0, 0x10, 0xE0, 0, 0, 1);
    // Immediate D0+50=20, C
    immediateADC(0xD0, 0x50, 0x20, 0, 1, 0);
    // Immediate D0+90=60, CV
    immediateADC(0xD0, 0x90, 0x60, 1, 1, 0);
    // Immediate D0+D0=A0, CN
    immediateADC(0xD0, 0xD0, 0xA0, 0, 1, 1);
    // Immediate Zero flag: 0xFE + 0x01 + 1 = 0x00
    registers.PC = 0x300;
    registers.A = 0x01;
    registers.flags.C = 1;
    writeMemory(0x300, 0xFE);
    ADC(0b010);
    assert(registers.A == 0x00);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 1);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute: ADC $045B = 0x33 + 0xAA = 0xDD
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    ADC(0b011);
    assert(registers.A == 0xDD);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Absolute,X: ADC $045B (+2)= 0x6E + 0xAA = 0x18, C
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x6E);
    ADC(0b111);
    assert(registers.A == 0x18);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,Y: ADC $045B (+1)= 0x7C + 0xAA = 0x26, C
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.Y = 0x01;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045C, 0x7C);
    ADC(0b110);
    assert(registers.A == 0x26);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero: ADC $08 = 0x63 + 0xAA = 0x0D, C
    registers.PC = 0x300;
    registers.A = 0xAA;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x63);
    ADC(0b001);
    assert(registers.A == 0x0D);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero,X: ADC $(08 +2) = 0x34 + 0xAA = 0xDE
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    ADC(0b101);
    assert(registers.A == 0xDE);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // (Zero,X): ADC ($20,4) = ADC $2047 = 0x66 + 0xAA = 0x10, C
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.X = 0x04;
    writeMemory(0x300, 0x20);
    writeMemory(0x24, 0x74);
    writeMemory(0x25, 0x20);
    writeMemory(0x2074, 0x66);
    ADC(0b000);
    assert(registers.A == 0x10);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // (Zero),Y: ADC ($86),10 = ADC $4028+10 = 0x73 + 0xAA = 0x1D, C
    registers.PC = 0x300;
    registers.A = 0xAA;
    registers.Y = 0x10;
    writeMemory(0x300, 0x86);
    writeMemory(0x86, 0x28);
    writeMemory(0x87, 0x40);
    writeMemory(0x4038, 0x73);
    ADC(0b100);
    assert(registers.A == 0x1D);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All ADC unit tests passed\n");
}

void immediateSBC(Byte m, Byte n, Byte result, Byte overflow, Byte carry, Byte negative) {
    registers.PC = 0x300;
    registers.A = m;
    registers.flags.C = 1;
    writeMemory(0x300, n);
    SBC(0b010);
    assert(registers.A == result);
    assert(registers.flags.C == carry);
    assert(registers.flags.V == overflow);
    assert(registers.flags.N == negative);
    clearRegisters();
}

void unitTestSBC() {
    // Immediate 50-f0=60
    immediateSBC(0x50, 0xF0, 0x60, 0, 0, 0);
    // Immediate 50-b0=a0, V
    immediateSBC(0x50, 0xB0, 0xA0, 1, 0, 1);
    // Immediate 50-70=e0
    immediateSBC(0x50, 0x70, 0xE0, 0, 0, 1);
    // Immediate 50-30=20, C
    immediateSBC(0x50, 0x30, 0x20, 0, 1, 0);
    // Immediate d0-f0=e0
    immediateSBC(0xD0, 0xF0, 0xE0, 0, 0, 1);
    // Immediate d0-b0=20, C
    immediateSBC(0xD0, 0xB0, 0x20, 0, 1, 0);
    // Immediate d0-70=60, VC
    immediateSBC(0xD0, 0x70, 0x60, 1, 1, 0);
    // Immediate d0-30=a0, C
    immediateSBC(0xD0, 0x30, 0xA0, 0, 1, 1);
    // Immediate Zero flag: 0x02 - 0x01 - 1 = 0x00
    registers.PC = 0x300;
    registers.A = 0x02;
    registers.flags.C = 0;
    writeMemory(0x300, 0x01);
    SBC(0b010);
    assert(registers.A == 0x00);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 1);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute: SBC $045B = 0x33 - 0x11 = 0x22
    registers.PC = 0x300;
    registers.A = 0x33;
    registers.flags.C = 1;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x11);
    SBC(0b011);
    assert(registers.A == 0x22);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,X: SBC $045B (+2)= 0x6E - 0x11 = 0x5D
    registers.PC = 0x300;
    registers.A = 0x6E;
    registers.flags.C = 1;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x11);
    SBC(0b111);
    assert(registers.A == 0x5D);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,Y: SBC $045B (+1)= 0x7C - 0x11 = 0x6B
    registers.PC = 0x300;
    registers.A = 0x7C;
    registers.flags.C = 1;
    registers.Y = 0x01;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045C, 0x11);
    SBC(0b110);
    assert(registers.A == 0x6B);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero: SBC $08 = 0x63 - 0x11 = 0x52
    registers.PC = 0x300;
    registers.A = 0x63;
    registers.flags.C = 1;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x11);
    SBC(0b001);
    assert(registers.A == 0x52);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero,X: SBC $(08 +2) = 0x34 - 0x11 = 0x23
    registers.PC = 0x300;
    registers.A = 0x34;
    registers.flags.C = 1;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x11);
    SBC(0b101);
    assert(registers.A == 0x23);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // (Zero,X): SBC ($20,4) = SBC $2047 = 0x66 - 0x11 = 0x55
    registers.PC = 0x300;
    registers.A = 0x66;
    registers.flags.C = 1;
    registers.X = 0x04;
    writeMemory(0x300, 0x20);
    writeMemory(0x24, 0x74);
    writeMemory(0x25, 0x20);
    writeMemory(0x2074, 0x11);
    SBC(0b000);
    assert(registers.A == 0x55);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // (Zero),Y: SBC ($86),10 = SBC $4028+10 = 0x73 - 0x11 = 0x62
    registers.PC = 0x300;
    registers.A = 0x73;
    registers.flags.C = 1;
    registers.Y = 0x10;
    writeMemory(0x300, 0x86);
    writeMemory(0x86, 0x28);
    writeMemory(0x87, 0x40);
    writeMemory(0x4038, 0x11);
    SBC(0b100);
    assert(registers.A == 0x62);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All SBC unit tests passed\n");
}


/* Group Two */
void unitTestLDX() {
    // Immediate no flags: LDX #0x6C
    registers.PC = 0x300;
    writeMemory(0x300, 0x6C);
    LDX(0b000);
    assert(registers.X == 0x6C);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Immediate Negative flag: LDX #0xF9
    registers.PC = 0x300;
    writeMemory(0x300, 0xF9);
    LDX(0b000);
    assert(registers.X == 0xF9);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Immediate Zero flag: LDX #0x00
    registers.PC = 0x300;
    writeMemory(0x300, 0x00);
    LDX(0b000);
    assert(registers.X == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute: LDX $045B = 0x33
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    LDX(0b011);
    assert(registers.X == 0x33);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,Y: LDX $045B (+2)= 0x44
    registers.PC = 0x300;
    registers.Y = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x44);
    LDX(0b111);
    assert(registers.X == 0x44);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero: LDX $08 = 0x11
    registers.PC = 0x300;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x11);
    LDX(0b001);
    assert(registers.X == 0x11);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero,Y: LDX $(08 +2) = 0x34
    registers.PC = 0x300;
    registers.Y = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    LDX(0b101);
    assert(registers.X == 0x34);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All LDX unit tests passed\n");
}

void unitTestASL() {
    // Absolute: ASL $045B = 0x33 << 1 = 0x66
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    ASL(0b011);
    assert(readMemory(0x045B) == 0x66);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute Carry flag: ASL $045B = 0x88 << 1 = 0x10,C
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x88);
    ASL(0b011);
    assert(readMemory(0x045B) == 0x10);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute Zero Flag: ASL $045B = 0x80 << 1 = 0x00,Z,C
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x80);
    ASL(0b011);
    assert(readMemory(0x045B) == 0x00);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute Negative Flag: ASL $045B = 0x42 << 1 = 0x84,N
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x42);
    ASL(0b011);
    assert(readMemory(0x045B) == 0x84);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Accumulator: ASL A = 0x33 << 1 = 0x66
    registers.PC = 0x300;
    registers.A = 0x33;
    ASL(0b010);
    assert(registers.A == 0x66);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,X: ASL $045B (+2)= 0x44 << 1 = 0x88,N
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x44);
    ASL(0b111);
    assert(readMemory(0x045D) == 0x88);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero: ASL $08 = 0x11 << 1 = 0x22
    registers.PC = 0x300;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x11);
    ASL(0b001);
    assert(readMemory(0x08) == 0x22);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero,X: ASL $(08 +2) = 0x34 << 1 = 0x68
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    ASL(0b101);
    assert(readMemory(0x0A) == 0x68);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All ASL unit tests passed\n");
}

void unitTestLSR() {
    // Absolute: LSR $045B = 0x66 >> 1 = 0x33
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x66);
    LSR(0b011);
    assert(readMemory(0x045B) == 0x33);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute Carry flag: LSR $045B = 0x99 >> 1 = 0x4C,C
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x99);
    LSR(0b011);
    assert(readMemory(0x045B) == 0x4C);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute Zero Flag: LSR $045B = 0x01 >> 1 = 0x00,Z,C
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x01);
    LSR(0b011);
    assert(readMemory(0x045B) == 0x00);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Accumulator: LSR A = 0x33 >> 1 = 0x19
    registers.PC = 0x300;
    registers.A = 0x33;
    LSR(0b010);
    assert(registers.A == 0x19);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,X: LSR $045B (+2)= 0x44 >> 1 = 0x22
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x44);
    LSR(0b111);
    assert(readMemory(0x045D) == 0x22);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero: LSR $08 = 0x78 >> 1 = 0x3C
    registers.PC = 0x300;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x78);
    LSR(0b001);
    assert(readMemory(0x08) == 0x3C);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero,X: LSR $(08 +2) = 0x34 >> 1 = 0x1A
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    LSR(0b101);
    assert(readMemory(0x0A) == 0x1A);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All LSR unit tests passed\n");
}

void unitTestROL() {
    // Absolute: ROL $045B = 0x33,1 << 1 = 0x67
    registers.PC = 0x300;
    registers.flags.C = 1;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    ROL(0b011);
    assert(readMemory(0x045B) == 0x67);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute Carry flag: ROL $045B = 0x88 << 1 = 0x10,C
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x88);
    ROL(0b011);
    assert(readMemory(0x045B) == 0x10);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute Zero Flag: ROL $045B = 0x80 << 1 = 0x00,Z,C
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x80);
    ROL(0b011);
    assert(readMemory(0x045B) == 0x00);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute Negative Flag: ROL $045B = 0x42 << 1 = 0x84,N
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x42);
    ROL(0b011);
    assert(readMemory(0x045B) == 0x84);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Accumulator: ROL A = 0x33 << 1 = 0x66
    registers.PC = 0x300;
    registers.A = 0x33;
    ROL(0b010);
    assert(registers.A == 0x66);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,X: ROL $045B (+2)= 0x44 << 1 = 0x88,N
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x44);
    ROL(0b111);
    assert(readMemory(0x045D) == 0x88);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero: ROL $08 = 0x11,1 << 1 = 0x23
    registers.PC = 0x300;
    registers.flags.C = 1;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x11);
    ROL(0b001);
    assert(readMemory(0x08) == 0x23);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero,X: ROL $(08 +2) = 0x34 << 1 = 0x68
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    ROL(0b101);
    assert(readMemory(0x0A) == 0x68);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All ROL unit tests passed\n");
}

void unitTestROR() {
    // Absolute: ROR $045B = 0x66 >> 1 = 0x33
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x66);
    ROR(0b011);
    assert(readMemory(0x045B) == 0x33);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute Carry flag: ROR $045B = 0x99 >> 1 = 0x4C,C
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x99);
    ROR(0b011);
    assert(readMemory(0x045B) == 0x4C);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute Negative Flag: ROR $405B = 1,0x66 >> 1 = 0xB3,N
    registers.PC = 0x300;
    registers.flags.C = 1;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x66);
    ROR(0b011);
    assert(readMemory(0x045B) == 0xB3);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Absolute Zero Flag: ROR $045B = 0x01 >> 1 = 0x00,Z,C
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x01);
    ROR(0b011);
    assert(readMemory(0x045B) == 0x00);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Accumulator: ROR A = 0x33 >> 1 = 0x19
    registers.PC = 0x300;
    registers.A = 0x33;
    ROR(0b010);
    assert(registers.A == 0x19);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,X: ROR $045B (+2)= 0x44 >> 1 = 0x22
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x44);
    ROR(0b111);
    assert(readMemory(0x045D) == 0x22);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero: ROR $08 = 0x78 >> 1 = 0x3C
    registers.PC = 0x300;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x78);
    ROR(0b001);
    assert(readMemory(0x08) == 0x3C);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero,X: ROR $(08 +2) = 1,0x34 >> 1 = 0x9A
    registers.PC = 0x300;
    registers.flags.C = 1;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    ROR(0b101);
    assert(readMemory(0x0A) == 0x9A);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    printf("All ROR unit tests passed\n");
}

void unitTestSTX() {
    // Absolute: STX $045B = 0x33
    registers.PC = 0x300;
    registers.X = 0x33;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    STX(0b011);
    assert(readMemory(0x045B) == 0x33);
    clearRegisters();
    // Zero: STX $08 = 0x11
    registers.PC = 0x300;
    registers.X = 0x11;
    writeMemory(0x300, 0x08);
    STX(0b001);
    assert(readMemory(0x08) == 0x11);
    clearRegisters();
    // Zero,Y: STX $(08 +2) = 0x34
    registers.PC = 0x300;
    registers.X = 0x34;
    registers.Y = 0x02;
    writeMemory(0x300, 0x08);
    STX(0b101);
    assert(readMemory(0x0A) == 0x34);
    clearRegisters();
    printf("All STX unit tests passed\n");
}

void unitTestINC() {
    // Absolute: INC $045B = 0x33++
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    INC(0b011);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    assert(readMemory(0x045B) == 0x34);
    clearRegisters();
    // Absolute Zero flag: INC $045B = 0xFF++
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0xFF);
    writeMemory(0x045C, 0x00);
    INC(0b011);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    assert(readMemory(0x045B) == 0x00);
    assert(readMemory(0x045C) == 0x00);
    clearRegisters();
    // Absolute Negative flag: INC $045B = 0x7F++
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x7F);
    INC(0b011);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    assert(readMemory(0x045B) == 0x80);
    clearRegisters();
    // Absolute,X: INC $045B (+2)= 0x44++
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x44);
    INC(0b111);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    assert(readMemory(0x045D) == 0x45);
    clearRegisters();
    // Zero: INC $08 = 0x11++
    registers.PC = 0x300;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x11);
    INC(0b001);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    assert(readMemory(0x0008) == 0x12);
    clearRegisters();
    // Zero,X: INC $(08 +2) = 0x34++
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    INC(0b101);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    assert(readMemory(0x000A) == 0x35);
    clearRegisters();
    printf("All INC unit tests passed\n");
}

void unitTestDEC() {
    // Absolute: DEC $045B = 0x33--
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    DEC(0b011);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    assert(readMemory(0x045B) == 0x32);
    clearRegisters();
    // Absolute Zero flag: DEC $045B = 0x01--
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x01);
    DEC(0b011);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    assert(readMemory(0x045B) == 0x00);
    clearRegisters();
    // Absolute Negative flag: DEC $045B = 0x00--
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x00);
    DEC(0b011);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    assert(readMemory(0x045B) == 0xFF);
    clearRegisters();
    // Absolute,X: DEC $045B (+2)= 0x44--
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x44);
    DEC(0b111);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    assert(readMemory(0x045D) == 0x43);
    clearRegisters();
    // Zero: DEC $08 = 0x11--
    registers.PC = 0x300;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x11);
    DEC(0b001);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    assert(readMemory(0x0008) == 0x10);
    clearRegisters();
    // Zero,X: DEC $(08 +2) = 0x34--
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    DEC(0b101);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    assert(readMemory(0x000A) == 0x33);
    clearRegisters();
    printf("All DEC unit tests passed\n");
}


/* Group Three */
void unitTestBIT() {
    // Absolute Zero Flag: BIT 0x045B = 0xCC & 0x33 = Z
    registers.PC = 0x300;
    registers.A = 0xCC;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    BIT(0b011);
    assert(registers.flags.Z == 1);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute Overflow Flag: BIT 0x045B = 0x33 & 0x59 = V
    registers.PC = 0x300;
    registers.A = 0x33;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x59);
    BIT(0b011);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute Negative Flag: BIT 0x045B = 0x33 & 0x99 = N
    registers.PC = 0x300;
    registers.A = 0x33;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x99);
    BIT(0b011);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero Zero Flag: BIT 0x08 = 0xCC & 0x33 = Z
    registers.PC = 0x300;
    registers.A = 0xCC;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x33);
    BIT(0b001);
    assert(registers.flags.Z == 1);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero Overflow Flag: BIT 0x08 = 0x33 & 0x59 = V
    registers.PC = 0x300;
    registers.A = 0x33;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x59);
    BIT(0b001);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero Negative Flag: BIT 0x08 = 0x33 & 0x99 = N
    registers.PC = 0x300;
    registers.A = 0x33;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x99);
    BIT(0b001);
    assert(registers.flags.Z == 0);
    assert(registers.flags.V == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    printf("All BIT unit tests passed\n");
}

void unitTestJMP() {
    // Absolute: JMP 0x045B
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    JMP_ABS(0b011);
    assert(registers.PC == 0x045B);
    // Indirect: JMP (0x045B) = JMP 0x1234
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x34);
    writeMemory(0x045C, 0x12);
    JMP(0b011);
    assert(registers.PC == 0x1234);
    printf("All JMP unit tests passed\n");
}

void unitTestSTY() {
    // Absolute: STY $045B = 0x33
    registers.PC = 0x300;
    registers.Y = 0x33;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    STY(0b011);
    assert(readMemory(0x045B) == 0x33);
    clearRegisters();
    // Zero: STY $08 = 0x11
    registers.PC = 0x300;
    registers.Y = 0x11;
    writeMemory(0x300, 0x08);
    STY(0b001);
    assert(readMemory(0x08) == 0x11);
    clearRegisters();
    // Zero,Y: STY $(08 +2) = 0x34
    registers.PC = 0x300;
    registers.Y = 0x34;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    STY(0b101);
    assert(readMemory(0x0A) == 0x34);
    clearRegisters();
    printf("All STY unit tests passed\n");
}

void unitTestLDY() {
    // Immediate no flags: LDY #0x6C
    registers.PC = 0x300;
    writeMemory(0x300, 0x6C);
    LDY(0b000);
    assert(registers.Y == 0x6C);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Immediate Negative flag: LDY #0xF9
    registers.PC = 0x300;
    writeMemory(0x300, 0xF9);
    LDY(0b000);
    assert(registers.Y == 0xF9);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Immediate Zero flag: LDY #0x00
    registers.PC = 0x300;
    writeMemory(0x300, 0x00);
    LDY(0b000);
    assert(registers.Y == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute: LDY $045B = 0x33
    registers.PC = 0x300;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    LDY(0b011);
    assert(registers.Y == 0x33);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute,Y: LDY $045B (+2)= 0x44
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045D, 0x44);
    LDY(0b111);
    assert(registers.Y == 0x44);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero: LDY $08 = 0x11
    registers.PC = 0x300;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0x11);
    LDY(0b001);
    assert(registers.Y == 0x11);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero,X: LDY $(08 +2) = 0x34
    registers.PC = 0x300;
    registers.X = 0x02;
    writeMemory(0x300, 0x08);
    writeMemory(0x0A, 0x34);
    LDY(0b101);
    assert(registers.Y == 0x34);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All LDY unit tests passed\n");
}

void unitTestCPY() {
    // Immediate: 01 ? FF = ()
    registers.PC = 0x300;
    registers.Y = 0x01;
    writeMemory(0x300, 0xFF);
    CPY(0b000);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Immediate: 7F ? 80 = N
    registers.PC = 0x300;
    registers.Y = 0x7F;
    writeMemory(0x300, 0x80);
    CPY(0b000);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Immediate: AA ? 99 = C
    registers.PC = 0x300;
    registers.Y = 0xAA;
    writeMemory(0x300, 0x99);
    CPY(0b000);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Immediate: AA ? AA = Z,C
    registers.PC = 0x300;
    registers.Y = 0xAA;
    writeMemory(0x300, 0xAA);
    CPY(0b000);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute: CPY $045B = 0x33 >
    registers.PC = 0x300;
    registers.Y = 0xAA;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    CPY(0b011);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero: CPY $08 = 0xAA =
    registers.PC = 0x300;
    registers.Y = 0xAA;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0xAA);
    CPY(0b001);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All CPY unit tests passed\n");
}

void unitTestCPX() {
    // Immediate: 01 ? FF = ()
    registers.PC = 0x300;
    registers.X = 0x01;
    writeMemory(0x300, 0xFF);
    CPX(0b000);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Immediate: 7F ? 80 = N
    registers.PC = 0x300;
    registers.X = 0x7F;
    writeMemory(0x300, 0x80);
    CPX(0b000);
    assert(registers.flags.C == 0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Immediate: AA ? 99 = C
    registers.PC = 0x300;
    registers.X = 0xAA;
    writeMemory(0x300, 0x99);
    CPX(0b000);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Immediate: AA ? AA = Z,C
    registers.PC = 0x300;
    registers.X = 0xAA;
    writeMemory(0x300, 0xAA);
    CPX(0b000);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Absolute: CPX $045B = 0x33 >
    registers.PC = 0x300;
    registers.X = 0xAA;
    writeMemory(0x300, 0x5B);
    writeMemory(0x301, 0x04);
    writeMemory(0x045B, 0x33);
    CPX(0b011);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Zero: CPX $08 = 0xAA =
    registers.PC = 0x300;
    registers.X = 0xAA;
    writeMemory(0x300, 0x08);
    writeMemory(0x08, 0xAA);
    CPX(0b001);
    assert(registers.flags.C == 1);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All CPX unit tests passed\n");
}


/* Stack */
void unitTestPHA() {
    // Positive value
    registers.A = 0x25;
    registers.SP = 0x14;
    PHA();
    assert(readMemory(0x0114) == 0x25);
    clearRegisters();
    // Negative value
    registers.A = 0xFF;
    registers.SP = 0xF0;
    PHA();
    assert(readMemory(0x01F0) == 0xFF);
    clearRegisters();
    printf("All PHA unit tests passed\n");
}

void unitTestPLA() {
    // Positive value
    registers.SP = 0x20;
    writeMemory(0x0121, 0x25);
    PLA();
    assert(registers.A == 0x25);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Negative value
    registers.SP = 0xF0;
    writeMemory(0x01F1, 0x81);
    PLA();
    assert(registers.A == 0x81);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero value
    registers.SP = 0x57;
    writeMemory(0x0158, 0x00);
    PLA();
    assert(registers.A == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All PLA unit tests passed\n");
}

void unitTestPHP() {
    // Zeros
    registers.PS = 0x00;
    registers.SP = 0x14;
    PHP();
    assert(readMemory(0x0114) == (0x00 | breakBit | unusedBit));
    clearRegisters();
    // Ones
    registers.PS = 0xFF;
    registers.SP = 0x14;
    PHP();
    assert(readMemory(0x0114) == 0xFF);
    clearRegisters();
    // Alternating
    registers.PS = 0xAA;
    registers.SP = 0x14;
    PHP();
    assert(readMemory(0x0114) == (0xAA | breakBit | unusedBit));
    clearRegisters();
    printf("All PHP unit tests passed\n");
}

void unitTestPLP() {
    Byte bAndUCleared = ~(unusedBit | breakBit);
    // Zeros
    registers.SP = 0x15;
    writeMemory(0x0116, 0x00);
    PLP();
    assert(registers.PS == 0x00);
    clearRegisters();
    // Ones - B&U are cleared
    registers.SP = 0x15;
    writeMemory(0x0116, 0xFF);
    PLP();
    assert(registers.PS == (0xFF & bAndUCleared));
    clearRegisters();
    // Alternating - B&U are cleared
    registers.SP = 0x15;
    writeMemory(0x0116, 0xAA);
    PLP();
    assert(registers.PS == (0xAA & bAndUCleared));
    clearRegisters();
    printf("All PLP unit tests passed\n");
}


/* Flags */
void unitTestCLC() {
    registers.flags.C = 0;
    CLC();
    assert(registers.flags.C == 0);
    registers.flags.C = 1;
    CLC();
    assert(registers.flags.C == 0);
    printf("All CLC unit tests passed\n");  
}

void unitTestSEC() {
    registers.flags.C = 0;
    SEC();
    assert(registers.flags.C == 1);
    registers.flags.C = 1;
    SEC();
    assert(registers.flags.C == 1);
    printf("All SEC unit tests passed\n");  
}

void unitTestCLI() {
    registers.flags.I = 0;
    CLI();
    assert(registers.flags.I == 0);
    registers.flags.I = 1;
    CLI();
    assert(registers.flags.I == 0);
    printf("All CLI unit tests passed\n");  
}

void unitTestSEI() {
    registers.flags.I = 0;
    SEI();
    assert(registers.flags.I == 1);
    registers.flags.I = 1;
    SEI();
    assert(registers.flags.I == 1);
    printf("All SEI unit tests passed\n");  
}

void unitTestCLV() {
    registers.flags.V = 0;
    CLV();
    assert(registers.flags.V == 0);
    registers.flags.V = 1;
    CLV();
    assert(registers.flags.V == 0);
    printf("All CLV unit tests passed\n");  
}

void unitTestCLD() {
    registers.flags.D = 0;
    CLD();
    assert(registers.flags.D == 0);
    registers.flags.D = 1;
    CLD();
    assert(registers.flags.D == 0);
    printf("All CLD unit tests passed\n");  
}

void unitTestSED() {
    registers.flags.D = 0;
    SED();
    assert(registers.flags.D == 1);
    registers.flags.D = 1;
    SED();
    assert(registers.flags.D == 1);
    printf("All SED unit tests passed\n");  
}


/* Other */
void unitTestDEY() {
    // Positive value
    registers.Y = 0x57;
    DEY();
    assert(registers.Y == 0x56);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Negative value
    registers.Y = 0xF1;
    DEY();
    assert(registers.Y == 0xF0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero value
    registers.Y = 0x01;
    DEY();
    assert(registers.Y == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Overflow value
    registers.Y = 0x00;
    DEY();
    assert(registers.Y == 0xFF);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    printf("All DEY unit tests passed\n");  
}

void unitTestTAY() {
    // Positive value
    registers.A = 0x12;
    TAY();
    assert(registers.Y == 0x12);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Negative value
    registers.A = 0xF2;
    TAY();
    assert(registers.Y == 0xF2);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero value
    registers.A = 0x00;
    TAY();
    assert(registers.Y == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All TAY unit tests passed\n");  
}

void unitTestINY() {
    // Positive value
    registers.Y = 0x57;
    INY();
    assert(registers.Y == 0x58);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Negative value
    registers.Y = 0xF1;
    INY();
    assert(registers.Y == 0xF2);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero value & Overflow
    registers.Y = 0xFF;
    INY();
    assert(registers.Y == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All INY unit tests passed\n");  
}

void unitTestINX() {
    // Positive value
    registers.X = 0x57;
    INX();
    assert(registers.X == 0x58);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Negative value
    registers.X = 0xF1;
    INX();
    assert(registers.X == 0xF2);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero value & Overflow
    registers.X = 0xFF;
    INX();
    assert(registers.X == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All INX unit tests passed\n");  
}

void unitTestTXA() {
    // Positive value
    registers.X = 0x12;
    TXA();
    assert(registers.A == 0x12);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Negative value
    registers.X = 0xF2;
    TXA();
    assert(registers.A == 0xF2);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero value
    registers.X = 0x00;
    TXA();
    assert(registers.A == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All TXA unit tests passed\n");    
}

void unitTestTXS() {
    // Positive value
    registers.X = 0x12;
    TXS();
    assert(registers.SP == 0x12);
    clearRegisters();
    // Negative value
    registers.X = 0xF2;
    TXS();
    assert(registers.SP == 0xF2);
    clearRegisters();
    // Zero value
    registers.X = 0x00;
    TXS();
    assert(registers.SP == 0x00);
    clearRegisters();
    printf("All TXS unit tests passed\n");    
}

void unitTestTAX() {
    // Positive value
    registers.A = 0x12;
    TAX();
    assert(registers.X == 0x12);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Negative value
    registers.A = 0xF2;
    TAX();
    assert(registers.X == 0xF2);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero value
    registers.A = 0x00;
    TAX();
    assert(registers.X == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All TAX unit tests passed\n");  
}

void unitTestTSX() {
    // Positive value
    registers.SP = 0x12;
    TSX();
    assert(registers.X == 0x12);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Negative value
    registers.SP = 0xF2;
    TSX();
    assert(registers.X == 0xF2);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero value
    registers.SP = 0x00;
    TSX();
    assert(registers.X == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All TSX unit tests passed\n");  
}

void unitTestDEX() {
    // Positive value
    registers.X = 0x57;
    DEX();
    assert(registers.X == 0x56);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Negative value
    registers.X = 0xF1;
    DEX();
    assert(registers.X == 0xF0);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero value
    registers.X = 0x01;
    DEX();
    assert(registers.X == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Overflow value
    registers.X = 0x00;
    DEX();
    assert(registers.X == 0xFF);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    printf("All DEX unit tests passed\n");  
}

void unitTestNOP() {
    registers.PC = 0x0300;
    NOP();
    assert(registers.PC == 0x0300);
}

void unitTestTYA() {
    // Positive value
    registers.Y = 0x12;
    TYA();
    assert(registers.A == 0x12);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 0);
    clearRegisters();
    // Negative value
    registers.Y = 0xF2;
    TYA();
    assert(registers.A == 0xF2);
    assert(registers.flags.Z == 0);
    assert(registers.flags.N == 1);
    clearRegisters();
    // Zero value
    registers.Y = 0x00;
    TYA();
    assert(registers.A == 0x00);
    assert(registers.flags.Z == 1);
    assert(registers.flags.N == 0);
    clearRegisters();
    printf("All TYA unit tests passed\n");    
}


/* Branching */
void unitTestBEQ() {
    // Forward
    registers.flags.Z = 1;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BEQ();
    assert(registers.PC == 0x343A);
    clearRegisters();
    // Backward
    registers.flags.Z = 1;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0xFC);
    BEQ();
    assert(registers.PC == 0x3431);
    clearRegisters();
    // No Branch
    registers.flags.Z = 0;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BEQ();
    assert(registers.PC == 0x3435);
    clearRegisters();
    printf("All BEQ unit tests passed\n");
}

void unitTestBNE() {
    // Forward
    registers.flags.Z = 0;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BNE();
    assert(registers.PC == 0x343A);
    clearRegisters();
    // Backward
    registers.flags.Z = 0;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0xFC);
    BNE();
    assert(registers.PC == 0x3431);
    clearRegisters();
    // No Branch
    registers.flags.Z = 1;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BNE();
    assert(registers.PC == 0x3435);
    clearRegisters();
    printf("All BNE unit tests passed\n");
}

void unitTestBCS() {
    // Forward
    registers.flags.C = 1;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BCS();
    assert(registers.PC == 0x343A);
    clearRegisters();
    // Backward
    registers.flags.C = 1;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0xFC);
    BCS();
    assert(registers.PC == 0x3431);
    clearRegisters();
    // No Branch
    registers.flags.C = 0;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BCS();
    assert(registers.PC == 0x3435);
    clearRegisters();
    printf("All BCS unit tests passed\n");
}

void unitTestBCC() {
    // Forward
    registers.flags.C = 0;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BCC();
    assert(registers.PC == 0x343A);
    clearRegisters();
    // Backward
    registers.flags.C = 0;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0xFC);
    BCC();
    assert(registers.PC == 0x3431);
    clearRegisters();
    // No Branch
    registers.flags.C = 1;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BCC();
    assert(registers.PC == 0x3435);
    clearRegisters();
    printf("All BCC unit tests passed\n");
}

void unitTestBVS() {
    // Forward
    registers.flags.V = 1;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BVS();
    assert(registers.PC == 0x343A);
    clearRegisters();
    // Backward
    registers.flags.V = 1;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0xFC);
    BVS();
    assert(registers.PC == 0x3431);
    clearRegisters();
    // No Branch
    registers.flags.V = 0;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BVS();
    assert(registers.PC == 0x3435);
    clearRegisters();
    printf("All BVS unit tests passed\n");
}

void unitTestBVC() {
    // Forward
    registers.flags.V = 0;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BVC();
    assert(registers.PC == 0x343A);
    clearRegisters();
    // Backward
    registers.flags.V = 0;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0xFC);
    BVC();
    assert(registers.PC == 0x3431);
    clearRegisters();
    // No Branch
    registers.flags.V = 1;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BVC();
    assert(registers.PC == 0x3435);
    clearRegisters();
    printf("All BVC unit tests passed\n");
}

void unitTestBMI() {
    // Forward
    registers.flags.N = 1;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BMI();
    assert(registers.PC == 0x343A);
    clearRegisters();
    // Backward
    registers.flags.N = 1;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0xFC);
    BMI();
    assert(registers.PC == 0x3431);
    clearRegisters();
    // No Branch
    registers.flags.N = 0;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BMI();
    assert(registers.PC == 0x3435);
    clearRegisters();
    printf("All BMI unit tests passed\n");
}

void unitTestBPL() {
    // Forward
    registers.flags.N = 0;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BPL();
    assert(registers.PC == 0x343A);
    clearRegisters();
    // Backward
    registers.flags.N = 0;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0xFC);
    BPL();
    assert(registers.PC == 0x3431);
    clearRegisters();
    // No Branch
    registers.flags.N = 1;
    registers.PC = 0x3434;
    writeMemory(0x3434, 0x05);
    BPL();
    assert(registers.PC == 0x3435);
    clearRegisters();
    printf("All BPL unit tests passed\n");
}


/* Subroutines */
void unitTestJSR() {
    // JSR 0x1234
    // Address 0x0306 -> Stack 0x0155,0x0154
    registers.PC = 0x304;
    registers.SP = 0x55;
    writeMemory(0x304, 0x34);
    writeMemory(0x305, 0x12);
    JSR();
    assert(registers.PC == 0x1234);
    assert(readMemory(0x0155) == 0x03);
    assert(readMemory(0x0154) == 0x06);
    clearRegisters();
    printf("All JSR unit tests passed\n");  
}

void unitTestRTS() {
    // 0x0306 pushed on stack at 0x0155,0x0154
    writeMemory(0x0155, 0x03);
    writeMemory(0x0154, 0x06);
    registers.SP = 0x53;
    RTS();
    assert(registers.PC == 0x0306);
    clearRegisters();
    printf("All RTS unit tests passed\n");  
}

void unitTestJSRandRTS() {
    // JSR 0x1234
    // Address 0x0306 -> Stack 0x0155,0x0154
    registers.A = 0;
    registers.PC = 0x304;
    registers.SP = 0x55;
    writeMemory(0x304, 0x34);
    writeMemory(0x305, 0x12);
    JSR();
    assert(registers.PC == 0x1234);
    // LDA $2211 = EE
    writeMemory(0x1234, 0x11);
    writeMemory(0x1235, 0x22);
    writeMemory(0x2211, 0xEE);
    LDA(0b011);
    assert(registers.A == 0xEE);
    // RTS to 0x306
    RTS();
    assert(registers.PC == 0x306);
    assert(registers.SP == 0x55);
    // LDA $5533 = DD
    writeMemory(0x306, 0x33);
    writeMemory(0x307, 0x55);
    writeMemory(0x5533, 0xDD);
    LDA(0b011);
    assert(registers.A = 0xDD);
    clearRegisters();
    printf("JSR and RTS unit test passed\n");  
}

void unitTestBRK() {
    // jump from 0x3456 to $(FFFE) = 0x6789
    registers.flags.C = 1;
    registers.flags.V = 1;
    registers.PC = 0x3456;
    registers.SP = 0x55;
    writeMemory(0xFFFE, 0x89);
    writeMemory(0xFFFF, 0x67);
    BRK();
    assert(readMemory(0x0155) == 0x34);
    assert(readMemory(0x0154) == 0x57); // PC+1 used for return address
    assert(readMemory(0x0153) == (overflowBit | carryBit | breakBit | unusedBit));
    assert(registers.PC == 0x6789);
    assert(registers.flags.B == 1);
    assert(registers.flags.I == 1);
    clearRegisters();
    printf("All JSR unit tests passed\n");  
}

void unitTestRTI() {
    // return to 0x5678 with Carry set
    registers.SP = 0x52;
    writeMemory(0x0153, carryBit);
    writeMemory(0x0154, 0x78);
    writeMemory(0x0155, 0x56);
    RTI();
    assert(registers.PC == 0x5678);
    assert(registers.flags.C == 1);
    assert(registers.flags.B == 0);
    clearRegisters();
    // unchanged register bits set
    registers.SP = 0x52;
    writeMemory(0x0153, carryBit);
    writeMemory(0x0154, 0x78);
    writeMemory(0x0155, 0x56);
    RTI();
    assert(registers.PC == 0x5678);
    assert(registers.flags.C == 1);
    assert(registers.flags.B == 0);
    clearRegisters();
    printf("All RTI unit tests passed\n");  
}

void unitTestBRKandRTI() {
    // BRK from 0x3456 to $(FFFE) = 0x6789
    registers.flags.C = 1;
    registers.flags.V = 1;
    registers.PC = 0x3456;
    registers.SP = 0x55;
    writeMemory(0xFFFE, 0x89);
    writeMemory(0xFFFF, 0x67);
    BRK();
    assert(readMemory(0x0155) == 0x34);
    assert(readMemory(0x0154) == 0x57); // PC+1 used for return address
    assert(readMemory(0x0153) == (overflowBit | carryBit | breakBit | unusedBit));
    assert(registers.PC == 0x6789);
    assert(registers.flags.B == 1);
    // LDA $(3312) = 0xDE
    writeMemory(0x6789, 0x12);
    writeMemory(0x678A, 0x33);
    writeMemory(0x3312, 0xDE);
    LDA(0b011);
    assert(registers.A == 0xDE);
    // RTI to 0x3457 with Carry and Overflow set (break left set)
    RTI();
    assert(registers.PC == 0x3457);
    assert(registers.flags.C == 1);
    assert(registers.flags.V == 1);
    assert(registers.flags.B == 0);
    clearRegisters();
    printf("BRK and RTI unit test passed\n");  
}
