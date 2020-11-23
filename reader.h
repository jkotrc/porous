#pragma once
#include <string>
#include <filesystem>


/*
A Reader class that takes in as input the path to either 'test' or 'train',
along with a pointer to the global queue that it should append to
making a directory list and having functions for read_next,
which are run on a separate thread
*/

//A reader class will be instantiated on a new thread
//it will go on while there are still new files
//and log how much stuff it did to some text file or stdout or something

typedef std::filesystem::directory_iterator file_iterator;
typedef std::filesystem::directory_entry dir_entry;

namespace porous {

    class Reader {
        private:
            file_iterator f_iter;
        public:
            Reader(std::string basedir);
            const dir_entry& next();

    };

}