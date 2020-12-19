cmake_minimum_required(VERSION 3.0.0)

#APPROACH:
#make ImageSet with double2s, indices, etc.
#load ImageSet onto CUDA and run kernel of it
#copy result back (a buffer of size N)

set(CUDASOURCES 
    "Reader.cpp"
    "ImageSet.cpp"
    "Kernels.cu"
)
add_executable(porous-cuda ${CUDASOURCES})
target_link_libraries(porous-cuda libporous)