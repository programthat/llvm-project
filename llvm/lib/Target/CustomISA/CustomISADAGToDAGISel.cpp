//===-- CustomISADAGToDAGISel.cpp - CustomISA DAG->DAG Instruction Selection-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISADAGToDAGISel.h"
#include "CustomISATargetMachine.h"
#include "CustomISARegisterInfo.h"
#include "CustomISAInstrInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"

using namespace llvm;

#define DEBUG_TYPE "customisa-isel"

CustomISADAGToDAGISel::CustomISADAGToDAGISel(CustomISATargetMachine &TM,
                                             CodeGenOptLevel OptLevel)
    : SelectionDAGISel(TM, OptLevel) {}

bool CustomISADAGToDAGISel::runOnMachineFunction(MachineFunction &MF) {
  return SelectionDAGISel::runOnMachineFunction(MF);
}

void CustomISADAGToDAGISel::Select(SDNode *Node) {
  // If already selected, don't reselect
  if (Node->isMachineOpcode()) {
    Node->setNodeId(-1);
    return;
  }

  // Select the instruction using the auto-generated tablegen patterns
  SelectCode(Node);
}

bool CustomISADAGToDAGISel::SelectAddr(SDValue Addr, SDValue &Base, SDValue &Offset) {
  // Address selection for load/store: base + offset
  // CustomISA uses Rb + imm12 format
  if (Addr.getOpcode() == ISD::ADD) {
    if (ConstantSDNode *C = dyn_cast<ConstantSDNode>(Addr.getOperand(1))) {
      int64_t OffsetVal = C->getSExtValue();
      if (isInt<12>(OffsetVal)) {
        Base = Addr.getOperand(0);
        Offset = CurDAG->getTargetConstant(OffsetVal, SDLoc(Addr), MVT::i32);
        return true;
      }
    }
  }

  // Simple register base
  Base = Addr;
  Offset = CurDAG->getTargetConstant(0, SDLoc(Addr), MVT::i32);
  return true;
}

SDValue CustomISADAGToDAGISel::PerformDAGCombine(SDNode *N, DAGCombinerInfo &DCI) const {
  // Target-specific DAG combines can be added here
  return SDValue();
}
