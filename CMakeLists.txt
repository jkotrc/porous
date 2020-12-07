cmake_minimum_required(VERSION 3.0.0)
project(porous VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES 
    "ConcurrentQueue.cpp"
    "utility.h"
    "InputFile.cpp"
    "Reader.cpp"
    "PorousDataSet.cpp"
    "Writer.cpp"
    "testthis.cpp"
)
#procedure: spawn a reader on a directory that will write data entries to a concurrent queue
#make a writer that is given a reader
#in the writer, while reader.hasnext
#write(std::move(entry))
    #takes the entry and writes an image to m_buffer
    #write m_buffer to output file


find_package(HDF5 COMPONENTS CXX HL)
find_package(GTest REQUIRED)
include_directories(
    ${HDF5_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
)

add_executable(porous main.cpp ${SOURCES})
target_link_libraries(porous 
    ${HDF5_LIBRARIES}
    ${GTEST_LIBRARIES}
    pthread
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
