//===-- CustomISAInstrInfo.td - CustomISA Instruction Definitions ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the CustomISA instructions.
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"
include "CustomISAInstrFormats.td"

//===----------------------------------------------------------------------===//
// Instruction Scheduling/Itineraries
//===----------------------------------------------------------------------===//

def CustomISAItineraries : ProcessorItineraries<[], [], []>;

// Simple itinerary classes
def IIAlu  : InstrItinClass<IIAlu>;
def IILoad : InstrItinClass<IILoad>;
def IIStore : InstrItinClass<IIStore>;
def IIBranch : InstrItinClass<IIBranch>;
def IIJump : InstrItinClass<IIJump>;
def IICall : InstrItinClass<IICall>;
def IIMul : InstrItinClass<IIMul>;
def IIDiv : InstrItinClass<IIDiv>;

//===----------------------------------------------------------------------===//
// Instruction Definitions
//===----------------------------------------------------------------------===//

// NOP - No operation
def NOP : ZeroOpInst<0, "nop", IIAlu>;

// HALT - Stop the program
def HALT : ZeroOpInst<1, "halt", IIAlu>;

// ECALL - Environment call
def ECALL : ECallInst<2, "ecall", IIAlu>;

// ADD - Rd = Ra + Rb
def ADD : RRRInst<14, "add $Rd, $Ra, $Rb", IIAlu>;

// SUB - Rd = Ra - Rb
def SUB : RRRInst<25, "sub $Rd, $Ra, $Rb", IIAlu>;

// DIV - Rd = Ra / Rb (integer division)
def DIV : RRRInst<26, "div $Rd, $Ra, $Rb", IIDiv>;

// MULL - Multiply lower 32 bits
def MULL : RRRInst<27, "mull $Rd, $Ra, $Rb", IIMul>;

// MULHU - Multiply unsigned upper 32 bits
def MULHU : RRRInst<28, "mulhu $Rd, $Ra, $Rb", IIMul>;

// MULHS - Multiply signed upper 32 bits
def MULHS : RRRInst<29, "mulhs $Rd, $Ra, $Rb", IIMul>;

// AND - Rd = Ra & Rb
def AND : RRRInst<30, "and $Rd, $Ra, $Rb", IIAlu>;

// OR - Rd = Ra | Rb
def OR : RRRInst<31, "or $Rd, $Ra, $Rb", IIAlu>;

// XOR - Rd = Ra ^ Rb
def XOR : RRRInst<32, "xor $Rd, $Ra, $Rb", IIAlu>;

// NOT - Rd = ~Ra
def NOT : RRInst<33, "not $Rd, $Ra", IIAlu>;

// SHL - Rd = Ra << imm12
def SHL : RRI12Inst<34, "shl $Rd, $Ra, $imm", IIAlu>;

// SHLR - Rd = Ra << Rb
def SHLR : RRRInst<35, "shlr $Rd, $Ra, $Rb", IIAlu>;

// SHR - Rd = Ra >> imm12 (logical shift right)
def SHR : RRI12Inst<36, "shr $Rd, $Ra, $imm", IIAlu>;

// SHRR - Rd = Ra >> Rb (logical shift right)
def SHRR : RRRInst<37, "shrr $Rd, $Ra, $Rb", IIAlu>;

// LDI - Load immediate (18-bit immediate)
def LDI : LDIInst<40, "ldi $Rd, $imm", IIAlu>;

// ADDI - Add immediate (not yet defined in ISA, placeholder)
// def ADDI : RRI12Inst<41, "addi $Rd, $Ra, $imm", IIAlu>;

// LOAD - Ra = memory[Rb + imm12]
def LOAD : MemInst<44, "load $Ra, $Rb, $imm", IILoad>;

// STORE - memory[Rb + imm12] = Ra
def STORE : MemInst<45, "store $Ra, $Rb, $imm", IIStore>;

// LOADR - Ra = memory[Rb]
def LOADR : MemRRInst<46, "loadr $Ra, $Rb", IILoad>;

