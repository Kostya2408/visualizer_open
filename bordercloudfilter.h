#ifndef BORDERCLOUDFILTER_H
#define BORDERCLOUDFILTER_H
#include <pointcloud.h>

enum class BorderScheme{
    BORDER_3D,
    BORDER_X,
    BORDER_Y,
    BORDER_Z
};

class BorderCloudFilter
{
public:
    BorderCloudFilter();

    void setLimits(float min_x, float min_y, float min_z,
                   float max_x, float max_y, float max_z);
    void setLimitsX(float min_x, float max_x);
    void setLimitsY(float min_y, float max_y);
    void setLimitsZ(float min_z, float max_z);

    void filterCloud(PointCloud<PointXYZ> &source,
                    PointCloud<PointXYZ> &dst,
                    BorderScheme scheme);
    void filterCloud(PointCloud<PointXYZI> &source,
                    PointCloud<PointXYZI> &dst,
                    BorderScheme scheme);


private:
    float minX,maxX,minY,maxY,minZ,maxZ;

};

#endif // BORDERCLOUDFILTER_H
