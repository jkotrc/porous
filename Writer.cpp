#include "Writer.h"
#include "Reader.h"
using namespace H5;
using namespace porous;

namespace {
    /*inline void compute_V(uint8_t* buffer, std::vector<double2> positions) {
        float ret=0;
        for (const double2& point : entry.position) {
            ret += exp(- (  SQ(x-point.x)+SQ(y-point.y)  )/(2*SQ(GAMMA)));
        }
        ret*=Zi;
        return ret;
    }*/
}

Writer::Writer(Reader const& reader,std::string outfilename) : m_reader(reader) {
    m_outfile = H5File(outfilename,H5F_ACC_TRUNC);
    m_dataset = PorousDataSet(m_outfile, m_reader.getFileCount(),400);
}

void Writer::begin_write() {
    while(true) {
        if(auto entries = m_reader.get_available(); entries.size() == 0) {
            if(m_reader.isFinished()) break;
            std::this_thread::yield();
        } else {
            for (auto& entry: entries) {
                
                m_dataset.addEntry(entry.energy);
            }
        }
    }
}