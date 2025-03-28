# CMakeList.txt : CMake project for ams2dsm, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(ams2dsm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_PCH_ENABLED OFF)

include(CMakeInitializeConfigs)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

include(FetchContent)

###############################################################################
# Web Server
###############################################################################

FetchContent_Declare(
    zlib
    GIT_REPOSITORY https://github.com/madler/zlib.git
	GIT_TAG v1.3.1
)
FetchContent_MakeAvailable(zlib)

FetchContent_Declare(
    cpp-httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
	GIT_TAG v0.20.0
)
FetchContent_MakeAvailable(cpp-httplib)

# get_property(LOCAL_VARS DIRECTORY PROPERTY VARIABLES)
# foreach(VAR ${LOCAL_VARS})
#     message(STATUS "LOCAL: ${VAR} = ${${VAR}}")
# endforeach()

###############################################################################
# Main
###############################################################################

add_library(ams2dsmlib "src/web/server.cpp")

target_sources(ams2dsmlib PUBLIC
    FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
		"src/web/server/routes.cppm"
)

target_include_directories(ams2dsmlib PUBLIC ${cpp-httplib_SOURCE_DIR})

include_directories(ams2dsm PRIVATE "src" "src/include")
add_executable(ams2dsm "src/main.cpp")
target_link_libraries(ams2dsm PUBLIC ams2dsmlib)

add_custom_target(WebCopy ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/web
        ${CMAKE_CURRENT_BINARY_DIR}/web
    DEPENDS ${CMAKE_SOURCE_DIR}/web
)

add_custom_target(WebSymlink ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/web
        ${CMAKE_CURRENT_BINARY_DIR}/web
    DEPENDS ${CMAKE_SOURCE_DIR}/web
)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_dependencies(ams2dsm WebSymlink)
else()
    add_dependencies(ams2dsm WebCopy)
endif()

if(MSVC)
    #add_compile_options(/experimental:module)
	add_compile_options(/wd5304)  # Disable C5304
	set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pdb)

	set_target_properties(ams2dsm PROPERTIES
		PDB_OUTPUT_DIRECTORY ${CMAKE_PDB_OUTPUT_DIRECTORY}
		COMPILE_PDB_NAME "ams2dsm"
    )
endif()

###############################################################################
# cpr for tests
###############################################################################

# set(CPR_ENABLE_SSL OFF)
# set(CURL_DISABLE_ALTSVC ON)
# set(CURL_DISABLE_SRP ON)
# set(ENABLE_IPV6 OFF)
# 
# include(FetchContent)
# FetchContent_Declare(
# 	cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
#     GIT_TAG 1.11.2
# )
# FetchContent_MakeAvailable(cpr)
# 
# # get_property(LOCAL_VARS DIRECTORY PROPERTY VARIABLES)
# # foreach(VAR ${LOCAL_VARS})
# #     message(STATUS "LOCAL: ${VAR} = ${${VAR}}")
# # endforeach()
# 
# set(CURL_INCLUDE_DIR "${CURL_SOURCE_DIR}/include")
# set(CPR_INCLUDE_DIR "${cpr_SOURCE_DIR}/include")
# 
# message(STATUS "CURL_INCLUDE_DIR: ${CURL_INCLUDE_DIR}")
# message(STATUS "CPR_INCLUDE_DIR: ${CPR_INCLUDE_DIR}")


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
endif()

include(GoogleTest)

# Создаем тестовый модуль
add_executable(runUnitTests)

# target_include_directories(runUnitTests PUBLIC ${ASIO_INCLUDE_DIR} ${CROW_INCLUDE_DIR} ${CURL_INCLUDE_DIR} ${CPR_INCLUDE_DIR})
# target_include_directories(runUnitTests PUBLIC ${ASIO_INCLUDE_DIR} ${CROW_INCLUDE_DIR})

target_sources(runUnitTests PRIVATE
	"tests/web/server.test.cpp"
)


target_sources(runUnitTests PRIVATE
    FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
		"tests/first.test.cppm"
)

target_include_directories(runUnitTests PUBLIC ${cpp-httplib_SOURCE_DIR})
target_link_libraries(runUnitTests PRIVATE ams2dsmlib gtest_main)

#enable_testing()
#gtest_discover_tests(runUnitTests)