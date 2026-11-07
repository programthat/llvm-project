//===-- CustomISATargetTransformInfo.h - CustomISA TTI --------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISATARGETTRANSFORMINFO_H
#define LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISATARGETTRANSFORMINFO_H

#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/BasicTTIImpl.h"

namespace llvm {

class CustomISATargetMachine;

class CustomISATTI : public BasicTTIImplBase<CustomISATTI> {
  using BaseT = BasicTTIImplBase<CustomISATTI>;
  friend BaseT;

  const CustomISATargetMachine *TM;

  const CustomISATargetMachine *getTM() const { return TM; }
  const CustomISATargetMachine *getST() const { return TM; }

public:
  explicit CustomISATTI(const CustomISATargetMachine *TM) : TM(TM) {}
  explicit CustomISATTI(const Function &F) : TM(&F.getTarget().getTargetMachine()) {}

  // Target-independent cost model
  bool isLegalAddImmediate(int64_t Imm) const { return true; }
  bool isLegalICmpImmediate(int64_t Imm) const { return true; }
  bool isLegalAddressingMode(Type *Ty, GlobalValue *BaseGV, int64_t BaseOffset,
                             bool HasBaseReg, int64_t Scale,
                             unsigned AddrSpace) const { return true; }

  // Instruction cost
  int getIntImmCost(Intrinsic::ID IID, unsigned Idx, int64_t Imm,
                    Type *Ty, TTI::TargetCostKind CostKind) const;

  // Register pressure
  unsigned getNumberOfRegisters(bool Vector) const { return 64; }

  // Unrolling preferences
  unsigned getUnrollingPreferences(Loop *L, ScalarEvolution &SE,
                                   TTI::UnrollingPreferences &UP) const;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISATARGETTRANSFORMINFO_H
