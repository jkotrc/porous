#include <iostream>

#include "PorousDataSet.h"
#include "utility.h"
#include "Reader.h"
#include "Writer.h"

#include <gtest/gtest.h>

using namespace std;
using namespace porous;

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    /*
    string path = "something";
    Reader r(path);

    Writer w(r, "output.h5");
    w.begin_write();

    std::cout << "Hello, world!\n";
    */
   return RUN_ALL_TESTS();
}
