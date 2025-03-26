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

###############################################################################
# ASIO
###############################################################################

include(FetchContent)
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-34-0
)

FetchContent_MakeAvailable(asio)
set(ASIO_INCLUDE_DIR "${asio_SOURCE_DIR}/asio/include")

###############################################################################
# Crow
###############################################################################

set(CROW_BUILD_EXAMPLES Off)
set(CROW_BUILD_TOOLS Off)
set(CROW_BUILD_TESTS Off)
set(CROW_BUILD_DOCS Off)

include(FetchContent)
FetchContent_Declare(
    crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.2.1.2
)
FetchContent_MakeAvailable(crow)
set(CROW_INCLUDE_DIR "${crow_SOURCE_DIR}/include")

###############################################################################
# Main
###############################################################################

add_executable(Ams2DSM
    src/main.cpp
)

target_include_directories(Ams2DSM PUBLIC ${ASIO_INCLUDE_DIR} ${CROW_INCLUDE_DIR})
message(STATUS "ASIO_INCLUDE_DIR: ${ASIO_INCLUDE_DIR}")
message(STATUS "CROW_INCLUDE_DIR: ${CROW_INCLUDE_DIR}")

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
    src/dsm.cppm
	src/web_server.cppm
)

###############################################################################
# Google Test
###############################################################################

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.16.0
)
FetchContent_MakeAvailable(googletest)

set(GTEST_INCLUDE_DIR "${gtest_SOURCE_DIR}/include")

if(MSVC)
	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)
endif()

find_package(GTest)
include(GoogleTest)

# Создаем тестовый модуль
add_executable(runUnitTests "tests/first.cppm")

target_sources(runUnitTests PRIVATE
    FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
    tests/first.cppm
)

if(MSVC)
    set_source_files_properties(tests.cpp PROPERTIES
        COMPILE_FLAGS "/experimental:module /module:export"
    )

	set(CMAKE_MSVC_INCREMENTAL_LINKER_DEFAULT "OFF")
	set(CMAKE_COMPILE_PDB_OFF 1)
endif()

target_link_libraries(runUnitTests PRIVATE gtest_main)

#enable_testing()
#gtest_discover_tests(runUnitTests)