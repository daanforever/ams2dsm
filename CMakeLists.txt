# CMakeList.txt : CMake project for Ams2DSM, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project("Ams2DSM" LANGUAGES CXX)    # Указываем язык C++

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if(MSVC)
    add_compile_options(/experimental:module)
    include_directories("$ENV{VCInstallDir}include")
	add_compile_options(/wd5304)  # Disable C5304
	set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pdb)
endif()

# Add include directories
include_directories(Ams2DSM PRIVATE "src")

# Add source to this project's executable.
add_executable(Ams2DSM
    src/main.cpp
)

target_sources(Ams2DSM PRIVATE
    FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
    src/Ams2DSM.cppm
)

# TODO: Add tests and install targets if needed.
