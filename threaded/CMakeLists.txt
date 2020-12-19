cmake_minimum_required(VERSION 3.0.0)

set(SOURCES 
    "main.cpp"
    "ThreadedReader.cpp"
    "Writer.cpp"
)

add_executable(porous-threaded ${SOURCES})
target_link_libraries(porous-threaded 
    libporous
    #${HDF5_LIBRARIES}
    #${GTEST_LIBRARIES}
    #pthread
)