#ifndef POINTCLOUDXYZ_H
#define POINTCLOUDXYZ_H
#include <vector>
#include<fstream>
#include<string>
#include "points.h"

using namespace std;

class PointCloudXYZ
{
public:
    //Точки
    vector<PointXYZ> points;
    //сохранение в файл
    void saveToFile(string path);
};
#endif // POINTCLOUDXYZ_H
