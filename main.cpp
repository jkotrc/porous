#include <iostream>
#include <cstddef>
#include <cstring>
#include <string>

#include "reader.h"

using namespace std;

/*
command line arguments:
porous <path_to_base>
or porous -h
*/

const std::string help_msg = 
R"LITERAL(
porous is a program designed to read that massive collection of hdf5 files into one. \n
USAGE: porous [path to base directory] \n
where the base directory is the one containing all the hdf5 files. \n
)LITERAL";

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        cout << "Invalid arguments! See porous -h for help!\n";
        return -1;
    }
    if (strcmp(argv[1], "-h")==0) {
        cout << help_msg;
        return 0;
    }
    cout << "The path " << argv[1] << " will be read\n";
    porous::Reader r(argv[1]);
    cout << r.next().path().c_str() << endl;
    return 0;
}
