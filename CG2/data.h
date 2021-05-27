#pragma once

#include <fstream>
#include <string>
#include <limits>
#include <QString>

class Data {
protected:
    int width, height, depth;
    short *data, min, max;
    float x_voxel_size, y_voxel_size, z_voxel_size;
public:
    void readFile(QString filename);

    short operator[](int i);

    short getMin();
    short getMax();

    void setMin(short value);
    void setMax(short value);

    int getWidth();
    int getHeight();
    int getDepth();
};
