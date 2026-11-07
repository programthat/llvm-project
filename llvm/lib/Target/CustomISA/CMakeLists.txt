# Initialize the target group for modern LLVM
add_llvm_component_group(CustomISA)

# Generate the C++ headers from TableGen
set(LLVM_TARGET_DEFINITIONS CustomISA.td)

llvm_tablegen(CustomISAGenRegisterInfo.inc -gen-register-info)
llvm_tablegen(CustomISAGenInstrInfo.inc -gen-instr-info)
llvm_tablegen(CustomISAGenAsmWriter.inc -gen-asm-writer)
llvm_tablegen(CustomISAGenDAGISel.inc -gen-dag-isel)
llvm_tablegen(CustomISAGenCallingConv.inc -gen-callingconv)
llvm_tablegen(CustomISAGenSubtargetInfo.inc -gen-subtarget)
llvm_tablegen(CustomISAGenAsmMatcher.inc -gen-asm-matcher)
llvm_tablegen(CustomISAGenDisassemblerTables.inc -gen-disassembler)
llvm_tablegen(CustomISAGenDFAPacketizer.inc -gen-dfa-packetizer)
llvm_tablegen(CustomISAGenFastISel.inc -gen-fast-isel)

# Group the generated headers together
add_public_tablegen_target(CustomISACommonTableGen)

# Define the core backend C++ compilation target
add_llvm_target(CustomISACodeGen
  CustomISAAsmPrinter.cpp
  CustomISAInstPrinter.cpp
  CustomISAFrameLowering.cpp
  CustomISAInstrInfo.cpp
  CustomISARegisterInfo.cpp
  CustomISASubtarget.cpp
  CustomISATargetMachine.cpp
  CustomISATargetObjectFile.cpp
  CustomISATargetTransformInfo.cpp
  CustomISATargetLowering.cpp
  CustomISADAGToDAGISel.cpp
  CustomISASelectionDAGInfo.cpp
  CustomISAMachineFunctionInfo.cpp

  # Ensure intrinsic definitions exist before building this
  DEPENDS
  intrinsics_gen
)

# Tell CMake to enter the subfolders for the remaining components
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
