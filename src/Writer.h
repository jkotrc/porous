#pragma once
#include "Reader.h"
#include "PorousDataSet.h"
#include <H5Cpp.h>
#include <string>
using namespace porous;
class Writer {
    private:
        uint8_t* m_buffer;
        ConcurrentQueue* m_queue;
        H5::H5File m_outfile;
        PorousDataSet m_dataset;
    public:
        Writer(ConcurrentQueue* queue,int n_files,std::string outfilename);
        ~Writer();
        void begin_write();
};