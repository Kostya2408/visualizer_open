#ifndef CLOUDTRANSFORMATION_H
#define CLOUDTRANSFORMATION_H
#include "pointcloud.h"
#include<math.h>


class CloudTransformation
{
public:
    CloudTransformation();
    void setParams(float tx, float ty, float tz,
                   float rx, float ry, float rz);
    void transformCloud(PointCloud<PointXYZ> &cloud);
    void transformCloud(PointCloud<PointXYZI> &cloud);
private:
    //текущее перемещение
    float current_t_x;
    float current_t_y;
    float current_t_z;
    //текущее вращение
    float current_r_x;
    float current_r_y;
    float current_r_z;
};

template<typename PointType>
PointType translatePoint(PointType point,
                         float tx,
                         float ty,
                         float tz) {
    PointType newPoint = point;
    newPoint.x = point.x + tx;
    newPoint.y = point.y + ty;
    newPoint.z = point.z + tz;
    return newPoint;
}
void matMultVec(float mat[3][3], float vec[3], float res[3]);

template <typename PointType>
PointType rotatePoint(PointType point,
                      float rx,
                      float ry,
                      float rz){

    float rotation_x[3][3] = {{1,0      ,       0},
                              {0,cos(rx),-sin(rx)},
                              {0,sin(rx), cos(rx)}};

    float rotation_y[3][3] = {{cos(ry) ,0,sin(ry)},
                              {0       ,1,      0},
                              {-sin(ry),0,cos(ry)}};

    float rotation_z[3][3] = {{cos(rz),-sin(rz),0},
                              {sin(rz),cos(rz), 0},
                              {0      ,0       ,1}};
    float oldPoint[3] = {point.x, point.y, point.z};
    float newPoint[3];
    matMultVec(rotation_z,oldPoint,newPoint);
    oldPoint[0] = newPoint[0];
    oldPoint[1] = newPoint[1];
    oldPoint[2] = newPoint[2];
    matMultVec(rotation_y,oldPoint,newPoint);
    oldPoint[0] = newPoint[0];
    oldPoint[1] = newPoint[1];
    oldPoint[2] = newPoint[2];
    matMultVec(rotation_x,oldPoint,newPoint);
    PointType result = point;
    result.x = newPoint[0];
    result.y = newPoint[1];
    result.z = newPoint[2];
    return result;

}

#endif // CLOUDTRANSFORMATION_H
