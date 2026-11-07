//===-- CustomISAMCAsmInfo.cpp - CustomISA Asm Info -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISAMCAsmInfo.h"
#include "llvm/ADT/Triple.h"

using namespace llvm;

CustomISAMCAsmInfo::CustomISAMCAsmInfo(const Triple &TT) {
  // CustomISA is big-endian
  IsLittleEndian = false;

  // Stack grows down
  StackGrowsUp = false;

  // Alignment
  AlignmentIsInBytes = true;
  Data16bitsDirective = "\t.half\t";
  Data32bitsDirective = "\t.word\t";
  Data64bitsDirective = "\t.dword\t";

  // Comment string
  CommentString = ";";

  // No debug info for now
  SupportsDebugInformation = false;

  // Use .section for sections
  UseIntegratedAssembler = true;

  // Private global prefix
  PrivateGlobalPrefix = "L";

  // Weak directive
  WeakDirective = "\t.weak\t";

  // GP relative relocations not supported
  HasLEB128 = true;

  // No exception handling
  ExceptionsType = ExceptionHandling::None;

  // Dwarf register numbers match our register definitions
  DwarfRegNumForCFI = true;
}
