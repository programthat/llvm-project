//===-- CustomISASubtarget.h - Define Subtarget for CustomISA ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISASUBTARGET_H
#define LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISASUBTARGET_H

#include "CustomISARegisterInfo.h"
#include "CustomISAFrameLowering.h"
#include "CustomISAInstrInfo.h"
#include "CustomISATargetLowering.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/Target/TargetMachine.h"

#define GET_SUBTARGETINFO_HEADER
#include "CustomISAGenSubtargetInfo.inc"

namespace llvm {

class CustomISASubtarget : public CustomISAGenSubtargetInfo {
  virtual void anchor();

  CustomISAInstrInfo InstrInfo;
  CustomISATargetLowering TLInfo;
  CustomISAFrameLowering FrameLowering;
  CustomISARegisterInfo RegInfo;

public:
  CustomISASubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                     const TargetMachine &TM);

  const CustomISAInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const CustomISATargetLowering *getTargetLowering() const override { return &TLInfo; }
  const CustomISAFrameLowering *getFrameLowering() const override { return &FrameLowering; }
  const CustomISARegisterInfo *getRegisterInfo() const override { return &RegInfo; }

  // Disable instruction scheduling since all instructions take 1 cycle
  bool enablePostRAScheduler(CodeGenOptLevel OptLevel) const override { return false; }
  bool enableMachineScheduler() const override { return false; }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISASUBTARGET_H
