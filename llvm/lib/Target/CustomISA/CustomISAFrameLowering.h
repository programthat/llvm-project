//===-- CustomISAFrameLowering.h - CustomISA Frame Information ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAFRAMELOWERING_H
#define LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {

class CustomISASubtarget;

class CustomISAFrameLowering : public TargetFrameLowering {
  virtual void anchor();

public:
  explicit CustomISAFrameLowering(const CustomISASubtarget &STI);

  // Stack frame management
  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  // Stack alignment
  bool hasFP(const MachineFunction &MF) const override { return true; }
  unsigned getFrameRegister(const MachineFunction &MF) const override;
  unsigned getStackRegister() const override;

  // Stack growth direction
  bool hasReservedCallFrame(const MachineFunction &MF) const override { return true; }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAFRAMELOWERING_H
