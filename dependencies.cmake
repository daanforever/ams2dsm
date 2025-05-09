include(FetchContent)

###############################################################################
# Boost
###############################################################################

set(BOOST_INCLUDE_LIBRARIES hana)
set(BOOST_ENABLE_CMAKE ON)

FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.88.0
)
FetchContent_MakeAvailable(Boost)

###############################################################################
# Boost Hana
###############################################################################

# set(BOOST_INCLUDE_LIBRARIES hana)
# set(BOOST_ENABLE_CMAKE ON)

# FetchContent_Declare(
#   hana
#   GIT_REPOSITORY https://github.com/boostorg/hana.git
#   GIT_TAG boost-1.88.0
# )
# FetchContent_MakeAvailable(hana)

###############################################################################
# Web Server
###############################################################################

set(ZLIB_BUILD_EXAMPLES OFF)

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
# yaml
###############################################################################

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG 0.8.0
)
FetchContent_MakeAvailable(yaml-cpp)

###############################################################################
# logger
###############################################################################

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(spdlog)

###############################################################################
# UUID
###############################################################################

set(UUID_BUILD_TESTS OFF)

FetchContent_Declare(
  uuid
  GIT_REPOSITORY https://github.com/mariusbancila/stduuid.git
  GIT_TAG v1.2.3
)
FetchContent_MakeAvailable(uuid)

###############################################################################
# inja
###############################################################################

set(BUILD_TESTING OFF)
set(INJA_BUILD_TESTS OFF)
set(BUILD_BENCHMARK OFF)

include(FetchContent)
FetchContent_Declare(inja
    GIT_REPOSITORY https://github.com/pantor/inja.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(inja)
