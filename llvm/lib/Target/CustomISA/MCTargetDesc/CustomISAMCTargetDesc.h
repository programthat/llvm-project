//===-- CustomISAMCTargetDesc.h - CustomISA Target Descriptions -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides CustomISA specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_MCTARGETDESC_CUSTOMISAMCTARGETDESC_H
#define LLVM_LIB_TARGET_CUSTOMISA_MCTARGETDESC_CUSTOMISAMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/Target/Target.h"

namespace llvm {
class Target;
class Triple;
class StringRef;
class MCTargetOptions;

MCInstrInfo *createCustomISAInstrInfo();
MCRegisterInfo *createCustomISARegisterInfo(const Triple &TT);
MCSubtargetInfo *createCustomISASubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS);
MCAsmInfo *createCustomISAMCAsmInfo(const MCRegisterInfo &MRI, const Triple &TT, const MCTargetOptions &Options);
MCInstPrinter *createCustomISAMCInstPrinter(const Triple &TT, unsigned SyntaxVariant, const MCAsmInfo &MAI, const MCInstrInfo &MII, const MCRegisterInfo &MRI);
MCCodeEmitter *createCustomISAMCCodeEmitter(const MCInstrInfo &MII, const MCRegisterInfo &MRI, MCContext &Ctx);
MCAsmBackend *createCustomISAMCAsmBackend(const Target &T, const MCSubtargetInfo &STI, const MCRegisterInfo &MRI, const MCTargetOptions &Options);

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_MCTARGETDESC_CUSTOMISAMCTARGETDESC_H
