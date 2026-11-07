//===-- CustomISAMCAsmBackend.h - CustomISA MC Asm Backend ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_MCTARGETDESC_CUSTOMISAMCASBACKEND_H
#define LLVM_LIB_TARGET_CUSTOMISA_MCTARGETDESC_CUSTOMISAMCASBACKEND_H

#include "llvm/MC/MCAsmBackend.h"

namespace llvm {

class MCAssembler;
class MCObjectWriter;
class MCFixup;
class MCValue;
class MCTargetOptions;
class raw_pwrite_stream;
class StringRef;
class Triple;

class CustomISAMCAsmBackend : public MCAsmBackend {
  virtual void anchor();

public:
  CustomISAMCAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                        const MCRegisterInfo &MRI, const MCTargetOptions &Options);
  ~CustomISAMCAsmBackend() override = default;

  unsigned getNumFixupKinds() const override { return 1; }

  bool mayNeedRelaxation(const MCInst &Inst, const MCSubtargetInfo &STI) const override {
    return false;
  }

  void relaxInstruction(const MCInst &Inst, const MCSubtargetInfo &STI,
                        MCInst &Res) const override {}

  bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
                            const MCRelaxableFragment *DF,
                            const MCAsmLayout &Layout) const override {
    return false;
  }

  unsigned getFixupKindInfo(unsigned Kind) const override;

  bool writeNopData(raw_pwrite_stream &OS, uint64_t Count,
                    const MCSubtargetInfo *STI) const override;

  std::unique_ptr<MCObjectWriter>
  createObjectWriter(raw_pwrite_stream &OS) const override;

  bool isLittleEndian() const override { return false; }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_MCTARGETDESC_CUSTOMISAMCASBACKEND_H
