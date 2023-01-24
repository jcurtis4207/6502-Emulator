#include "6502_instructions.h"

void executeInstruction(Byte instruction) {
    Byte opcode = (instruction & 0b11100000) >> 5;
    Byte addressMode = (instruction & 0b00011100) >> 2;
    Byte group = instruction & 0b00000011;
    char match = true;

    switch (instruction) {
        case 0x00:
            BRK();
            break;
        case 0x08:
            PHP();
            break;
        case 0x10:
            BPL();
            break;
        case 0x18:
            CLC();
            break;
        case 0x20:
            JSR();
            break;
        case 0x28:
            PLP();
            break;
        case 0x30:
            BMI();
            break;
        case 0x38:
            SEC();
            break;
        case 0x40:
            RTI();
            break;
        case 0x48:
            PHA();
            break;
        case 0x50:
            BVC();
            break;
        case 0x58:
            CLI();
            break;
        case 0x60:
            RTS();
            break;
        case 0x68:
            PLA();
            break;
        case 0x70:
            BVS();
            break;
        case 0x78:
            SEI();
            break;
        case 0x88:
            DEY();
            break;
        case 0x8A:
            TXA();
            break;
        case 0x90:
            BCC();
            break;
        case 0x98:
            TYA();
            break;
        case 0x9A:
            TXS();
            break;
        case 0xA8:
            TAY();
            break;
        case 0xAA:
            TAX();
            break;
        case 0xB0:
            BCS();
            break;
        case 0xB8:
            CLV();
            break;
        case 0xBA:
            TSX();
            break;
        case 0xC8:
            INY();
            break;
        case 0xCA:
            DEX();
            break;
        case 0xD0:
            BNE();
            break;
        case 0xD8:
            CLD();
            break;
        case 0xE8:
            INX();
            break;
        case 0xEA:
            NOP();
            break;
        case 0xF0:
            BEQ();
            break;
        case 0xF8:
            SED();
            break;
        // fake
        case 0xFF:
            printRegisters();
            exit(0);
            break;
        default:
            match = false;
            break;
    }
    if (match) {
        return;
    }

    if (group == 0b00) {
        switch(opcode) {
            case 0b001:
                BIT(addressMode);
                break;
            case 0b010:
                JMP_ABS(addressMode);
                break;
            case 0b011:
                JMP(addressMode);
                break;
            case 0b100:
                STY(addressMode);
                break;
            case 0b101:
                LDY(addressMode);
                break;
            case 0b110:
                CPY(addressMode);
                break;
            case 0b111:
                CPX(addressMode);
                break;
            default:
                throwError("Instruction not found, opcode");
        }
    } else if (group == 0b10) {
        switch(opcode) {
            case 0b00:
                ASL(addressMode);
                break;
            case 0b001:
                ROL(addressMode);
                break;
            case 0b010:
                LSR(addressMode);
                break;
            case 0b011:
                ROR(addressMode);
                break;
            case 0b100:
                STX(addressMode);
                break;
            case 0b101:
                LDX(addressMode);
                break;
            case 0b110:
                DEC(addressMode);
                break;
            case 0b111:
                INC(addressMode);
                break;
            default:
                throwError("Instruction not found, opcode");
        }
    } else if (group == 0b01) {
        switch (opcode) {
            case 0b000:
                ORA(addressMode);
                break;
            case 0b001:
                AND(addressMode);
                break;
            case 0b010:
                EOR(addressMode);
                break;
            case 0b011:
                ADC(addressMode);
                break;
            case 0b100:
                STA(addressMode);
                break;
            case 0b101:
                LDA(addressMode);
                break;
            case 0b110:
                CMP(addressMode);
                break;
            case 0b111:
                SBC(addressMode);
                break;
            default:
                throwError("Instruction not found, opcode");
        }
    } else {
        throwError("Instruction not found, group");
    }
}
