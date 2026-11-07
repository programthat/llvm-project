//===-- CustomISAMCAsmInfo.h - CustomISA Asm Info -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_MCTARGETDESC_CUSTOMISAMCASMINFO_H
#define LLVM_LIB_TARGET_CUSTOMISA_MCTARGETDESC_CUSTOMISAMCASMINFO_H

#include "llvm/MC/MCAsmInfo.h"

namespace llvm {

class Triple;

class CustomISAMCAsmInfo : public MCAsmInfo {
public:
  explicit CustomISAMCAsmInfo(const Triple &TT);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_MCTARGETDESC_CUSTOMISAMCASMINFO_H