// STORER - memory[Rb] = Ra
def STORER : MemRRInst<47, "storer $Ra, $Rb", IIStore>;

// CMP - Compare Ra and Rb, set flags
def CMP : CMPInst<49, "cmp $Ra, $Rb", IIAlu>;

// JMP - PC = Ra + imm18
def JMP : JumpInst<50, "jmp $Ra, $imm", IIJump>;

// JMO - PC += Ra + imm18 (offset jump)
def JMO : JumpInst<51, "jmo $Ra, $imm", IIJump>;

// JMC - if flags[flag_id]: PC = Ra + imm12
def JMC : CondJumpInst<52, "jmc $Ra, $imm, $flag", IIBranch>;

// JMCO - if flags[flag_id]: PC += Ra + imm12 (offset conditional jump)
def JMCO : CondJumpInst<53, "jmco $Ra, $imm, $flag", IIBranch>;

// JAL - LR = PC + 1; PC += imm18 (jump and link)
def JAL : JALInst<58, "jal $imm", IICall>;

// JALR - LR = PC + 1; PC += Ra + imm12 (jump and link register)
def JALR : JALRInst<59, "jalr $LR, $Ra, $imm", IICall>;

// RET - Pseudo-instruction (alias for JALR R0, LR, 0)
// This is handled in the assembler, not as a real instruction

//===----------------------------------------------------------------------===//
// Pseudo Instructions
//===----------------------------------------------------------------------===//

// Pseudo-instruction for RET (expands to JALR R0, LR, 0)
def RET : PseudoInst<"ret", (outs), (ins), IIBranch> {
  let isPseudo = 1;
}

// Pseudo-instruction for MOV (expands to ADD Rd, Ra, R0)
def MOV : PseudoInst<"mov $Rd, $Ra", (outs GPR:$Rd), (ins GPR:$Ra), IIAlu> {
  let isPseudo = 1;
}

// Pseudo-instruction for LI (load immediate - alias for LDI)
def LI : PseudoInst<"li $Rd, $imm", (outs GPR:$Rd), (ins imm18:$imm), IIAlu> {
  let isPseudo = 1;
}

// Pseudo-instruction for branch if equal (BEQ - expands to CMP + JMC EQ)
def BEQ : PseudoInst<"beq $Ra, $Rb, $imm", (outs), (ins GPR:$Ra, GPR:$Rb, imm12:$imm), IIBranch> {
  let isPseudo = 1;
}

// Pseudo-instruction for branch if not equal (BNE)
def BNE : PseudoInst<"bne $Ra, $Rb, $imm", (outs), (ins GPR:$Ra, GPR:$Rb, imm12:$imm), IIBranch> {
  let isPseudo = 1;
}

// Pseudo-instruction for branch if less than (BLT)
def BLT : PseudoInst<"blt $Ra, $Rb, $imm", (outs), (ins GPR:$Ra, GPR:$Rb, imm12:$imm), IIBranch> {
  let isPseudo = 1;
}

// Pseudo-instruction for branch if greater than (BGT)
def BGT : PseudoInst<"bgt $Ra, $Rb, $imm", (outs), (ins GPR:$Ra, GPR:$Rb, imm12:$imm), IIBranch> {
  let isPseudo = 1;
}

// Pseudo-instruction for CALL (alias for JAL)
def CALL : PseudoInst<"call $imm", (outs), (ins imm18:$imm), IICall> {
  let isPseudo = 1;
}

// Pseudo-instruction for JR (jump register - JMP R0, Ra, 0)
def JR : PseudoInst<"jr $Ra", (outs), (ins GPR:$Ra), IIJump> {
  let isPseudo = 1;
}

// Pseudo-instruction for JALR with R0 (JALR R0, Ra, 0)
def JALR_R0 : PseudoInst<"jalr $Ra", (outs GPR:$LR), (ins GPR:$Ra), IICall> {
  let isPseudo = 1;
}
