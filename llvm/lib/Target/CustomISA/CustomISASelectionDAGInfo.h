//===-- CustomISASelectionDAGInfo.h - CustomISA SelectionDAG Info ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISASELECTIONDAGINFO_H
#define LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISASELECTIONDAGINFO_H

#include "llvm/CodeGen/SelectionDAGTargetInfo.h"

namespace llvm {

class CustomISASelectionDAGInfo : public SelectionDAGTargetInfo {
  virtual void anchor();

public:
  CustomISASelectionDAGInfo(const DataLayout &DL) : SelectionDAGTargetInfo(DL) {}
  ~CustomISASelectionDAGInfo() override = default;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISASELECTIONDAGINFO_H
