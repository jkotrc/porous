cmake_minimum_required(VERSION 3.0.0)
project(porous VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES 
    "src/main.cpp"
    "src/ConcurrentQueue.cpp"
    "src/utility.cpp"
    "src/InputFile.cpp"
    "src/Reader.cpp"
    "src/PorousDataSet.cpp"
    "src/Writer.cpp"
)

find_package(HDF5 COMPONENTS CXX HL)
enable_testing()
find_package(GTest REQUIRED)
include_directories(
    ${HDF5_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
)

add_executable(porous ${SOURCES})
target_link_libraries(porous 
    ${HDF5_LIBRARIES}
    ${GTEST_LIBRARIES}
    pthread
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
