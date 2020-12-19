cmake_minimum_required(VERSION 3.0.0)

set(LIBSOURCES 
    "ConcurrentQueue.cpp"
    "InputFile.cpp"
    "utility.cpp"
    "PorousDataSet.cpp"
    "utility.cpp"
)

add_library(libporous ${LIBSOURCES})
target_link_libraries(libporous 
    ${HDF5_LIBRARIES}
    ${GTEST_LIBRARIES}
)