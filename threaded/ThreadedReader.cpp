#include "ThreadedReader.h"

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
    void threaded_read(porous::ConcurrentQueue* entries, std::vector<std::string> const& files) {
        for (int i = 0; i < files.size(); i++) {
            try {
                InputFile in(files[i]);
                InputData datum;
                datum.energy=in.readEnergy();
                datum.position=std::move(in.readPositions()); //is this correct?
                if(!entries->enqueue(datum))
                {
                    i--;
                    std::this_thread::yield();
                }
            } catch(std::exception& e) {
                printf("%s\n",e.what());
                printf("Exception reading input file... skipping\n");
                continue;
            }
        }
        entries->finish();
    }
}

ThreadedReader::~ThreadedReader() {
    if (m_readthread.joinable())
    m_readthread.join();
}

ThreadedReader::ThreadedReader(std::string path, std::shared_ptr<porous::ConcurrentQueue> queue) : m_queue(queue) {
    m_paths = lst_directories(path);
    m_readthread = std::thread(threaded_read, m_queue.get(), m_paths);
}

ThreadedReader::ThreadedReader(ThreadedReader const& cp) {
    this->m_paths=cp.m_paths;
}

int ThreadedReader::getFileCount() {
    return this->m_paths.size();
}

std::shared_ptr<porous::ConcurrentQueue>& ThreadedReader::getQueue() {
    return m_queue;
}

TEST(TestThreadedReader, DoesItWork) {
    std::shared_ptr<porous::ConcurrentQueue> queue(new porous::ConcurrentQueue);
    ThreadedReader r("../samples",queue);
    while(true) {
        if (auto fetch=queue->dequeue_available(); fetch.size() > 0) {
            for (InputData& dat : fetch) {
                ASSERT_GE(dat.position.size(),0);
            }
        } else if (fetch.size() == 0) {
            const bool fin = queue->isFinished();
            if (fin) break;
            std::this_thread::yield();
        }
    }
}