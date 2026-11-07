//===-- CustomISATargetLowering.cpp - CustomISA Target Lowering -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISATargetLowering.h"
#include "CustomISASubtarget.h"
#include "CustomISATargetMachine.h"
#include "CustomISARegisterInfo.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

CustomISATargetLowering::CustomISATargetLowering(const CustomISATargetMachine &TM,
                                                 const CustomISASubtarget &STI)
    : TargetLowering(TM, STI) {
  // Set up register classes
  addRegisterClass(MVT::i32, &CustomISA::GPR);

  // Set stack pointer register
  setStackPointerRegisterToSaveRestore(CustomISA::SP);

  // Operation actions
  setOperationAction(ISD::GlobalAddress, MVT::i32, Custom);
  setOperationAction(ISD::ConstantPool, MVT::i32, Custom);
  setOperationAction(ISD::BlockAddress, MVT::i32, Custom);
  setOperationAction(ISD::JumpTable, MVT::i32, Custom);

  // Arithmetic operations
  setOperationAction(ISD::ADD, MVT::i32, Legal);
  setOperationAction(ISD::SUB, MVT::i32, Legal);
  setOperationAction(ISD::MUL, MVT::i32, Legal);
  setOperationAction(ISD::SDIV, MVT::i32, Legal);
  setOperationAction(ISD::UDIV, MVT::i32, Legal);
  setOperationAction(ISD::SREM, MVT::i32, Legal);
  setOperationAction(ISD::UREM, MVT::i32, Legal);
  setOperationAction(ISD::AND, MVT::i32, Legal);
  setOperationAction(ISD::OR, MVT::i32, Legal);
  setOperationAction(ISD::XOR, MVT::i32, Legal);
  setOperationAction(ISD::SHL, MVT::i32, Legal);
  setOperationAction(ISD::SRL, MVT::i32, Legal);
  setOperationAction(ISD::SRA, MVT::i32, Legal);

  // Comparison operations
  setOperationAction(ISD::SETCC, MVT::i32, Custom);
  setOperationAction(ISD::SELECT, MVT::i32, Legal);
  setOperationAction(ISD::SELECT_CC, MVT::i32, Custom);

  // Load/Store operations
  setOperationAction(ISD::LOAD, MVT::i32, Legal);
  setOperationAction(ISD::STORE, MVT::i32, Legal);

  // Control flow
  setOperationAction(ISD::BR_CC, MVT::i32, Custom);
  setOperationAction(ISD::BRCOND, MVT::i32, Custom);
  setOperationAction(ISD::BR, MVT::i32, Custom);
  setOperationAction(ISD::CALL, MVT::i32, Custom);
  setOperationAction(ISD::RET, MVT::i32, Custom);

  // Stack operations
  setOperationAction(ISD::FrameIndex, MVT::i32, Legal);

  // Scheduling preference
  setSchedulingPreference(Sched::RegPressure);
}

SDValue CustomISATargetLowering::LowerOperation(SDValue Op, SelectionDAG &DAG) const {
  switch (Op.getOpcode()) {
  case ISD::GlobalAddress:
    return LowerGlobalAddress(Op, DAG);
  case ISD::ConstantPool:
    return LowerConstantPool(Op, DAG);
  case ISD::BlockAddress:
    return LowerBlockAddress(Op, DAG);
  case ISD::JumpTable:
    return LowerJumpTable(Op, DAG);
  case ISD::SETCC:
    return LowerSETCC(Op, DAG);
  case ISD::SELECT_CC:
    return LowerSELECT_CC(Op, DAG);
  case ISD::BR_CC:
    return LowerBR_CC(Op, DAG);
  case ISD::BRCOND:
    return LowerBRCOND(Op, DAG);
  case ISD::BR:
    return LowerBR(Op, DAG);
  case ISD::CALL:
    return LowerCall(Op, DAG);
  case ISD::RET:
    return LowerRET(Op, DAG);
  default:
    llvm_unreachable("Unknown operation to lower");
  }
}

SDValue CustomISATargetLowering::LowerGlobalAddress(SDValue Op, SelectionDAG &DAG) const {
  // Load global address using LDI + ADD sequence
  // For now, return a placeholder
  return SDValue();
}

SDValue CustomISATargetLowering::LowerConstantPool(SDValue Op, SelectionDAG &DAG) const {
  return SDValue();
}

SDValue CustomISATargetLowering::LowerBlockAddress(SDValue Op, SelectionDAG &DAG) const {
  return SDValue();
}

SDValue CustomISATargetLowering::LowerJumpTable(SDValue Op, SelectionDAG &DAG) const {
  return SDValue();
}

SDValue CustomISATargetLowering::LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                                                      bool IsVarArg,
                                                      const SmallVectorImpl<ISD::InputArg> &Ins,
                                                      SDLoc DL, SelectionDAG &DAG) const {
  // Arguments are passed in R1-R7, rest on stack
  // This is a simplified implementation
  return Chain;
}

SDValue CustomISATargetLowering::LowerCall(TargetLowering::CallLoweringInfo &CLI,
                                           SmallVectorImpl<SDValue> &InVals) const {
  // Call lowering - use JAL instruction
  return DAG.getNode(ISD::CALL, CLI.DL, CLI.RetTy, CLI.Chain, CLI.Callee);
}

SDValue CustomISATargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                                             bool IsVarArg,
                                             const SmallVectorImpl<ISD::OutputArg> &Outs,
                                             SDLoc DL, SelectionDAG &DAG) const {
  // Return value in R1, use RET (JALR R0, LR, 0)
  return DAG.getNode(ISD::RET, DL, MVT::Other, Chain);
}

MachineBasicBlock *CustomISATargetLowering::emitFrameEntry(MachineFunction &MF,
                                                           MachineBasicBlock &MBB) const {
  return &MBB;
}

const TargetRegisterClass *CustomISATargetLowering::getPointerRegClass(const MachineFunction &MF,
                                                                       unsigned Kind) const {
  return &CustomISA::GPR;
}

CallingConv::ID CustomISATargetLowering::getDefaultCallingConv(CallingConv::ID CC) const {
  return CallingConv::C;
}

bool CustomISATargetLowering::isOffsetFoldingLegal(const GlobalAddressSDNode *GA) const {
  return false;
}

bool CustomISATargetLowering::isOffsetFoldingLegal(const ConstantPoolSDNode *CP) const {
  return false;
}

bool CustomISATargetLowering::isOffsetFoldingLegal(const JumpTableSDNode *JT) const {
  return false;
}

bool CustomISATargetLowering::isOffsetFoldingLegal(const BlockAddressSDNode *BA) const {
  return false;
}

bool CustomISATargetLowering::canLowerReturn(CallingConv::ID CallConv, MachineFunctionType &MFType,
                                             bool IsVarArg) const {
  return true;
}
