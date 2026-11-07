//===-- CustomISASchedule.td - CustomISA Scheduling Definitions -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the scheduling information for CustomISA instructions.
// All instructions execute in 1 cycle (combinational evaluation per tick).
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"
include "CustomISAInstrFormats.td"

//===----------------------------------------------------------------------===//
// Processor Models
//===----------------------------------------------------------------------===//

// Generic CustomISA processor model
def CustomISAGeneric : ProcessorModel<CustomISAItineraries> {
  let Name = "generic";
  let Description = "Generic CustomISA processor";
}

//===----------------------------------------------------------------------===//
// Functional Units
//===----------------------------------------------------------------------===//

// Single functional unit - all instructions execute in 1 cycle
def ALU : FuncUnit;

//===----------------------------------------------------------------------===//
// Instruction Itineraries
//===----------------------------------------------------------------------===//

// All operations execute in 1 cycle (combinational evaluation)
def IIAlu  : InstrItinData<IIAlu,  [InstrStage<1, [ALU]>]>;
def IILoad : InstrItinData<IILoad, [InstrStage<1, [ALU]>]>;
def IIStore : InstrItinData<IIStore, [InstrStage<1, [ALU]>]>;
def IIBranch : InstrItinData<IIBranch, [InstrStage<1, [ALU]>]>;
def IIJump : InstrItinData<IIJump, [InstrStage<1, [ALU]>]>;
def IICall : InstrItinData<IICall, [InstrStage<1, [ALU]>]>;
def IIMul : InstrItinData<IIMul, [InstrStage<1, [ALU]>]>;
def IIDiv : InstrItinData<IIDiv, [InstrStage<1, [ALU]>]>;
