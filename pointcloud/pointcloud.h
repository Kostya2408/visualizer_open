#ifndef POINTCLOUDXYZ_H
#define POINTCLOUDXYZ_H
#include <vector>
#include<fstream>
#include<string>
#include "points.h"

using namespace std;

template <typename PointType>
class PointCloud
{
public:
    //точки
    vector<PointType> points;
    //сохранение в файл
    void saveToFile(string path);

};

#endif // POINTCLOUD_H
