﻿# CMakeList.txt : CMake project for ams2dsm, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8...3.31.6)
project(ams2dsm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_PCH_ENABLED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CMakeInitializeConfigs)
include(dependencies.cmake)

###############################################################################
# Main
###############################################################################

add_library(ams2dsmlib)

target_sources(ams2dsmlib PRIVATE
	"src/web/server/core.cpp"
	"src/web/server/router.cpp"
	"src/web/server/routes.cpp"
	"src/web/server/request.cpp"
	"src/web/server/response.cpp"
	"src/web/server/controller/index.cpp"
	"src/web/server/controller/login.cpp"
	"src/web/server/middlewares/auth.cpp"
	"src/web/server/cookie.cpp"
	"src/web/server/session_manager.cpp"
	"src/web/server/logger.cpp"
	"src/web/server/application.cpp"
)

target_sources(ams2dsmlib PUBLIC
    FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
	"src/config.cppm"
	"src/logger.cppm"
    "src/uuid.cppm"
)

# target_include_directories(ams2dsmlib PUBLIC
# 	${zlib_SOURCE_DIR}
# 	${cpp-httplib_SOURCE_DIR}
# 	${uuid_SOURCE_DIR}/include
# 	${inja_SOURCE_DIR}/include/inja
# )

target_link_libraries(ams2dsmlib PUBLIC httplib yaml-cpp::yaml-cpp spdlog::spdlog stduuid pantor::inja )


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/web
		COMMAND ${CMAKE_COMMAND} -E create_symlink
			${CMAKE_SOURCE_DIR}/web
			${CMAKE_CURRENT_BINARY_DIR}/web
		DEPENDS ${CMAKE_SOURCE_DIR}/web
		COMMENT "Creating symlink for web"
	)
else()
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/web
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/web
			${CMAKE_CURRENT_BINARY_DIR}/web
		DEPENDS ${CMAKE_SOURCE_DIR}/web
		COMMENT "Copy files for web"
	)
endif()

add_custom_target(
  prepare_web
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/web
)

add_executable(ams2dsm "src/main.cpp")

include_directories(ams2dsm PRIVATE "src" "src/include")
target_link_libraries(ams2dsm PUBLIC ams2dsmlib)
add_dependencies(ams2dsm prepare_web)

###############################################################################
# Google Test
###############################################################################

if(MSVC)
	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# set(INSTALL_GTEST OFF)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.16.0
)
FetchContent_MakeAvailable(googletest)

# set(GTEST_INCLUDE_DIR "${gtest_SOURCE_DIR}/include")

###############################################################################
# Tests
###############################################################################

enable_testing()

add_executable(dsmTest)

target_sources(dsmTest PRIVATE
	"tests/web/server.test.cpp"
)

target_sources(dsmTest PRIVATE
    FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
		
		"tests/config.test.cppm"
)

target_include_directories(dsmTest PUBLIC ${cpp-httplib_SOURCE_DIR} "${gmock_SOURCE_DIR}/include")
target_link_libraries(dsmTest PRIVATE ams2dsmlib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(dsmTest)


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
