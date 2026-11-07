//===-- CustomISACallingConv.td - CustomISA Calling Convention ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the calling convention for CustomISA.
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"
include "CustomISARegisters.td"

//===----------------------------------------------------------------------===//
// Calling Convention Definitions
//===----------------------------------------------------------------------===//

// CustomISA calling convention (CC_CustomISA = 64)
def CC_CustomISA : CallingConv<[
  // Return value in R1
  CCIfType<[i32], CCAssignToReg<[R1]>>,

  // Arguments in R1-R7 (up to 7 arguments in registers)
  CCIfType<[i32], CCAssignToReg<[R1, R2, R3, R4, R5, R6, R7]>>,

  // Remaining arguments on stack
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

// C calling convention (same as CustomISA for now)
def CC_C : CallingConv<[
  CCIfType<[i32], CCAssignToReg<[R1]>>,
  CCIfType<[i32], CCAssignToReg<[R1, R2, R3, R4, R5, R6, R7]>>,
  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

//===----------------------------------------------------------------------===//
// Calling Convention Aliases
//===----------------------------------------------------------------------===//

def CustomISACallingConv : CallingConvList<[
  CallingConvAlias<"C", CC_C>,
  CallingConvAlias<"CustomISA", CC_CustomISA>
]>;
