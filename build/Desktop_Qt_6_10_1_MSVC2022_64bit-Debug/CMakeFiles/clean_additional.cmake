# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\projeto_automacao_teste_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\projeto_automacao_teste_autogen.dir\\ParseCache.txt"
  "projeto_automacao_teste_autogen"
  )
endif()
