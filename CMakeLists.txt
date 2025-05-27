# ##############################################################################

cmake_minimum_required(VERSION 3.16)

# Получаем имя проекта из имени директории
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} VERSION 1.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/archives)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ##############################################################################

option(${PROJECT_NAME}_BUILD_EXAMPLES "build examples" ON)
option(${PROJECT_NAME}_BUILD_TESTS "build tests" ON)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# ##############################################################################

include(cmake/fetch.cmake)
include_directories(${PROJECT_SOURCE_DIR}/include)

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fprofile-arcs
# -ftest-coverage") set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g
# -fprofile-arcs -ftest-coverage")

# ##############################################################################

add_subdirectory(libraries/Commands)
add_subdirectory(libraries/EntityComponentSystem)
add_subdirectory(libraries/Network)
add_subdirectory(libraries/InversionOfControl)
add_subdirectory(libraries/GameLogic)

# include(cmake/tests.cmake)

include(cmake/examples.cmake)

# include(cmake/install.cmake)
