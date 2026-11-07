add_llvm_component_library(LLVMCustomISAInfo
  CustomISATargetInfo.cpp
  LINK_COMPONENTS Support
  ADD_TO_COMPONENT CustomISA
)
