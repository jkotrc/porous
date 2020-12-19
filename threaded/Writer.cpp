#include "Writer.h"
#include "ThreadedReader.h"

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
    uint32_t n_entries=0;
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
        printf("Entry %u completed\n",n_entries);
    }
}

Writer::Writer(porous::ConcurrentQueue* queue,int n_files,std::string outfilename) : m_queue(queue) {
    m_outfile = H5File(outfilename, H5F_ACC_TRUNC);
    m_dataset = PorousDataSet(m_outfile, n_files,image_dimension);
    m_buffer = new uint8_t[image_dimension*image_dimension];
    m_dataset.setBuffer(m_buffer);
}

Writer::~Writer() {}

void Writer::begin_write() {
    while(true) {
        if(auto entries = m_queue->dequeue_available(); entries.size() == 0) {
            const bool fin = m_queue->isFinished();
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
    std::shared_ptr<porous::ConcurrentQueue> queue(new porous::ConcurrentQueue);
    ThreadedReader r("../samples",queue);
    Writer w(queue.get(),r.getFileCount(),"../writer_out.h5");
    w.begin_write();
}