#pragma once
#include <string>
#include "ImageSet.h"

class CudaReader /*: public NumberedReader*/ {
    public:
        CudaReader()=delete;
        CudaReader(std::string input_path);
        ~CudaReader();
        ImageSet nextN(int N);
        bool hasNext();        
    private:
        int m_filecount;
        int m_currentfile;
};