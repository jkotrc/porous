#include "Reader.h"
#include "ConcurrentQueue.h"
#include <filesystem>
#include <gtest/gtest.h>
using namespace porous;
using namespace H5;

namespace {
    using std::filesystem::directory_iterator;
    std::vector<std::string> lst_directories(std::string const& dir_path) {
        std::vector<std::string> ret;
        Timer t("indexing files");
        for (auto& entry : directory_iterator(dir_path)) {
            ret.push_back(entry.path().string());
        }
        std::cout << "There are " << ret.size() << " to read\n";
        return ret;
    }
    void threaded_read(ConcurrentQueue* entries, std::vector<std::string> const& files) {
        for (int i = 0; i < files.size(); i++) {
            InputFile in(files[i]);
            InputData datum;
            datum.energy=in.readEnergy();
            datum.position=std::move(in.readPositions()); //is this correct?
            entries->enqueue(datum);
        }
        entries->finish();
    }
}

Reader::~Reader() {
    if (m_readthread.joinable())
    m_readthread.join();
}

Reader::Reader(std::string path) {
    m_paths = lst_directories(path);
}

void Reader::begin() {
    m_readthread = std::thread(threaded_read, &m_queue, m_paths);
}

Reader::Reader(Reader const& cp) {
    this->m_paths=cp.m_paths;
}

int Reader::getFileCount() {
    return this->m_paths.size();
}

ConcurrentQueue* Reader::getQueue() {
    return &m_queue;
}

std::vector<porous::InputData> Reader::get_available() {
    return m_queue.dequeue_available();
}

bool Reader::isFinished() {
    const bool fin = m_queue.isFinished();
    if (fin) {
        m_readthread.join();
        return true;
    }
    return fin;
//    return m_queue.isFinished();
}

TEST(TestReader, Works) {
    Reader r("../samples");
    r.begin();
    while(true){
        if (auto fetch=r.get_available(); fetch.size() > 0) {
            for (InputData& dat : fetch) {
                ASSERT_GE(dat.position.size(),0);
            }
        } else if (fetch.size() == 0) {
            const bool fin = r.isFinished();
            if (fin) break;
            std::this_thread::yield();
        }
    }
}