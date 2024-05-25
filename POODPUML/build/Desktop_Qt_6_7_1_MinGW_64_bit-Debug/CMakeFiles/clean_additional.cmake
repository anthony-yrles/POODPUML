# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\POODPUML_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\POODPUML_autogen.dir\\ParseCache.txt"
  "POODPUML_autogen"
  )
endif()
