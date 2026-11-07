//===-- CustomISAAsmPrinter.cpp - CustomISA Assembly Printer --------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISAAsmPrinter.h"
#include "CustomISAMachineFunctionInfo.h"
#include "CustomISAInstrInfo.h"
#include "CustomISATargetMachine.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "customisa-asm-printer"

CustomISAAsmPrinter::CustomISAAsmPrinter(TargetMachine &TM,
                                         std::unique_ptr<MCStreamer> Streamer)
    : AsmPrinter(TM, std::move(Streamer)) {}

void CustomISAAsmPrinter::emitInstruction(const MachineInstr *MI) {
  // Convert MachineInstr to MCInst and emit
  MCInst TmpInst;
  lowerCustomISAInstr(MI, TmpInst);
  OutStreamer->emitInstruction(TmpInst, getSubtargetInfo());
}

void CustomISAAsmPrinter::lowerCustomISAInstr(const MachineInstr *MI,
                                              MCInst &OutMI) const {
  OutMI.setOpcode(MI->getOpcode());

  for (const MachineOperand &MO : MI->operands()) {
    MCOperand MCOp;

    if (MO.isReg()) {
      if (MO.isImplicit())
        continue;
      MCOp = MCOperand::createReg(MO.getReg());
    } else if (MO.isImm()) {
      MCOp = MCOperand::createImm(MO.getImm());
    } else if (MO.isFPImm()) {
      // Not used in this ISA
      continue;
    } else if (MO.isSymbol()) {
      MCSymbol *Sym = GetExternalSymbolSymbol(MO.getSymbolName());
      MCOp = MCOperand::createExpr(MCSymbolRefExpr::create(Sym, OutContext));
    } else {
      llvm_unreachable("Unknown operand type");
    }

    OutMI.addOperand(MCOp);
  }
}

bool CustomISAAsmPrinter::PrintAsmOperand(const MachineInstr *MI, unsigned OpNum,
                                          unsigned AsmVariant,
                                          const char *ExtraCode,
                                          raw_ostream &O) {
  // Custom operand printing for inline asm
  return AsmPrinter::PrintAsmOperand(MI, OpNum, AsmVariant, ExtraCode, O);
}

bool CustomISAAsmPrinter::PrintAsmMemoryOperand(const MachineInstr *MI,
                                                unsigned OpNum,
                                                unsigned AsmVariant,
                                                const char *ExtraCode,
                                                raw_ostream &O) {
  // Custom memory operand printing for inline asm
  return AsmPrinter::PrintAsmMemoryOperand(MI, OpNum, AsmVariant, ExtraCode, O);
}

void CustomISAAsmPrinter::emitFunctionEntryLabel() {
  // Emit function entry label
  AsmPrinter::emitFunctionEntryLabel();
}

void CustomISAAsmPrinter::emitFunctionBodyStart() {
  // Emit function body start
  AsmPrinter::emitFunctionBodyStart();
}

void CustomISAAsmPrinter::emitFunctionBodyEnd() {
  // Emit function body end
  AsmPrinter::emitFunctionBodyEnd();
}

void CustomISAAsmPrinter::emitStartOfAsmFile(Module &M) {
  // Emit file header
  OutStreamer->emitRawText("\t.file\t\"" + M.getSourceFileName() + "\"");
  OutStreamer->emitRawText("\t.section .text");
}

void CustomISAAsmPrinter::emitEndOfAsmFile(Module &M) {
  // Emit file footer
  AsmPrinter::emitEndOfAsmFile(M);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeCustomISAAsmPrinter() {
  RegisterAsmPrinter<CustomISAAsmPrinter> X(getTheCustomISATarget());
}
