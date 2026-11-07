//===-- CustomISATargetMachine.h - Define TargetMachine for CustomISA -----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISATARGETMACHINE_H
#define LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISATARGETMACHINE_H

#include "CustomISASubtarget.h"
#include "CustomISATargetObjectFile.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetTransformInfo.h"

namespace llvm {

class CustomISATargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  CustomISASubtarget Subtarget;

public:
  CustomISATargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                         StringRef FS, const TargetOptions &Options,
                         Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                         CodeGenOptLevel OL, bool JIT);
  ~CustomISATargetMachine() override;

  const CustomISASubtarget *getSubtargetImpl(const Function &F) const override;
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override;
  TargetTransformInfo getTargetTransformInfo(const Function &F) const override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_CUSTOMISA_CUSTOMISATARGETMACHINE_H
