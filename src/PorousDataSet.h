#pragma once
#include <H5Cpp.h>

/*
PorousDataSet should be capable of appending energies, in addition to buffers
*/

class PorousDataSet {
    public:
        PorousDataSet();
        PorousDataSet(H5::H5File& parent, int length, int image_dimension);
        void addEntry(double energy,uint8_t* image);
        void addEntry(double energy);
        void setBuffer(uint8_t* buf);
    private:
        int m_index{0};
        int m_imagedim;
        
        uint8_t* m_buffer;

        H5::DataSpace m_energyspace;
        H5::DataSpace m_energymemspace;
        H5::DataSet* m_energydata;

        H5::DataSpace m_imagespace;
        H5::DataSpace m_imagememspace;
        H5::DataSet* m_imagedata;
};