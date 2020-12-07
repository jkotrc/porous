#pragma once
#include "utility.h"
#include <H5Cpp.h>

class InputFile : public H5::H5File {
    public:
        InputFile(std::string const& path);
        ~InputFile();
        double readEnergy();
        std::vector<porous::double2> readPositions();
};