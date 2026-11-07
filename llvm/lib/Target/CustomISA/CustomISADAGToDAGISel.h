//===-- CustomISADAGToDAGISel.h - CustomISA DAG->DAG Instruction Selection --===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISADAGTODAGISEL_H
#define LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISADAGTODAGISEL_H

#include "CustomISASubtarget.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

namespace llvm {

class CustomISADAGToDAGISel : public SelectionDAGISel {
  virtual void anchor();

public:
  explicit CustomISADAGToDAGISel(CustomISATargetMachine &TM,
                                 CodeGenOptLevel OptLevel);

  bool runOnMachineFunction(MachineFunction &MF) override;

  // Custom lowering for specific nodes
  void Select(SDNode *Node) override;

  // Complex pattern matching
  bool SelectAddr(SDValue Addr, SDValue &Base, SDValue &Offset);

  // Target-specific DAG combine
  SDValue PerformDAGCombine(SDNode *N, DAGCombinerInfo &DCI) const override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISADAGTODAGISEL_H
