#pragma once
#include <vector>
#include <cstddef>
#include <atomic>

namespace porous {

    struct double3 {
        double x,y,z;
    };

    struct DataEntry {
        double energy;
        int position_length;
        double3* position;
    };


    class DataBuffer {
        private:
            int current;    //used by the processor to keep track of what was already done
            int n_entries; //todo: make this atomic
            std::vector<std::byte> _buffer;
        public:
            //it should not be possible to free_used and call next at the same time
            DataBuffer(int n_entries);
            ~DataBuffer();
            void add(DataEntry& entry);
            DataEntry* next();
    };
}