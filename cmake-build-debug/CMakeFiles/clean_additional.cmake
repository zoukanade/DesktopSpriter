# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DesktopSpriter_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DesktopSpriter_autogen.dir\\ParseCache.txt"
  "DesktopSpriter_autogen"
  )
endif()
