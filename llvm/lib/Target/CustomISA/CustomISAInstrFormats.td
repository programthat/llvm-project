//===-- CustomISAInstrFormats.td - CustomISA Instruction Formats ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the instruction formats for CustomISA.
//
// Instruction format: Opcode (8 bits) | Args (dynamic length) | Padding
// Total: 32 bits (4 bytes)
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"
include "CustomISARegisters.td"

//===----------------------------------------------------------------------===//
// Operand Types
//===----------------------------------------------------------------------===//

// 6-bit register operand (R0-R63)
def gpr : Operand<i32> {
  let EncoderMethod = "getGPRRegOpValue";
  let DecoderMethod = "DecodeGPRRegisterOperand";
  let OperandType = "OPERAND_GPR";
}

// 6-bit register operand for base register in memory operations (excludes R0, R63)
def gprbase : Operand<i32> {
  let EncoderMethod = "getGPRRegOpValue";
  let DecoderMethod = "DecodeGPRRegisterOperand";
  let OperandType = "OPERAND_GPRBASE";
}

// 12-bit immediate operand (for shifts, memory offsets)
def imm12 : Operand<i32> {
  let EncoderMethod = "getImm12OpValue";
  let DecoderMethod = "DecodeImm12Operand";
  let OperandType = "OPERAND_IMM12";
}

// 18-bit immediate operand (for LDI, jumps)
def imm18 : Operand<i32> {
  let EncoderMethod = "getImm18OpValue";
  let DecoderMethod = "DecodeImm18Operand";
  let OperandType = "OPERAND_IMM18";
}

// 6-bit flag ID operand
def flagid : Operand<i32> {
  let EncoderMethod = "getFlagIdOpValue";
  let DecoderMethod = "DecodeFlagIdOperand";
  let OperandType = "OPERAND_FLAGID";
}

//===----------------------------------------------------------------------===//
// Instruction Format Classes
//===----------------------------------------------------------------------===//

// Base instruction class - all instructions are 32 bits (4 bytes)
class CustomISAInst<bits<8> opc, string asm, list<dag> ops, InstrItinClass itin>
    : Instruction {
  let Namespace = "CustomISA";
  let OutOperandList = ops.OutOperandList;
  let InOperandList = ops.InOperandList;
  let AsmString = asm;
  let TSFlags = 0;
  let Itinerary = itin;
  let Size = 4; // 32 bits = 4 bytes
  let Opcode = opc;
}

// Format: OPCODE Rd(6) Ra(6) Rb(6) padding(6) - 3 register operands (ADD, SUB, etc.)
class RRRInst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs GPR:$Rd), (ins GPR:$Ra, GPR:$Rb), itin> {
  let Constraints = "$Rd = $Ra";
}

// Format: OPCODE Rd(6) Ra(6) imm(12) - 2 register operands + 12-bit immediate (SHL, SHR)
class RRI12Inst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs GPR:$Rd), (ins GPR:$Ra, imm12:$imm), itin> {
  let Constraints = "$Rd = $Ra";
}

// Format: OPCODE Rd(6) Ra(6) padding(12) - 2 register operands (NOT)
class RRInst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs GPR:$Rd), (ins GPR:$Ra), itin> {
  let Constraints = "$Rd = $Ra";
}

// Format: OPCODE Rd(6) imm(18) padding(0) - Load immediate (LDI)
class LDIInst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs GPR:$Rd), (ins imm18:$imm), itin> {}

// Format: OPCODE Ra(6) Rb(6) imm(12) - Memory operations (LOAD, STORE)
class MemInst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs GPR:$Ra), (ins GPRBase:$Rb, imm12:$imm), itin> {}

// Format: OPCODE Ra(6) Rb(6) padding(12) - Register-register memory (LOADR, STORER)
class MemRRInst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs GPR:$Ra), (ins GPRBase:$Rb), itin> {}

// Format: OPCODE Ra(6) Rb(6) padding(12) - Compare (CMP)
class CMPInst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs), (ins GPR:$Ra, GPR:$Rb), itin> {}

// Format: OPCODE Ra(6) imm(18) - Unconditional jumps (JMP, JMO)
class JumpInst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs), (ins GPR:$Ra, imm18:$imm), itin> {}

// Format: OPCODE Ra(6) imm(12) flagid(6) - Conditional jumps (JMC, JMCO)
class CondJumpInst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs), (ins GPR:$Ra, imm12:$imm, flagid:$flag), itin> {}

// Format: OPCODE LR(6) imm(18) - Jump and link (JAL)
class JALInst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs GPR:$LR), (ins imm18:$imm), itin> {}

// Format: OPCODE LR(6) Ra(6) imm(12) - Jump and link register (JALR)
class JALRInst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs GPR:$LR), (ins GPR:$Ra, imm12:$imm), itin> {}

// Format: OPCODE (no operands - NOP, HALT)
class ZeroOpInst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs), (ins), itin> {}

// Format: OPCODE ? ? ? (ECALL - environment call)
class ECallInst<bits<8> opc, string asm, InstrItinClass itin>
    : CustomISAInst<opc, asm, (outs), (ins GPR:$arg1, GPR:$arg2, GPR:$arg3), itin> {}
