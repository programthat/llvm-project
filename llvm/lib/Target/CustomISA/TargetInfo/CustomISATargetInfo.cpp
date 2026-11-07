//===-- CustomISATargetInfo.cpp - CustomISA Target Info -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/CustomISATargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheCustomISATarget() {
  static Target TheCustomISATarget;
  return TheCustomISATarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeCustomISATargetInfo() {
  RegisterTarget<Triple::customisa, /*HasJIT=*/false>
    X(getTheCustomISATarget(), "customisa", "CustomISA", "CustomISA");
}
