include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)

set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/3rdparty)

set(BOOST_INCLUDE_LIBRARIES system serialization asio stacktrace)
set(FETCHCONTENT_DOWNLOAD_DIR
    "${CMAKE_SOURCE_DIR}/3rdparty/downloads"
    CACHE PATH "Directory to download dependencies")

add_definitions(-DBOOST_ALL_NO_LIB)
add_definitions(-DBOOST_ALL_DYN_LINK)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  GIT_PROGRESS TRUE
  DOWNLOAD_EXTRACT_TIMESTAMP ON)
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
if(NOT googletest_POPULATED)
  FetchContent_MakeAvailable(googletest)
endif()

include(FetchContent)

FetchContent_Declare(
  Boost
  URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
  URL_MD5 893b5203b862eb9bbd08553e24ff146a
  DOWNLOAD_EXTRACT_TIMESTAMP ON
  GIT_PROGRESS TRUE)

if(NOT boost_POPULATED)
  FetchContent_MakeAvailable(Boost)
  include_directories(${BOOST_LIBRARY_INCLUDES})
endif()
