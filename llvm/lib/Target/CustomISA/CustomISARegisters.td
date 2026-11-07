//===-- CustomISARegisters.td - CustomISA Register Definitions ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the CustomISA registers.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Register Classes
//===----------------------------------------------------------------------===//

// 32-bit general purpose register class
class CustomISAReg<bits<6> num, string n> : Register<n> {
  let HWEncoding = {num, 0b0000000000};
  let Namespace = "CustomISA";
}

// General purpose registers R0-R63
def R0  : CustomISAReg<0,  "R0">,  DwarfRegNum<[0]>;
def R1  : CustomISAReg<1,  "R1">,  DwarfRegNum<[1]>;
def R2  : CustomISAReg<2,  "R2">,  DwarfRegNum<[2]>;
def R3  : CustomISAReg<3,  "R3">,  DwarfRegNum<[3]>;
def R4  : CustomISAReg<4,  "R4">,  DwarfRegNum<[4]>;
def R5  : CustomISAReg<5,  "R5">,  DwarfRegNum<[5]>;
def R6  : CustomISAReg<6,  "R6">,  DwarfRegNum<[6]>;
def R7  : CustomISAReg<7,  "R7">,  DwarfRegNum<[7]>;
def R8  : CustomISAReg<8,  "R8">,  DwarfRegNum<[8]>;
def R9  : CustomISAReg<9,  "R9">,  DwarfRegNum<[9]>;
def R10 : CustomISAReg<10, "R10">, DwarfRegNum<[10]>;
def R11 : CustomISAReg<11, "R11">, DwarfRegNum<[11]>;
def R12 : CustomISAReg<12, "R12">, DwarfRegNum<[12]>;
def R13 : CustomISAReg<13, "R13">, DwarfRegNum<[13]>;
def R14 : CustomISAReg<14, "R14">, DwarfRegNum<[14]>;
def R15 : CustomISAReg<15, "R15">, DwarfRegNum<[15]>;
def R16 : CustomISAReg<16, "R16">, DwarfRegNum<[16]>;
def R17 : CustomISAReg<17, "R17">, DwarfRegNum<[17]>;
def R18 : CustomISAReg<18, "R18">, DwarfRegNum<[18]>;
def R19 : CustomISAReg<19, "R19">, DwarfRegNum<[19]>;
def R20 : CustomISAReg<20, "R20">, DwarfRegNum<[20]>;
def R21 : CustomISAReg<21, "R21">, DwarfRegNum<[21]>;
def R22 : CustomISAReg<22, "R22">, DwarfRegNum<[22]>;
def R23 : CustomISAReg<23, "R23">, DwarfRegNum<[23]>;
def R24 : CustomISAReg<24, "R24">, DwarfRegNum<[24]>;
def R25 : CustomISAReg<25, "R25">, DwarfRegNum<[25]>;
def R26 : CustomISAReg<26, "R26">, DwarfRegNum<[26]>;
def R27 : CustomISAReg<27, "R27">, DwarfRegNum<[27]>;
def R28 : CustomISAReg<28, "R28">, DwarfRegNum<[28]>;
def R29 : CustomISAReg<29, "R29">, DwarfRegNum<[29]>;
def R30 : CustomISAReg<30, "R30">, DwarfRegNum<[30]>;
def R31 : CustomISAReg<31, "R31">, DwarfRegNum<[31]>;
def R32 : CustomISAReg<32, "R32">, DwarfRegNum<[32]>;
def R33 : CustomISAReg<33, "R33">, DwarfRegNum<[33]>;
def R34 : CustomISAReg<34, "R34">, DwarfRegNum<[34]>;
def R35 : CustomISAReg<35, "R35">, DwarfRegNum<[35]>;
def R36 : CustomISAReg<36, "R36">, DwarfRegNum<[36]>;
def R37 : CustomISAReg<37, "R37">, DwarfRegNum<[37]>;
def R38 : CustomISAReg<38, "R38">, DwarfRegNum<[38]>;
def R39 : CustomISAReg<39, "R39">, DwarfRegNum<[39]>;
def R40 : CustomISAReg<40, "R40">, DwarfRegNum<[40]>;
def R41 : CustomISAReg<41, "R41">, DwarfRegNum<[41]>;
def R42 : CustomISAReg<42, "R42">, DwarfRegNum<[42]>;
def R43 : CustomISAReg<43, "R43">, DwarfRegNum<[43]>;
def R44 : CustomISAReg<44, "R44">, DwarfRegNum<[44]>;
def R45 : CustomISAReg<45, "R45">, DwarfRegNum<[45]>;
def R46 : CustomISAReg<46, "R46">, DwarfRegNum<[46]>;
def R47 : CustomISAReg<47, "R47">, DwarfRegNum<[47]>;
def R48 : CustomISAReg<48, "R48">, DwarfRegNum<[48]>;
def R49 : CustomISAReg<49, "R49">, DwarfRegNum<[49]>;
def R50 : CustomISAReg<50, "R50">, DwarfRegNum<[50]>;
def R51 : CustomISAReg<51, "R51">, DwarfRegNum<[51]>;
def R52 : CustomISAReg<52, "R52">, DwarfRegNum<[52]>;
def R53 : CustomISAReg<53, "R53">, DwarfRegNum<[53]>;
def R54 : CustomISAReg<54, "R54">, DwarfRegNum<[54]>;
def R55 : CustomISAReg<55, "R55">, DwarfRegNum<[55]>;
def R56 : CustomISAReg<56, "R56">, DwarfRegNum<[56]>;
def R57 : CustomISAReg<57, "R57">, DwarfRegNum<[57]>;
def R58 : CustomISAReg<58, "R58">, DwarfRegNum<[58]>;
def R59 : CustomISAReg<59, "R59">, DwarfRegNum<[59]>;
def R60 : CustomISAReg<60, "R60">, DwarfRegNum<[60]>;
def R61 : CustomISAReg<61, "R61">, DwarfRegNum<[61]>;
def R62 : CustomISAReg<62, "R62">, DwarfRegNum<[62]>;
def R63 : CustomISAReg<63, "R63">, DwarfRegNum<[63]>;

