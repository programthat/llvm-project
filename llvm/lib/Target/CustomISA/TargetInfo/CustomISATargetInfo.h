//===-- CustomISATargetInfo.h - CustomISA Target Info ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_TARGETINFO_CUSTOMISATARGETINFO_H
#define LLVM_LIB_TARGET_CUSTOMISA_TARGETINFO_CUSTOMISATARGETINFO_H

#include "llvm/Target/Target.h"

namespace llvm {

Target &getTheCustomISATarget();

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_TARGETINFO_CUSTOMISATARGETINFO_H
