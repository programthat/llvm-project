//===-- CustomISAMCTargetDesc.cpp - CustomISA Target Descriptions ---------===//
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

#include "CustomISAMCTargetDesc.h"
#include "CustomISAMCAsmInfo.h"
#include "CustomISATargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "CustomISAGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "CustomISAGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "CustomISAGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createCustomISAInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitCustomISAInstrInfo(X);
  return X;
}

static MCRegisterInfo *createCustomISARegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitCustomISARegisterInfo(X, LR);
  return X;
}

static MCSubtargetInfo *createCustomISASubtargetInfo(const Triple &TT,
                                                     StringRef CPU,
                                                     StringRef FS) {
  return createCustomISASubtargetInfoImpl(TT, CPU, FS);
}

static MCAsmInfo *createCustomISAMCAsmInfo(const MCRegisterInfo &MRI,
                                           const Triple &TT,
                                           const MCTargetOptions &Options) {
  return new CustomISAMCAsmInfo(TT);
}

static MCInstPrinter *createCustomISAMCInstPrinter(const Triple &TT,
                                                   unsigned SyntaxVariant,
                                                   const MCAsmInfo &MAI,
                                                   const MCInstrInfo &MII,
                                                   const MCRegisterInfo &MRI) {
  return new CustomISAMCInstPrinter(MAI, MII, MRI);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeCustomISATargetMC() {
  // Register the MC asm info
  RegisterMCAsmInfoFn X(getTheCustomISATarget(), createCustomISAMCAsmInfo);

  // Register the MC instruction info
  TargetRegistry::RegisterMCInstrInfo(getTheCustomISATarget(),
                                      createCustomISAInstrInfo);

  // Register the MC register info
  TargetRegistry::RegisterMCRegInfo(getTheCustomISATarget(),
                                    createCustomISARegisterInfo);

  // Register the MC subtarget info
  TargetRegistry::RegisterMCSubtargetInfo(getTheCustomISATarget(),
                                          createCustomISASubtargetInfo);

  // Register the MC instruction printer
  TargetRegistry::RegisterMCInstPrinter(getTheCustomISATarget(),
                                        createCustomISAMCInstPrinter);

  // Register the MC code emitter
  TargetRegistry::RegisterMCCodeEmitter(getTheCustomISATarget(),
                                        createCustomISAMCCodeEmitter);

  // Register the MC asm backend
  TargetRegistry::RegisterMCAsmBackend(getTheCustomISATarget(),
                                       createCustomISAMCAsmBackend);
}
