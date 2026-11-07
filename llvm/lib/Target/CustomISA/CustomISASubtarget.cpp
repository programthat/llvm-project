//===-- CustomISASubtarget.cpp - CustomISA Subtarget Information ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISASubtarget.h"
#include "CustomISA.h"
#include "CustomISATargetMachine.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_SUBTARGETINFO_CTOR
#include "CustomISAGenSubtargetInfo.inc"

CustomISASubtarget::CustomISASubtarget(const Triple &TT, StringRef CPU,
                                       StringRef FS, const TargetMachine &TM)
    : CustomISAGenSubtargetInfo(TT, CPU, FS, /*TuneCPU*/ CPU, TM),
      InstrInfo(*this),
      TLInfo(*this),
      FrameLowering(*this),
      RegInfo(*this) {
  // Parse subtarget features
  ParseSubtargetFeatures(CPU, FS);
}
