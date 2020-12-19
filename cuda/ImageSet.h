#pragma once

#include <commonlib/utility.h>
#include <memory>
#include <vector>

struct ImageSet {
    size_t N;
    std::vector<porous::double2> positions;
    std::vector<double> energies;
    std::vector<int> breakpoints;
};
struct ImageSetPtr {
    const porous::double2* positions;
    const double* energies;
    const int* breakpoints;
    ImageSetPtr(ImageSet const& set) noexcept {
        positions=&set.positions[0];
        energies=&set.energies[0];
        breakpoints=&set.breakpoints[0];
    }
};