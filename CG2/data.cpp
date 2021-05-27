#include "data.h"

void Data::readFile(QString filename)
{
    std::ifstream input(filename.toStdString(), std::ios::binary);

    input.read((char*)&width, sizeof(int));
    input.read((char*)&height, sizeof(int));
    input.read((char*)&depth, sizeof(int));

    input.read((char*)&x_voxel_size, sizeof(float));
    input.read((char*)&y_voxel_size, sizeof(float));
    input.read((char*)&z_voxel_size, sizeof(float));

    data = new short[width * height * depth];
    min = SHRT_MAX; max = SHRT_MIN;

    for (int i = 0; i < width * height * depth; i++)
    {
        input.read((char*)(data + i), sizeof(short));
        if (data[i] < min) min = data[i];
        if (data[i] > max) max = data[i];
    }
}

short Data::operator[](int i) { return data[i]; }

short Data::getMin() { return min; }

short Data::getMax() { return max; }

void Data::setMin(short value) { min = value; }

void Data::setMax(short value) { max = value; }

int Data::getWidth() { return width; }

int Data::getHeight() { return height; }

int Data::getDepth() { return depth; }
