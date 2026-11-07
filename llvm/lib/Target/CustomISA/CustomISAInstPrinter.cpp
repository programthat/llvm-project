//===-- CustomISAInstPrinter.cpp - CustomISA Assembly Printer -------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISAInstPrinter.h"
#include "CustomISAMCTargetDesc.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "CustomISAGenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "CustomISAGenRegisterInfo.inc"

CustomISAInstPrinter::CustomISAInstPrinter(const MCAsmInfo &MAI,
                                           const MCInstrInfo &MII,
                                           const MCRegisterInfo &MRI)
    : MCInstPrinter(MAI, MII, MRI) {}

void CustomISAInstPrinter::printInst(const MCInst *MI, raw_ostream &OS,
                                     StringRef Annot,
                                     const MCSubtargetInfo &STI) {
  // Print the instruction mnemonic and operands
  printInstruction(MI, OS);
  printAnnotation(OS, Annot);
}

void CustomISAInstPrinter::printOperand(const MCInst *MI, unsigned OpNum,
                                        raw_ostream &OS,
                                        const char *Modifier) {
  const MCOperand &Op = MI->getOperand(OpNum);

  if (Op.isReg()) {
    printRegName(OS, Op.getReg());
  } else if (Op.isImm()) {
    OS << Op.getImm();
  } else if (Op.isExpr()) {
    Op.getExpr()->print(OS, &MAI);
  } else {
    llvm_unreachable("Unknown operand type");
  }
}

void CustomISAInstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const {
  // Register names are defined in the generated register info
  OS << getRegisterName(RegNo);
}

void CustomISAInstPrinter::printMemOperand(const MCInst *MI, unsigned OpNum,
                                           raw_ostream &OS,
                                           const char *Modifier) {
  // Memory operand format: base + offset
  // For CustomISA: Ra = mem[Rb + imm]
  const MCOperand &Base = MI->getOperand(OpNum);
  const MCOperand &Offset = MI->getOperand(OpNum + 1);

  OS << "[";
  printOperand(MI, OpNum, OS);
  if (Offset.isImm() && Offset.getImm() != 0) {
    OS << " + " << Offset.getImm();
  }
  OS << "]";
}
