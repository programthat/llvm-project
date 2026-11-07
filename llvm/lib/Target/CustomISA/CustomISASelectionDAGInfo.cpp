//===-- CustomISASelectionDAGInfo.cpp - CustomISA SelectionDAG Info -------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CustomISASelectionDAGInfo.h"

using namespace llvm;

CustomISASelectionDAGInfo::CustomISASelectionDAGInfo(const DataLayout &DL)
    : SelectionDAGTargetInfo(DL) {}

CustomISASelectionDAGInfo::~CustomISASelectionDAGInfo() = default;
