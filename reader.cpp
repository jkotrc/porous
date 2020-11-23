#include "reader.h"
#include <iostream>

namespace fs = std::filesystem;
using namespace std;
using namespace porous;

Reader::Reader(string path) {
    try {
        f_iter = file_iterator(path);
    } catch (std::exception& e) {
        cout << "path does not exist!....probably. Here's the details\n";
        cout << e.what() << endl;
    }   
}

const dir_entry& Reader::next() {
    f_iter++;
    return *f_iter;
}