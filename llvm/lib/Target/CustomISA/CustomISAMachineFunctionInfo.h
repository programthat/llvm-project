//===-- CustomISAMachineFunctionInfo.h - CustomISA Machine Function Info --===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAMACHINEFUNCTIONINFO_H
#define LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAMACHINEFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

class CustomISAMachineFunctionInfo : public MachineFunctionInfo {
  virtual void anchor();

public:
  CustomISAMachineFunctionInfo() = default;
  ~CustomISAMachineFunctionInfo() override = default;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAMACHINEFUNCTIONINFO_H
