#include "Writer.h"
#include "Reader.h"

#include <gtest/gtest.h>
#include <cmath>
using namespace H5;
using namespace porous;

constexpr int image_dimension=400;
//constexpr double gamma = 0.2;
constexpr int Zi=12;
constexpr double GAMMA = 0.2;
constexpr double sq(const double x) {
    return x*x;
}

namespace {
    inline void V(uint8_t* buffer, const std::vector<double2>& positions) {
        Timer t("potential computation");
        for (int j = 0; j < image_dimension; j++) {
            for (int i = 0; i < image_dimension; i++) {
                double ret=0;
                const double x = ((double)i)*30.0/((double)image_dimension);
                const double y = 30.0-((double)j)*30.0/((double)image_dimension);
                for (const double2& point : positions) {
                    const double dist = sq(x-point.x)+sq(y-point.y);
                    ret += exp(- (  dist  )/(2*sq(GAMMA)));
                }
                ret*=255;
                buffer[j*400+i]=ret;
            }
        }
    }
}


Writer::Writer(Reader const& reader,std::string outfilename) : m_reader(reader) {
    m_outfile = H5File(outfilename,H5F_ACC_TRUNC);
    m_dataset = PorousDataSet(m_outfile, m_reader.getFileCount(),image_dimension);
    m_buffer = new uint8_t[image_dimension*image_dimension];
    m_dataset.setBuffer(m_buffer);
    m_reader.begin();
}

Writer::~Writer() {

}

void Writer::begin_write() {
    while(true) {
        if(auto entries = m_reader.get_available(); entries.size() == 0) {
            const bool fin = m_reader.isFinished();
            if(fin){
                std::cout << "Done writing!\n";
                return;
            }
            std::this_thread::yield();
        } else {
            for (auto& entry: entries) {
                V(m_buffer, entry.position);
                m_dataset.addEntry(entry.energy);
            }
        }
    }
}

TEST(TestWriter, writingtest) {
    Reader r("../samples");
    Writer w(r,"../writer_out.h5");
    w.begin_write();
}