#pragma once
#include "Reader.h"
#include "PorousDataSet.h"
#include <H5Cpp.h>
#include <string>
using namespace porous;
class Writer {
    private:
        uint8_t* m_buffer;
        Reader m_reader;
        H5::H5File m_outfile;
        PorousDataSet m_dataset;
    public:
        Writer(Reader const& reader,std::string outfilename);//this is just a sketch
        ~Writer();
        void begin_write();
};