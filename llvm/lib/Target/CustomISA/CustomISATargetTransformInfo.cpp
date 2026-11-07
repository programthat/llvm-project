//===-- CustomISATargetTransformInfo.cpp - CustomISA TTI ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISATargetTransformInfo.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/IR/Intrinsics.h"

using namespace llvm;

int CustomISATTI::getIntImmCost(Intrinsic::ID IID, unsigned Idx, int64_t Imm,
                                Type *Ty, TTI::TargetCostKind CostKind) const {
  // All immediates are relatively cheap since we have LDI instruction
  return 1;
}

unsigned CustomISATTI::getUnrollingPreferences(Loop *L, ScalarEvolution &SE,
                                               TTI::UnrollingPreferences &UP) const {
  // Conservative unrolling for small register file
  UP.Partial = true;
  UP.Runtime = true;
  UP.UpperBound = 100;
  return 0;
}
