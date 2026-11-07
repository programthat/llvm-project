//===-- CustomISATargetMachine.cpp - Define TargetMachine for CustomISA ---===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISATargetMachine.h"
#include "CustomISA.h"
#include "CustomISATargetObjectFile.h"
#include "CustomISATargetTransformInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeCustomISATarget() {
  // Register the target
  RegisterTargetMachine<CustomISATargetMachine> X(getTheCustomISATarget());
}

static std::string computeDataLayout(const Triple &TT) {
  // CustomISA is 32-bit, big-endian
  return "E-m:e-p:32:32-i32:32-n32-S32";
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           Optional<Reloc::Model> RM) {
  if (!RM.hasValue())
    return Reloc::Static;
  return *RM;
}

static CodeModel::Model getEffectiveCodeModel(const Triple &TT,
                                              Optional<CodeModel::Model> CM) {
  if (CM)
    return *CM;
  return CodeModel::Small;
}

CustomISATargetMachine::CustomISATargetMachine(const Target &T, const Triple &TT,
                                               StringRef CPU, StringRef FS,
                                               const TargetOptions &Options,
                                               Optional<Reloc::Model> RM,
                                               Optional<CodeModel::Model> CM,
                                               CodeGenOptLevel OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(TT), TT, CPU, FS, Options,
                        getEffectiveRelocModel(TT, RM),
                        getEffectiveCodeModel(TT, CM), OL),
      TLOF(std::make_unique<CustomISATargetObjectFile>()),
      Subtarget(TT, CPU, FS, *this) {
  initAsmInfo();
}

CustomISATargetMachine::~CustomISATargetMachine() = default;

const CustomISASubtarget *
CustomISATargetMachine::getSubtargetImpl(const Function &F) const {
  Attribute CPUAttr = F.getFnAttribute("target-cpu");
  Attribute FSAttr = F.getFnAttribute("target-features");

  std::string CPU = !CPUAttr.hasAttribute(Attribute::None)
                        ? CPUAttr.getValueAsString().str()
                        : TargetCPU;
  std::string FS = !FSAttr.hasAttribute(Attribute::None)
                       ? FSAttr.getValueAsString().str()
                       : TargetFS;

  return &Subtarget;
}

TargetPassConfig *CustomISATargetMachine::createPassConfig(PassManagerBase &PM) {
  return new CustomISAPassConfig(*this, PM);
}

TargetLoweringObjectFile *CustomISATargetMachine::getObjFileLowering() const {
  return TLOF.get();
}

TargetTransformInfo CustomISATargetMachine::getTargetTransformInfo(
    const Function &F) const {
  return TargetTransformInfo(CustomISATTI(*this, F));
}
