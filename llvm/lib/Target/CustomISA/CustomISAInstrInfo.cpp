//===-- CustomISAInstrInfo.cpp - CustomISA Instruction Information --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISAInstrInfo.h"
#include "CustomISASubtarget.h"
#include "CustomISARegisterInfo.h"
#include "CustomISAMachineFunctionInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "CustomISAGenInstrInfo.inc"

CustomISAInstrInfo::CustomISAInstrInfo(const CustomISASubtarget &STI)
    : CustomISAGenInstrInfo(), RI(STI.getRegisterInfo()) {}

bool CustomISAInstrInfo::analyzeBranch(MachineBasicBlock &MBB,
                                       MachineBasicBlock *&TBB,
                                       MachineBasicBlock *&FBB,
                                       SmallVectorImpl<MachineOperand> &Cond,
                                       bool AllowModify) const {
  // Simple implementation - can be expanded later
  return true;
}

unsigned CustomISAInstrInfo::insertBranch(MachineBasicBlock &MBB,
                                          MachineBasicBlock *TBB,
                                          MachineBasicBlock *FBB,
                                          ArrayRef<MachineOperand> Cond,
                                          DebugLoc DL,
                                          int *BytesAdded) const {
  // Simple implementation - can be expanded later
  return 0;
}

unsigned CustomISAInstrInfo::removeBranch(MachineBasicBlock &MBB,
                                          int *BytesRemoved) const {
  // Simple implementation - can be expanded later
  return 0;
}

bool CustomISAInstrInfo::isLoadFromStackSlot(const MachineInstr &MI,
                                             int &FrameIndex) const {
  return false;
}

bool CustomISAInstrInfo::isStoreToStackSlot(const MachineInstr &MI,
                                            int &FrameIndex) const {
  return false;
}

void CustomISAInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator I,
                                     DebugLoc DL, unsigned DestReg,
                                     unsigned SrcReg, bool KillSrc) const {
  // Use ADD Rd, Rs, R0 to copy (since R0 is hardwired to 0)
  BuildMI(MBB, I, DL, get(CustomISA::ADD), DestReg)
      .addReg(SrcReg, getKillRegState(KillSrc))
      .addReg(CustomISA::R0);
}

void CustomISAInstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                             MachineBasicBlock::iterator I,
                                             unsigned SrcReg, bool isKill,
                                             int FrameIndex,
                                             const TargetRegisterClass *RC,
                                             const TargetRegisterInfo *TRI) const {
  // Store register to stack slot using STORE instruction
  // This is a simplified implementation
  BuildMI(MBB, I, I->getDebugLoc(), get(CustomISA::STORE))
      .addReg(SrcReg, getKillRegState(isKill))
      .addReg(CustomISA::SP)
      .addImm(FrameIndex * 4); // 4 bytes per slot
}

void CustomISAInstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                              MachineBasicBlock::iterator I,
                                              unsigned DestReg, int FrameIndex,
                                              const TargetRegisterClass *RC,
                                              const TargetRegisterInfo *TRI) const {
  // Load register from stack slot using LOAD instruction
  BuildMI(MBB, I, I->getDebugLoc(), get(CustomISA::LOAD), DestReg)
      .addReg(CustomISA::SP)
      .addImm(FrameIndex * 4); // 4 bytes per slot
}

bool CustomISAInstrInfo::expandPostRAPseudo(MachineInstr &MI) const {
  // Expand pseudo instructions after register allocation
  switch (MI.getOpcode()) {
  case CustomISA::RET: {
    // RET expands to JALR R0, LR, 0
    MachineBasicBlock &MBB = *MI.getParent();
    DebugLoc DL = MI.getDebugLoc();
    BuildMI(MBB, MI, DL, get(CustomISA::JALR))
        .addReg(CustomISA::R0)
        .addReg(CustomISA::LR)
        .addImm(0);
    MI.eraseFromParent();
    return true;
  }
  case CustomISA::MOV: {
    // MOV expands to ADD Rd, Ra, R0
    MachineBasicBlock &MBB = *MI.getParent();
    DebugLoc DL = MI.getDebugLoc();
    unsigned Rd = MI.getOperand(0).getReg();
    unsigned Ra = MI.getOperand(1).getReg();
    BuildMI(MBB, MI, DL, get(CustomISA::ADD), Rd)
        .addReg(Ra)
        .addReg(CustomISA::R0);
    MI.eraseFromParent();
    return true;
  }
  case CustomISA::LI: {
    // LI expands to LDI
    MachineBasicBlock &MBB = *MI.getParent();
    DebugLoc DL = MI.getDebugLoc();
    unsigned Rd = MI.getOperand(0).getReg();
    int64_t Imm = MI.getOperand(1).getImm();
    BuildMI(MBB, MI, DL, get(CustomISA::LDI), Rd)
        .addImm(Imm);
    MI.eraseFromParent();
    return true;
  }
  default:
    return false;
  }
}
