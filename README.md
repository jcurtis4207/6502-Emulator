# 6502 Emulator

This is a basic emulator for the 6502 CPU, using only the original opcodes.

This is the first emulator I have written, the first meaningful project I've written in C, and is hopefully a stepping stone for future projects.

#

## Functionality

Currently, the emulator can read in a binary file and execute it.
The file must be specified inside the `main` function, as well as the address of where to start writing the binary into memory.
> Depending on the file, the program counter may need to be set manually.

```c
int main() {
    reset();
    readROM(0x8000, "./testfile.bin");
    registers.PC = 0x8001;
```

## Usage

The repository contains 3 scripts
- `assemble` - takes an assembly file and assembles a binary and creates a hexdump text file. It requires `dasm` to be in the current directory (not included in this repo).
- `build` - simply compiles `main.c` and executes the binary.
- `run_unit_tests` - compiles `unit_tests.c` and executes it.

## Tests

The emulator was tested using Klaus2m5's [6502 Functional Test Repo](https://github.com/Klaus2m5/6502_65C02_functional_tests) with decimal mode disabled. This test suite, along with other tests found in the [neskell repo](https://github.com/blitzcode/neskell/tree/master/src/tests), helped massively when debugging.

## Future Work

I'm not sure how I want to proceed with this. One idea is to use this as the basis for a Commodore 64 emulator, but since I didn't start out with that intention, it would probably require a huge amount of reworking to use it in a larger emulator. For example, there is no concept of a clock or cycles.

Most likely I will leave this as is, but take what I learned and use it create something else.