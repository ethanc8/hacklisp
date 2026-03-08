# Bootstrapping from FPGA

# Project goals

Modern open-source operating systems are built using different open-source operating systems. If a "trusting trust" attack was performed many years ago on a common open-source operating system, the attacker's attack may have spread to all existing compilers and OSes. Other similar risks also prevail. Bootstrapping from a verifiable and extremely small binary seed, only trusting human-readable source code beyond that point, will allow the achievement of a computing system that is trustable.

While this exercise has been achieved on modern x86\_64 systems, x86\_64 systems include large amounts of proprietary code and firmware, along with "Management Engines" or similar high-privileged CPUs that can engage in attacks against the trusted code. Additionally, even if an x86\_64 system were completely open, it is not really feasible for a typical high school student or undergraduate to understand the system from the logical level up. Bootstrapping to an assembler on the Hack computer will allow people to have a simple computer that can achieve some useful tasks, that they can fully understand and trust.

The goal of the project is to achieve a system that can assemble and run Hack assembly, with minimal inputs:

* An FPGA  
* The HDL of the Hack computer  
* A screen  
* A small Hack binary, as small as possible  
* Source code for progressively more advanced assemblers

We must trust that these elements are not malicious. Additionally, we must assume that the software used to program the FPGA is also not malicious. Assuming that any of these elements are malicious would make the project extremely difficult.

# Design and implementation

This has two parts, one hardware and one extremely-low-level software. The hardware part would involve:

* Writing a computer with the Hack design in Verilog  
  * I plan to follow [https://gitlab.com/x653/nand2tetris-fpga/](https://gitlab.com/x653/nand2tetris-fpga/)  
  * I have completed Project 1 in Verilog, no further  
* Implementing appropriate I/O devices  
  * Screen (VGA)  
  * Keyboard  
    * The UART serial console exposed over USB can be used  
    * An entirely on-device input, using the four switches on the board, plus 4 more switches on a breadboard attached to PMOD, could be designed  
      * [https://digilent.com/reference/\_media/reference/pmod/pmodbtn/pmodbtn\_sch.pdf](https://digilent.com/reference/_media/reference/pmod/pmodbtn/pmodbtn_sch.pdf)

The software part would and involve:

* A basic "hex0" ASCII hex-to-binary converter supporting comments  
  * This should be as minimal as possible, since it will be a binary that the user must trust to correspond to source code  
  * This is inspired by the hex0 from [stage0-posix](https://github.com/oriansj/stage0-posix)  
* A "hex1" assembler that still only has hex instructions, but now has one-character labels  
  * This would be written in hex0 code  
* A "hex2" assembler which has full A-instruction support  
  * This would be written in hex1 code  
* A final basic assembler that fully supports Hack assembly, which could be used in future projects to bootstrap to the Jack compiler or a C compiler  
  * This would be written in hex2 code

This is inspired by [stage0-posix](https://github.com/oriansj/stage0-posix), but we assume that there is no C compiler we can bootstrap to, nor do we assume the existence of a POSIX kernel, so the bootstrapping steps should be different. We will probably also have to implement a basic code editor, so that the user can enter the code in via the keyboard. Alternately, we can assume that writing the ROM is trusted (otherwise how could we trust the CPU itself, other than the fact that it's hard to make significant malicious code into such a small FPGA?).

# Success criteria

I expect that the project might be rather large and not feasible in the available time. Thus, there are multiple goals, and the full completion of the project is a far-fetched stretch goal.

* **Basic goal (hardware):** A full Verilog implementation of the Hack computer is designed, and loaded onto the FPGA. It is able to perform any computable problem within the limits of its RAM and memory, but cannot communicate the result of the computation except via the 4 LEDs on the NandLand Go Board.  
* **Full goal (hardware):** It is possible to enter data into the Hack computer with the serial console and via the buttons on the Go Board. The Hack computer also has video output via VGA. Additionally, the computer has WX memory \-- it can write executable code to memory which it can then jump to.  
* **Basic goal (software):** hex0 is completed, and assembles the code stored at a memory address in ROM, writing it to RAM. It then jumps to the assembled code.  
* **Medium goal (software):** hex0, hex1, and hex2 are completed, culminating in writing a basic assembler with full support for Hack assembly to RAM.   
* **Full goal (software):** The user can input code via the serial console, and can then assemble and execute the code.  
  * I'm not sure how difficult it would be to implement this in assembly.  
* **Extra:** The user can input code via the buttons on the NandLand Go Board, plus extra buttons attached to PMOD. The input code appears on the screen attached by VGA. The user can then assemble and execute the code.

# Anticipated challenges

## Hardware

[https://gitlab.com/x653/nand2tetris-fpga/](https://gitlab.com/x653/nand2tetris-fpga/) provides a rather good frame for the implementation of the actual CPU. However, implementing the VGA screen and the button-press input will need to be done in a quite novel way. The additional buttons connected via PMOD may be difficult, as resistors need to be used and it is not really "digital design", but rather a different type of circuit design.

I haven't used serial consoles much before, so I don't really understand the difficulties with implementing support for them. However, NandLand has a tutorial on implementing serial console support on the Go Board.

## Software

Assembly programming is rather difficult, and implementing an assembler in assembly would probably prove to be much more difficult than implementing it in a high-level language with excellent string processing facilities. It's possible I might want to extend my Rust assembler with extra facilities to make programming a little bit easier.

Providing a way for the development of the code to be done on-device is even more difficult. There, I'd need to implement a terminal emulator, a font, and also find a way to input code with only 8 buttons. At least for hex0, a simpler way might be to implement each byte as just pixels on and off on the screen, and just provide a 0, 1, and backspace button for the user to input code. However, this is a rather far stretch goal.
