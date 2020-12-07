#pragma once
#include <string>
#include <filesystem>
#include <chrono>
#include <atomic>
#include <future>
#include <vector>
#include <H5Cpp.h>

#include "utility.h"
using namespace porous;

using namespace H5;

/*
A Reader class that takes in as input the path to either 'test' or 'train',
along with a pointer to the global queue that it should append to
making a directory list and having functions for read_next,
which are run on a separate thread
*/
using std::filesystem::directory_iterator;
using std::filesystem::directory_entry;

typedef std::vector<std::future<DataEntry>> future_entries_t;
typedef std::vector<std::promise<DataEntry>> promised_entries_t;

namespace porous {

    struct DataEntries {
        std::vector<DataEntry> entry;
        std::atomic_int max_available;
        DataEntries(int n) {entry=std::vector<DataEntry>();entry.resize(n);}
    };

    class Reader {
        private:
            std::thread reader_thread;
            std::atomic_int n_available{0};
            int file_count;
        public:
            Reader() = default;
            ~Reader() {if(reader_thread.joinable())reader_thread.join();}
            void read(std::vector<DataEntry>& ref, std::string path);
            int max_available(){return n_available.load();}
            int getFileCount(){return file_count;}
    };
}