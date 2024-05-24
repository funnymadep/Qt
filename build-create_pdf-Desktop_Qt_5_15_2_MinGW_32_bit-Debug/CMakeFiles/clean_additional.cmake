# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\create_pdf_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\create_pdf_autogen.dir\\ParseCache.txt"
  "create_pdf_autogen"
  )
endif()
