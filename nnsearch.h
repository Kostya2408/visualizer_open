#ifndef NNSEARCH_H
#define NNSEARCH_H
#include "pointcloud.h"
#include <iostream>

using namespace std;

class NNsearch
{
public:
    NNsearch();
    PointXYZ nearestSearch(PointXYZ target_point,
                            PointCloud<PointXYZ> &cloud);
    PointXYZI nearestSearch(PointXYZI target_point,
                            PointCloud<PointXYZI> &cloud);
    PointXYZRGB nearestSearch(PointXYZRGB target_point,
                            PointCloud<PointXYZRGB> &cloud);
    vector<PointXYZ> radiusSearch(PointXYZ target_point,
                            PointCloud<PointXYZ> &cloud,
                           float radius);
    vector<PointXYZI> radiusSearch(PointXYZI target_point,
                            PointCloud<PointXYZI> &cloud,
                           float radius);

};

#endif // NNSEARCH_H

