#pragma once
#include <H5Cpp.h>
#include <vector>
/*

H5File
DataSpace is made from dimensions
DataSet depends on H5File and DataSpace and is created through it

*/

namespace porous {
    using namespace H5;

    class Image {
        private:
            int m_dimension;
            uint8_t* pixels; //std::unique_ptr??
        public:
            ~Image();
            Image(int dim);
            int getDimension(){return m_dimension;}
            uint8_t* getBuffer(){return pixels;}
    };

    class ImageSet {
        private:
            std::vector<Image> images;
            H5File* m_parent;
            DataSet m_set;
            DataSpace m_space;
    };
}