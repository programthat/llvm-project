//===-- CustomISAMCAsmBackend.cpp - CustomISA MC Asm Backend --------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISAMCAsmBackend.h"
#include "CustomISAMCTargetDesc.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {

class CustomISAELFObjectWriter : public MCELFObjectTargetWriter {
public:
  CustomISAELFObjectWriter(uint8_t OSABI)
      : MCELFObjectTargetWriter(/*Is64Bit*/ false, OSABI, ELF::EM_NONE,
                                /*HasRelocationAddend*/ false) {}

  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override {
    // Custom relocation types would be defined here
    return ELF::R_386_NONE;
  }
};

} // end anonymous namespace

CustomISAMCAsmBackend::CustomISAMCAsmBackend(const Target &T,
                                             const MCSubtargetInfo &STI,
                                             const MCRegisterInfo &MRI,
                                             const MCTargetOptions &Options)
    : MCAsmBackend(support::big) {}

unsigned CustomISAMCAsmBackend::getFixupKindInfo(unsigned Kind) const {
  // Define fixup kinds
  static const MCFixupKindInfo Infos[] = {
    // Fixup for 18-bit immediate
    {"FK_CustomISA_18", 0, 18, MCFixupKindInfo::FKF_IsPCRel},
    // Fixup for 12-bit immediate
    {"FK_CustomISA_12", 0, 12, 0},
  };

  if (Kind < array_lengthof(Infos))
    return Infos[Kind].Kind;
  return 0;
}

bool CustomISAMCAsmBackend::writeNopData(raw_pwrite_stream &OS, uint64_t Count,
                                         const MCSubtargetInfo *STI) const {
  // NOP is 0x00000000 (32 bits)
  for (uint64_t i = 0; i < Count; ++i) {
    OS.write("\x00\x00\x00\x00", 4);
  }
  return true;
}

std::unique_ptr<MCObjectWriter>
CustomISAMCAsmBackend::createObjectWriter(raw_pwrite_stream &OS) const {
  return createCustomISAELFObjectWriter(OS, MCELFObjectTargetWriter::getOSABI());
}
