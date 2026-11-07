//===-- CustomISARegisterInfo.h - CustomISA Register Information ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAREGISTERINFO_H
#define LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAREGISTERINFO_H

#include "CustomISAInstrInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "CustomISAGenRegisterInfo.inc"

namespace llvm {

class CustomISARegisterInfo : public CustomISAGenRegisterInfo {
  virtual void anchor();

public:
  CustomISARegisterInfo();

  // Frame register information
  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;
  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID CC) const override;
  BitVector getReservedRegs(const MachineFunction &MF) const override;

  // Frame index elimination
  void eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum, RegScavenger *RS = nullptr) const override;

  // Stack frame
  bool hasFP(const MachineFunction &MF) const override { return true; }
  unsigned getFrameRegister(const MachineFunction &MF) const override { return FP; }
  unsigned getStackRegister() const override { return SP; }

  // R0 is hardwired to zero
  bool isConstantPhysReg(unsigned Reg) const override { return Reg == R0; }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAREGISTERINFO_H