// Special registers (not in GPR space, separate encoding)
// LR is a dedicated register for JAL/JALR (link register)
def LR  : CustomISAReg<63, "LR">,  DwarfRegNum<[63]>;  // Link register (R63)
// SP and FP are conventions using general registers (R61, R62)
// PC is separate architectural state, not a register

//===----------------------------------------------------------------------===//
// Register Classes
//===----------------------------------------------------------------------===//

// All general purpose registers (R0-R63)
def GPR : RegisterClass<"CustomISA", [i32], 32, (add
  R0, R1, R2, R3, R4, R5, R6, R7,
  R8, R9, R10, R11, R12, R13, R14, R15,
  R16, R17, R18, R19, R20, R21, R22, R23,
  R24, R25, R26, R27, R28, R29, R30, R31,
  R32, R33, R34, R35, R36, R37, R38, R39,
  R40, R41, R42, R43, R44, R45, R46, R47,
  R48, R49, R50, R51, R52, R53, R54, R55,
  R56, R57, R58, R59, R60, R61, R62, R63)> {
}

// Special register classes
def LRReg : RegisterClass<"CustomISA", [i32], 32, (add LR)>;
def SPReg : RegisterClass<"CustomISA", [i32], 32, (add SP)>;
def FPReg : RegisterClass<"CustomISA", [i32], 32, (add FP)>;
def PCReg : RegisterClass<"CustomISA", [i32], 32, (add PC)>;

// Register class for registers that can be used as base in memory operands
// R0 is hardwired to 0, R63 is LR, so exclude those
def GPRBase : RegisterClass<"CustomISA", [i32], 32, (add
  R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15,
  R16, R17, R18, R19, R20, R21, R22, R23, R24, R25, R26, R27, R28, R29, R30, R31,
  R32, R33, R34, R35, R36, R37, R38, R39, R40, R41, R42, R43, R44, R45, R46, R47,
  R48, R49, R50, R51, R52, R53, R54, R55, R56, R57, R58, R59, R60, R61, R62)>;

// Callee-saved registers (R8-R15, R61=SP, R62=FP, R63=LR)
def CalleeSavedRegs : RegisterClass<"CustomISA", [i32], 32, (add
  R8, R9, R10, R11, R12, R13, R14, R15,
  R61, R62, R63)>;

// Caller-saved registers (R1-R7, R16-R60)
def CallerSavedRegs : RegisterClass<"CustomISA", [i32], 32, (add
  R1, R2, R3, R4, R5, R6, R7,
  R16, R17, R18, R19, R20, R21, R22, R23,
  R24, R25, R26, R27, R28, R29, R30, R31,
  R32, R33, R34, R35, R36, R37, R38, R39,
  R40, R41, R42, R43, R44, R45, R46, R47,
  R48, R49, R50, R51, R52, R53, R54, R55,
  R56, R57, R58, R59, R60)>;

// Register tuples for 64-bit values (not used in this 32-bit ISA, but kept for completeness)
def GPRPair : RegisterClass<"CustomISA", [i64], 64, (add
  R0, R1, R2, R3, R4, R5, R6, R7,
  R8, R9, R10, R11, R12, R13, R14, R15,
  R16, R17, R18, R19, R20, R21, R22, R23,
  R24, R25, R26, R27, R28, R29, R30, R31,
  R32, R33, R34, R35, R36, R37, R38, R39,
  R40, R41, R42, R43, R44, R45, R46, R47,
  R48, R49, R50, R51, R52, R53, R54, R55,
  R56, R57, R58, R59, R60, R61, R62, R63)>;
