//===-- CustomISAMCCodeEmitter.h - CustomISA MC Code Emitter --------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_MCTARGETDESC_CUSTOMISAMCCODEEMITTER_H
#define LLVM_LIB_TARGET_CUSTOMISA_MCTARGETDESC_CUSTOMISAMCCODEEMITTER_H

#include "llvm/MC/MCCodeEmitter.h"

namespace llvm {

class MCContext;
class MCExpr;
class MCInst;
class MCInstrInfo;
class MCRegisterInfo;
class MCOperand;
class raw_ostream;

class CustomISAMCCodeEmitter : public MCCodeEmitter {
  virtual void anchor();

  const MCInstrInfo &MCII;
  const MCRegisterInfo &MRI;
  MCContext &Ctx;

public:
  CustomISAMCCodeEmitter(const MCInstrInfo &MCII, const MCRegisterInfo &MRI,
                         MCContext &Ctx)
      : MCII(MCII), MRI(MRI), Ctx(Ctx) {}
  ~CustomISAMCCodeEmitter() override = default;

  void encodeInstruction(const MCInst &MI, raw_ostream &OS,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;

  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const override;

  // Custom operand encoding
  unsigned getGPRRegOpValue(const MCInst &MI, const MCOperand &MO,
                            SmallVectorImpl<MCFixup> &Fixups,
                            const MCSubtargetInfo &STI) const;
  unsigned getImm12OpValue(const MCInst &MI, const MCOperand &MO,
                           SmallVectorImpl<MCFixup> &Fixups,
                           const MCSubtargetInfo &STI) const;
  unsigned getImm18OpValue(const MCInst &MI, const MCOperand &MO,
                           SmallVectorImpl<MCFixup> &Fixups,
                           const MCSubtargetInfo &STI) const;
  unsigned getFlagIdOpValue(const MCInst &MI, const MCOperand &MO,
                            SmallVectorImpl<MCFixup> &Fixups,
                            const MCSubtargetInfo &STI) const;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_MCTARGETDESC_CUSTOMISAMCCODEEMITTER_H
