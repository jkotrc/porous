#include "imageset.h"

using namespace porous;

Image::Image(int dim) : m_dimension(dim) {
    pixels = new uint8_t[dim*dim];

}
Image::~Image() {
    delete[] pixels;
}
