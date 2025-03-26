# CMakeList.txt : CMake project for Ams2DSM, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(Ams2DSM LANGUAGES CXX)    # Указываем язык C++

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

include(CMakeInitializeConfigs)

include_directories(Ams2DSM PRIVATE "src")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_executable(Ams2DSM
    src/main.cpp
)

if(MSVC)
    add_compile_options(/experimental:module)
	add_compile_options(/wd5304)  # Disable C5304
	set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pdb)

	set_target_properties(Ams2DSM PROPERTIES
		PDB_OUTPUT_DIRECTORY ${CMAKE_PDB_OUTPUT_DIRECTORY}
		COMPILE_PDB_NAME "Ams2DSM"
    )
endif()

target_sources(Ams2DSM PRIVATE
    FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
    src/Ams2DSM.cppm
)