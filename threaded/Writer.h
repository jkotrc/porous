#pragma once
#include "ThreadedReader.h"
#include <commonlib/PorousDataSet.h>
#include <H5Cpp.h>
#include <string>

class Writer {
    private:
        uint8_t* m_buffer;
        porous::ConcurrentQueue* m_queue;
        H5::H5File m_outfile;
        porous::PorousDataSet m_dataset;
    public:
        Writer(porous::ConcurrentQueue* queue,int n_files,std::string outfilename);
        ~Writer();
        void begin_write();
};