//===-- CustomISAInstPrinter.h - CustomISA Assembly Printer ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAINSTPRINTER_H
#define LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAINSTPRINTER_H

#include "llvm/MC/MCInstPrinter.h"

namespace llvm {

class MCAsmInfo;
class MCInstrInfo;
class MCRegisterInfo;
class MCInst;

class CustomISAInstPrinter : public MCInstPrinter {
  virtual void anchor();

public:
  CustomISAInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                       const MCRegisterInfo &MRI);
  ~CustomISAInstPrinter() override = default;

  void printInst(const MCInst *MI, raw_ostream &OS, StringRef Annot,
                 const MCSubtargetInfo &STI) override;

  void printOperand(const MCInst *MI, unsigned OpNum, raw_ostream &OS,
                    const char *Modifier = nullptr) override;

  void printRegName(raw_ostream &OS, unsigned RegNo) const override;

  // Custom operand printing
  void printMemOperand(const MCInst *MI, unsigned OpNum, raw_ostream &OS,
                       const char *Modifier = nullptr);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAINSTPRINTER_H
