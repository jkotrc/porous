cmake_minimum_required(VERSION 3.0.0)
project(porous LANGUAGES CXX CUDA)



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(HDF5 COMPONENTS CXX HL)
enable_testing()
find_package(GTest REQUIRED)

include_directories(
    ${HDF5_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
    "./"
)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(commonlib)
add_subdirectory(threaded)
add_subdirectory(cuda)