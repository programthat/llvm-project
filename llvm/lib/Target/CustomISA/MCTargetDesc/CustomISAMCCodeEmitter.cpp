//===-- CustomISAMCCodeEmitter.cpp - CustomISA MC Code Emitter ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISAMCCodeEmitter.h"
#include "CustomISAMCTargetDesc.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "CustomISAGenInstrInfo.inc"

void CustomISAMCCodeEmitter::encodeInstruction(const MCInst &MI, raw_ostream &OS,
                                               SmallVectorImpl<MCFixup> &Fixups,
                                               const MCSubtargetInfo &STI) const {
  // Get the instruction opcode
  unsigned Opcode = MI.getOpcode();
  const MCInstrDesc &Desc = MCII.get(Opcode);

  // Get the binary encoding from the instruction descriptor
  uint64_t Bits = 0;

  // Encode opcode (8 bits)
  Bits |= (uint64_t)(Desc.getOpcode()) << 24;

  // Encode operands based on instruction format
  // This is a simplified implementation - real implementation would use
  // the generated encoder tables from tablegen

  // Write as big-endian 32-bit value
  support::endian::write32be(OS, (uint32_t)Bits);
}

unsigned CustomISAMCCodeEmitter::getMachineOpValue(const MCInst &MI,
                                                   const MCOperand &MO,
                                                   SmallVectorImpl<MCFixup> &Fixups,
                                                   const MCSubtargetInfo &STI) const {
  if (MO.isReg()) {
    return MRI.getEncodingValue(MO.getReg());
  } else if (MO.isImm()) {
    return (unsigned)MO.getImm();
  } else if (MO.isExpr()) {
    // Handle relocations
    Fixups.push_back(MCFixup::create(0, MO.getExpr(), MCFixupKind(0)));
    return 0;
  }
  return 0;
}

unsigned CustomISAMCCodeEmitter::getGPRRegOpValue(const MCInst &MI,
                                                  const MCOperand &MO,
                                                  SmallVectorImpl<MCFixup> &Fixups,
                                                  const MCSubtargetInfo &STI) const {
  if (MO.isReg()) {
    return MRI.getEncodingValue(MO.getReg());
  }
  return 0;
}

unsigned CustomISAMCCodeEmitter::getImm12OpValue(const MCInst &MI,
                                                 const MCOperand &MO,
                                                 SmallVectorImpl<MCFixup> &Fixups,
                                                 const MCSubtargetInfo &STI) const {
  if (MO.isImm()) {
    int64_t Imm = MO.getImm();
    // 12-bit signed immediate
    return (unsigned)(Imm & 0xFFF);
  }
  return 0;
}

unsigned CustomISAMCCodeEmitter::getImm18OpValue(const MCInst &MI,
                                                 const MCOperand &MO,
                                                 SmallVectorImpl<MCFixup> &Fixups,
                                                 const MCSubtargetInfo &STI) const {
  if (MO.isImm()) {
    int64_t Imm = MO.getImm();
    // 18-bit signed immediate
    return (unsigned)(Imm & 0x3FFFF);
  }
  return 0;
}

unsigned CustomISAMCCodeEmitter::getFlagIdOpValue(const MCInst &MI,
                                                  const MCOperand &MO,
                                                  SmallVectorImpl<MCFixup> &Fixups,
                                                  const MCSubtargetInfo &STI) const {
  if (MO.isImm()) {
    int64_t Imm = MO.getImm();
    // 6-bit flag ID
    return (unsigned)(Imm & 0x3F);
  }
  return 0;
}
