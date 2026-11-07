//===-- CustomISATargetParser.h - CustomISA Target Parser -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGETPARSER_CUSTOMISATARGETPARSER_H
#define LLVM_TARGETPARSER_CUSTOMISATARGETPARSER_H

#include "llvm/TargetParser/Triple.h"

namespace llvm {

// CustomISA target parser functions
bool isCustomISA(const Triple &TT);
bool isCustomISA(StringRef ArchName);

} // end namespace llvm

#endif // LLVM_TARGETPARSER_CUSTOMISATARGETPARSER_H
