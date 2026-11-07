//===-- CustomISARegisterInfo.cpp - CustomISA Register Information --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISARegisterInfo.h"
#include "CustomISASubtarget.h"
#include "CustomISAMachineFunctionInfo.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/RegisterScavenging.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "CustomISAGenRegisterInfo.inc"

CustomISARegisterInfo::CustomISARegisterInfo()
    : CustomISAGenRegisterInfo(LR) {}

// Callee-saved registers: R8-R15, R61(SP), R62(FP), R63(LR)
const MCPhysReg *CustomISARegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  static const MCPhysReg CalleeSavedRegs[] = {
    R8, R9, R10, R11, R12, R13, R14, R15,
    R61, R62, R63, 0
  };
  return CalleeSavedRegs;
}

// Call preserved mask for C calling convention
const uint32_t *CustomISARegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                                            CallingConv::ID CC) const {
  static const uint32_t CallPreservedMask[] = {
    // R0-R31
    0x0000FF00,  // R8-R15 preserved
    // R32-R63
    0xE0000000,  // R61, R62, R63 preserved
    0
  };
  return CallPreservedMask;
}

// Reserved registers: R0 (hardwired to 0), R63 (LR)
BitVector CustomISARegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  static const uint32_t ReservedRegs[] = {
    0x00000001,  // R0
    0x80000000   // R63 (LR)
  };
  BitVector Reserved(getNumRegs());
  for (unsigned i = 0; i < array_lengthof(ReservedRegs); ++i) {
    if (ReservedRegs[i]) {
      for (unsigned j = 0; j < 32; ++j) {
        if (ReservedRegs[i] & (1u << j)) {
          Reserved.set(i * 32 + j);
        }
      }
    }
  }
  return Reserved;
}

void CustomISARegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                                int SPAdj, unsigned FIOperandNum,
                                                RegScavenger *RS) const {
  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  MachineFrameInfo &MFI = MF.getFrameInfo();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  int64_t Offset = MFI.getObjectOffset(FrameIndex) + MFI.getStackSize() + SPAdj;

  // Replace frame index with SP + offset
  MI.getOperand(FIOperandNum).ChangeToRegister(SP, false);
  // Add immediate operand for offset
  // This would need proper handling based on instruction format
}
