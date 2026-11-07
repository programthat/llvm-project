//===-- CustomISATargetLowering.h - CustomISA Target Lowering -------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISATARGETLOWERING_H
#define LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISATARGETLOWERING_H

#include "CustomISASubtarget.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/IR/CallingConv.h"

namespace llvm {

class CustomISATargetLowering : public TargetLowering {
  virtual void anchor();

public:
  explicit CustomISATargetLowering(const CustomISATargetMachine &TM,
                                   const CustomISASubtarget &STI);

  // Lowering operations
  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;
  SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                               bool IsVarArg,
                               const SmallVectorImpl<ISD::InputArg> &Ins,
                               SDLoc DL, SelectionDAG &DAG) const override;
  SDValue LowerCall(TargetLowering::CallLoweringInfo &CLI,
                    SmallVectorImpl<SDValue> &InVals) const override;
  SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                      bool IsVarArg,
                      const SmallVectorImpl<ISD::OutputArg> &Outs,
                      SDLoc DL, SelectionDAG &DAG) const override;

  // Address computation
  SDValue LowerGlobalAddress(SDValue Op, SelectionDAG &DAG) const override;
  SDValue LowerConstantPool(SDValue Op, SelectionDAG &DAG) const override;
  SDValue LowerBlockAddress(SDValue Op, SelectionDAG &DAG) const override;
  SDValue LowerJumpTable(SDValue Op, SelectionDAG &DAG) const override;

  // Stack frame
  MachineBasicBlock *emitFrameEntry(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const override;

  // Register classes
  const TargetRegisterClass *getPointerRegClass(const MachineFunction &MF,
                                                unsigned Kind) const override;

  // Calling convention
  CallingConv::ID getDefaultCallingConv(CallingConv::ID CC) const override;

  // Custom lowering hooks
  bool isOffsetFoldingLegal(const GlobalAddressSDNode *GA) const override;
  bool isOffsetFoldingLegal(const ConstantPoolSDNode *CP) const override;
  bool isOffsetFoldingLegal(const JumpTableSDNode *JT) const override;
  bool isOffsetFoldingLegal(const BlockAddressSDNode *BA) const override;

  // Stack alignment
  unsigned getStackAlignment() const override { return 4; }

  // Byval handling
  bool canLowerReturn(CallingConv::ID CallConv, MachineFunctionType &MFType,
                      bool IsVarArg) const override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISATARGETLOWERING_H
