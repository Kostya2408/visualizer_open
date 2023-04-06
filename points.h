#ifndef POINTS_H
#define POINTS_H

//проствая точка
struct PointXYZ{
    float x;
    float y;
    float z;
};
//точка с интенсивностью
struct PointXYZI{
    float x;
    float y;
    float z;
    float intensity;
};
//Точка со значением цвета в RGB
struct PointXYZRGB{
    float x;
    float y;
    float z;
    float R;
    float G;
    float B;
};


#endif // POINTS_H
