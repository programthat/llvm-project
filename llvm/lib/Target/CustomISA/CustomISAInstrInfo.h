//===-- CustomISAInstrInfo.h - CustomISA Instruction Information ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAINSTRINFO_H
#define LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAINSTRINFO_H

#include "CustomISARegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "CustomISAGenInstrInfo.inc"

namespace llvm {

class CustomISASubtarget;

class CustomISAInstrInfo : public CustomISAGenInstrInfo {
  virtual void anchor();
  const CustomISARegisterInfo &RI;

public:
  explicit CustomISAInstrInfo(const CustomISASubtarget &STI);

  // Branch analysis
  bool analyzeBranch(MachineBasicBlock &MBB, MachineBasicBlock *&TBB,
                     MachineBasicBlock *&FBB,
                     SmallVectorImpl<MachineOperand> &Cond,
                     bool AllowModify) const override;

  unsigned insertBranch(MachineBasicBlock &MBB, MachineBasicBlock *TBB,
                        MachineBasicBlock *FBB,
                        ArrayRef<MachineOperand> Cond,
                        DebugLoc DL, int *BytesAdded = nullptr) const override;

  unsigned removeBranch(MachineBasicBlock &MBB,
                        int *BytesRemoved = nullptr) const override;

  // Instruction predicates
  bool isLoadFromStackSlot(const MachineInstr &MI,
                           int &FrameIndex) const override;
  bool isStoreToStackSlot(const MachineInstr &MI,
                          int &FrameIndex) const override;

  // Copy instruction
  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                   DebugLoc DL, unsigned DestReg, unsigned SrcReg,
                   bool KillSrc) const override;

  // Store/load reg to stack slot
  void storeRegToStackSlot(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                           unsigned SrcReg, bool isKill, int FrameIndex,
                           const TargetRegisterClass *RC,
                           const TargetRegisterInfo *TRI) const override;
  void loadRegFromStackSlot(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                            unsigned DestReg, int FrameIndex,
                            const TargetRegisterClass *RC,
                            const TargetRegisterInfo *TRI) const override;

  // Expand pseudo instructions
  bool expandPostRAPseudo(MachineInstr &MI) const override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISAINSTRINFO_H
