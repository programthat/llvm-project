//===-- CustomISA.td - CustomISA Target Description -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file describes the CustomISA target for LLVM.
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"
include "CustomISARegisters.td"
include "CustomISAInstrFormats.td"
include "CustomISAInstrInfo.td"
include "CustomISASchedule.td"
include "CustomISACallingConv.td"

//===----------------------------------------------------------------------===//
// CustomISA Target Definition
//===----------------------------------------------------------------------===//

def CustomISA : Target {
  let Name = "CustomISA";
  let Triple = "customisa";
  let InstructionSet = CustomISAInstrInfo;
  let TargetLowering = CustomISATargetLowering;
  let TargetJITInfo = DefaultJITInfo;
  let MCCodeEmitter = CustomISAMCCodeEmitter;
  let MCAsmBackend = CustomISAMCAsmBackend;
  let MCObjectWriter = CustomISAMCObjectWriter;
  let AsmParser = CustomISAAsmParser;
  let Disassembler = CustomISADisassembler;
  let InstrItineraries = CustomISAItineraries;
  let CallingConv = CustomISACallingConv;
  let Subtarget = CustomISASubtarget;
  let FrameLowering = CustomISAFrameLowering;
  let RegisterInfo = CustomISARegisterInfo;
  let LegalizeTypes = CustomISALegalizeTypes;
  let LegalizeDAG = CustomISALegalizeDAG;
  let SelectionDAGISel = CustomISADAGToDAGISel;
  let TargetTransformInfo = CustomISATTI;
}

//===----------------------------------------------------------------------===//
// Subtarget Features
//===----------------------------------------------------------------------===//

def FeatureCustomISA : SubtargetFeature<"customisa", "HasCustomISA", "true",
                                      "CustomISA base architecture">;

def CustomISASubtarget : Subtarget<CustomISA> {
  let Features = [FeatureCustomISA];
}

//===----------------------------------------------------------------------===//
// Data Layout
//===----------------------------------------------------------------------===//

// CustomISA is 32-bit, big-endian
def CustomISADataLayout : DataLayout {
  let String = "E-m:e-p:32:32-i32:32-n32-S32";
}
