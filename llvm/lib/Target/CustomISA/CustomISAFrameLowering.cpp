//===-- CustomISAFrameLowering.cpp - CustomISA Frame Information ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISAFrameLowering.h"
#include "CustomISASubtarget.h"
#include "CustomISARegisterInfo.h"
#include "CustomISAMachineFunctionInfo.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/RegisterScavenging.h"

using namespace llvm;

CustomISAFrameLowering::CustomISAFrameLowering(const CustomISASubtarget &STI)
    : TargetFrameLowering(StackGrowsDown, Align(4), 0, Align(4)) {}

unsigned CustomISAFrameLowering::getFrameRegister(const MachineFunction &MF) const {
  return CustomISA::FP;
}

unsigned CustomISAFrameLowering::getStackRegister() const {
  return CustomISA::SP;
}

void CustomISAFrameLowering::emitPrologue(MachineFunction &MF,
                                          MachineBasicBlock &MBB) const {
  MachineBasicBlock::iterator MBBI = MBB.begin();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  const CustomISARegisterInfo &RegInfo =
      *static_cast<const CustomISARegisterInfo *>(MF.getSubtarget().getRegisterInfo());

  // Get the number of bytes to allocate from the stack
  uint64_t StackSize = MFI.getStackSize();

  if (StackSize == 0)
    return;

  // Save FP and LR to stack
  // PUSH FP
  BuildMI(MBB, MBBI, DebugLoc(), RegInfo.get(CustomISA::STORE))
      .addReg(CustomISA::FP)
      .addReg(CustomISA::SP)
      .addImm(-4);

  // PUSH LR
  BuildMI(MBB, MBBI, DebugLoc(), RegInfo.get(CustomISA::STORE))
      .addReg(CustomISA::LR)
      .addReg(CustomISA::SP)
      .addImm(-8);

  // Set FP = SP
  BuildMI(MBB, MBBI, DebugLoc(), RegInfo.get(CustomISA::ADD), CustomISA::FP)
      .addReg(CustomISA::SP)
      .addReg(CustomISA::R0);

  // Allocate stack space: SP = SP - StackSize
  if (StackSize <= 0x3FFFF) { // 18-bit immediate
    BuildMI(MBB, MBBI, DebugLoc(), RegInfo.get(CustomISA::ADDI), CustomISA::SP)
        .addReg(CustomISA::SP)
        .addImm(-StackSize);
  } else {
    // Need to load large immediate first
    // This is a simplified version
    BuildMI(MBB, MBBI, DebugLoc(), RegInfo.get(CustomISA::LDI), CustomISA::R1)
        .addImm(StackSize);
    BuildMI(MBB, MBBI, DebugLoc(), RegInfo.get(CustomISA::SUB), CustomISA::SP)
        .addReg(CustomISA::SP)
        .addReg(CustomISA::R1);
  }
}

void CustomISAFrameLowering::emitEpilogue(MachineFunction &MF,
                                          MachineBasicBlock &MBB) const {
  MachineBasicBlock::iterator MBBI = MBB.getLastNonDebugInstr();
  MachineFrameInfo &MFI = MF.getFrameInfo();
  const CustomISARegisterInfo &RegInfo =
      *static_cast<const CustomISARegisterInfo *>(MF.getSubtarget().getRegisterInfo());

  uint64_t StackSize = MFI.getStackSize();

  if (StackSize == 0)
    return;

  // Deallocate stack space: SP = SP + StackSize
  if (StackSize <= 0x3FFFF) {
    BuildMI(MBB, MBBI, DebugLoc(), RegInfo.get(CustomISA::ADDI), CustomISA::SP)
        .addReg(CustomISA::SP)
        .addImm(StackSize);
  } else {
    BuildMI(MBB, MBBI, DebugLoc(), RegInfo.get(CustomISA::LDI), CustomISA::R1)
        .addImm(StackSize);
    BuildMI(MBB, MBBI, DebugLoc(), RegInfo.get(CustomISA::ADD), CustomISA::SP)
        .addReg(CustomISA::SP)
        .addReg(CustomISA::R1);
  }

  // Restore LR
  BuildMI(MBB, MBBI, DebugLoc(), RegInfo.get(CustomISA::LOAD), CustomISA::LR)
      .addReg(CustomISA::SP)
      .addImm(-8);

  // Restore FP
  BuildMI(MBB, MBBI, DebugLoc(), RegInfo.get(CustomISA::LOAD), CustomISA::FP)
      .addReg(CustomISA::SP)
      .addImm(-4);
}
