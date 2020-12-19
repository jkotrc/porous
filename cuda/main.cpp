#include <iostream>


using namespace std;
using namespace porous;


int main(int argc, char** argv) {
    if (argc == 3) {
        printf("Reading from %s and writing to %s\n",argv[1],argv[2]);
        std::shared_ptr<porous::ConcurrentQueue> queue(new porous::ConcurrentQueue);
        ThreadedReader r(argv[1],queue);
        Writer w(queue.get(),r.getFileCount(),argv[2]);
        w.begin_write();
        return 0;
    } 
    cout << "USAGE: porous [data directory] [output file path]\n";
    cout << "any other arguments run the unit tests instead\n";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();   
}