#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "6502_unit_tests.h"

int main() {
    clearRegisters();
    // Group One
    unitTestLDA();
    unitTestORA();
    unitTestAND();
    unitTestEOR();
    unitTestCMP();
    unitTestADC();
    unitTestSBC();
    unitTestSTA();
    // Group Two
    unitTestLDX();
    unitTestASL();
    unitTestLSR();
    unitTestROL();
    unitTestROR();
    unitTestSTX();
    unitTestINC();
    unitTestDEC();
    // Group Three
    unitTestBIT();
    unitTestJMP();
    unitTestSTY();
    unitTestLDY();
    unitTestCPY();
    unitTestCPX();
    // Stack
    unitTestPHA();
    unitTestPLA();
    unitTestPHP();
    unitTestPLP();
    // Flags
    unitTestCLC();
    unitTestSEC();
    unitTestCLI();
    unitTestSEI();
    unitTestCLV();
    unitTestCLD();
    unitTestSED();
    // Other
    unitTestINX();
    unitTestINY();
    unitTestDEX();
    unitTestDEY();
    unitTestTAX();
    unitTestTAY();
    unitTestTSX();
    unitTestTXA();
    unitTestTXS();
    unitTestTYA();
    unitTestNOP();
    // Branching
    unitTestBEQ();
    unitTestBNE();
    unitTestBCS();
    unitTestBCC();
    unitTestBVS();
    unitTestBVC();
    unitTestBMI();
    unitTestBPL();
    // Subroutines
    unitTestJSR();
    unitTestRTS();
    unitTestJSRandRTS();
    unitTestBRK();
    unitTestRTI();
    unitTestBRKandRTI();
}
