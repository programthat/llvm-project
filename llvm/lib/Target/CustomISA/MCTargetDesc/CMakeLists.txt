add_llvm_component_library(LLVMCustomISADesc
  CustomISAMCTargetDesc.cpp
  CustomISAMCAsmBackend.cpp
  CustomISAMCAsmInfo.cpp
  CustomISAMCCodeEmitter.cpp
  LINK_COMPONENTS Support CustomISAInfo
  ADD_TO_COMPONENT CustomISA
)
