//===-- CustomISATargetParser.cpp - CustomISA Target Parser ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/TargetParser/CustomISATargetParser.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

bool llvm::isCustomISA(const Triple &TT) {
  return TT.getArch() == Triple::customisa;
}

bool llvm::isCustomISA(StringRef ArchName) {
  return ArchName == "customisa";
}
