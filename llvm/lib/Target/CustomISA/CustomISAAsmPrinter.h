//===-- CustomISAAsmPrinter.h - CustomISA Assembly Printer ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAASMPRINTER_H
#define LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAASMPRINTER_H

#include "llvm/CodeGen/AsmPrinter.h"

namespace llvm {

class CustomISAAsmPrinter : public AsmPrinter {
  virtual void anchor();

public:
  explicit CustomISAAsmPrinter(TargetMachine &TM,
                               std::unique_ptr<MCStreamer> Streamer);
  ~CustomISAAsmPrinter() override = default;

  void emitInstruction(const MachineInstr *MI) override;

  void lowerCustomISAInstr(const MachineInstr *MI, MCInst &OutMI) const;

  bool PrintAsmOperand(const MachineInstr *MI, unsigned OpNum,
                       unsigned AsmVariant, const char *ExtraCode,
                       raw_ostream &O) override;

  bool PrintAsmMemoryOperand(const MachineInstr *MI, unsigned OpNum,
                             unsigned AsmVariant, const char *ExtraCode,
                             raw_ostream &O) override;

  void emitFunctionEntryLabel() override;
  void emitFunctionBodyStart() override;
  void emitFunctionBodyEnd() override;

  void emitStartOfAsmFile(Module &M) override;
  void emitEndOfAsmFile(Module &M) override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAASMPRINTER_H
