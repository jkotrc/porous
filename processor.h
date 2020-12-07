#pragma once

#include <H5Cpp.h>
#include <string>
#include <algorithm>

namespace porous {
    using namespace H5;
    typedef std::pair<DataSpace,DataSet> h5data_t;

    struct DataEntry;
    class OutputFile {
        private:
            H5File m_file;

            h5data_t m_energy;
            h5data_t m_positions;

            int m_dimensions; //type=uint8
            int m_entrycount;
            int m_entryindex{0};
            float* image;
            bool m_saved{false};
        public:
            OutputFile(std::string name, int image_dimensions, int n_entries);
            ~OutputFile();
            void addEntry(DataEntry&& entry);
            void setEnergy(const float energy);
            void save();
    };
}