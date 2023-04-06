#ifndef VOXELCLOUDFILTER_H
#define VOXELCLOUDFILTER_H
#include "pointcloud.h"
#include <iostream>
#include <time.h>


class VoxelCloudFilter
{
public:
    VoxelCloudFilter();
    void setCellSize(float cell);
    void filterCloud(PointCloud<PointXYZ> &source,
                     PointCloud<PointXYZ> &dst);
    void filterCloud(PointCloud<PointXYZI> &source,
                     PointCloud<PointXYZI> &dst);
private:
    float cellSize;
};
//фильтр - способ реализации 1 - кубики
template<typename PointType>
struct cubic {
    vector<PointType> includedPoints;
    //координаты кубика
    float x,y,z;
    //размер кубика
    float size;
};
//template<typename PointType>
//void voxelDistribution(PointCloud<PointType> &src,
//                            PointCloud<PointType> &dst,
//                            float cell){
//    //создаем кубики
//    vector<cubic<PointType> > cubicArray;
//    for(unsigned int i = 0; i < src.points.size();i++){
//        //вычисляем координаты кубика
//        float c_x = (int)(src.points.at(i).x/cell) * cell;
//        float c_y = (int)(src.points.at(i).y/cell) * cell;
//        float c_z = (int)(src.points.at(i).z/cell) * cell;
//        bool isCubicFound = false;
//        for(unsigned int j = 0; j < cubicArray.size();j++){
//            if(cubicArray.at(j).x == c_x &&
//                    cubicArray.at(j).y == c_y &&
//                    cubicArray.at(j).z == c_z){
//                //если находим кубик, то добавляем точку
//                cubicArray.at(j).includedPoints.push_back(
//                            src.points.at(i));
//                isCubicFound = true;
//                break;
//            }
//        }
//        //если кубик не нашли
//        if(!isCubicFound){
//            cubic<PointType> cub;
//            cub.x = c_x;
//            cub.y = c_y;
//            cub.z = c_z;
//            cub. includedPoints.push_back(src.points.at(i));
//            cubicArray.push_back(cub);
//        }
//        if(i%1000 == 0){
//            cout<<"Progress "<<i<<"/"<<src.points.size()<<endl;
//        }

//    }
//    dst.points.clear();
//    for(unsigned int j = 0;j < cubicArray.size();j++){
//        float a_x = 0, a_y = 0, a_z = 0;
//        for(unsigned int i = 0; i < cubicArray.at(j).includedPoints.size();
//            i++){
//            a_x += cubicArray.at(j).includedPoints.at(i).x;
//            a_y += cubicArray.at(j).includedPoints.at(i).y;
//            a_z += cubicArray.at(j).includedPoints.at(i).z;
//        }
//        a_x /= cubicArray.at(j).includedPoints.size();
//        a_y /= cubicArray.at(j).includedPoints.size();
//        a_z /= cubicArray.at(j).includedPoints.size();
//        PointType point = cubicArray.at(j).includedPoints.at(0);
//        point.x = a_x;
//        point.y = a_y;
//        point.z = a_z;
//        dst.points.push_back(point);
//    }
//}
//1 вычисление размера первого вокселя
//находим минимумы и максимумы по всем осям
//template<typename PointType>
//void voxelDistribution(PointCloud<PointType> &src,
//                       PointCloud<PointType> &dst,
//                       float cell){
//    float min_x = 1e9;
//    float min_y = 1e9;
//    float min_z = 1e9;
//    float max_x = -1e9;
//    float max_y = -1e9;
//    float max_z = -1e9;
//    for(unsigned int i = 0; i < src.points.size();i++){
//        PointType currentPoint = src.points.at(i);
//        if(currentPoint.x > max_x){
//            max_x = currentPoint.x;
//        }
//        if(currentPoint.y > max_y){
//            max_y = currentPoint.y;
//        }
//        if(currentPoint.z > max_z){
//            max_z = currentPoint.z;
//        }
//        if(currentPoint.x < min_x){
//            min_x = currentPoint.x;
//        }
//        if(currentPoint.y < min_y){
//            min_y = currentPoint.y;
//        }
//        if(currentPoint.z < min_z){
//            min_z = currentPoint.z;
//        }
//    }
//    float abs_min = min_x;
//    float abs_max = max_x;
//    if(min_y < abs_min){
//        abs_min = min_y;
//    }
//    if(min_z < abs_min){
//        abs_min = min_z;
//    }
//    if(max_y > abs_max){
//        abs_max = max_y;
//    }
//    if(max_z > abs_max){
//        abs_max = max_z;
//    }
//    float currentVoxelSize = cell;
//    while(currentVoxelSize < (abs_max - abs_min)){
//        currentVoxelSize = currentVoxelSize * 2;
//    }

//    //создавем масив вокселей и внедряем туда первый воксель
//    vector<cubic<PointType>> cubicArray;
//    cubic<PointType> currentCubic;
//    currentCubic.x = abs_min;
//    currentCubic.y = abs_min;
//    currentCubic.z = abs_min;
//    currentCubic.includedPoints = src.points;
//    cubicArray.push_back(currentCubic);

//    //3. Разделяем воксели
//    while(currentVoxelSize > cell){
//        vector<cubic<PointType>> childCubicArray;
//        currentVoxelSize = currentVoxelSize / 2;
//        for(unsigned int j = 0; j < cubicArray.size();j++){
//            //проходим по всем текущим вокселям и делим их на 8 и создаем 8 дочерних
//            for(int i_x = 0; i_x < 2; i_x++){
//                for(int j_y = 0; j_y < 2; j_y++){
//                    for(int k_z = 0; k_z < 2; k_z++){
//                        cubic<PointType> childCubic;
//                        childCubic.x = cubicArray.at(j).x + i_x * currentVoxelSize;
//                        childCubic.y = cubicArray.at(j).y + j_y * currentVoxelSize;
//                        childCubic.z = cubicArray.at(j).z + k_z * currentVoxelSize;
//                        childCubicArray.push_back(childCubic);

//                    }
//                }
//            }
//            //проходим по точкам текущего вокселя и распределяем их по дочерним вокселям
//            for(unsigned int i = 0; i < cubicArray.at(j).includedPoints.size();i++){
//                PointType currentPoint = cubicArray.at(j).includedPoints.at(i);
//                //проходим по всем дочерним вокселям и определяем, куда добавить точку
//                for(unsigned int k = 0; k < childCubicArray.size();k++){
//                    if(currentPoint.x >= childCubicArray.at(k).x &&
//                            currentPoint.y >= childCubicArray.at(k).y &&
//                            currentPoint.z >= childCubicArray.at(k).z &&
//                            currentPoint.x < childCubicArray.at(k).x + currentVoxelSize &&
//                            currentPoint.y < childCubicArray.at(k).y + currentVoxelSize &&
//                            currentPoint.z < childCubicArray.at(k).z + currentVoxelSize){
//                        childCubicArray.at(k).includedPoints.push_back(currentPoint);
//                        break;
//                    }
//                }
//            }
//        }
//        cout<<"Current voxel size "<<currentVoxelSize<<endl;
//        cubicArray.clear();
//        for(unsigned int m = 0; m < childCubicArray.size(); m++){
//            if(childCubicArray.at(m).includedPoints.size() > 0){
//                cubicArray.push_back(childCubicArray.at(m));
//            }
//        }
//    }
//    //4 анализируем воксели и усредняем точки в них

//    dst.points.clear();
//    for(unsigned int j = 0;j < cubicArray.size();j++){
//        float a_x = 0, a_y = 0, a_z = 0;
//        for(unsigned int i = 0; i < cubicArray.at(j).includedPoints.size();
//            i++){
//            a_x += cubicArray.at(j).includedPoints.at(i).x;
//            a_y += cubicArray.at(j).includedPoints.at(i).y;
//            a_z += cubicArray.at(j).includedPoints.at(i).z;
//        }
//        a_x /= cubicArray.at(j).includedPoints.size();
//        a_y /= cubicArray.at(j).includedPoints.size();
//        a_z /= cubicArray.at(j).includedPoints.size();
//        PointType point = cubicArray.at(j).includedPoints.at(0);
//        point.x = a_x;
//        point.y = a_y;
//        point.z = a_z;
//        dst.points.push_back(point);
//    }
//}



//---реализация через рекурсию

template<typename PointType>
void voxel_recursive(cubic<PointType>currentCubic,
                     float voxelSize,
                     vector<cubic<PointType>> & voxels){
    if(currentCubic.size <= voxelSize){
        voxels.push_back(currentCubic);
    }
    else{
        float currentVoxelSize = currentCubic.size/2;
        //проходим по всем текущим вокселям и делим их на 8 и создаем 8 дочерних
        for(int i_x = 0; i_x < 2; i_x++){
            for(int j_y = 0; j_y < 2; j_y++){
                for(int k_z = 0; k_z < 2; k_z++){
                    cubic<PointType> childCubic;
                    childCubic.x = currentCubic.x + i_x * currentVoxelSize;
                    childCubic.y = currentCubic.y + j_y * currentVoxelSize;
                    childCubic.z = currentCubic.z + k_z * currentVoxelSize;
                    childCubic.size = currentVoxelSize;

                    for(unsigned int i = 0; i < currentCubic.includedPoints.size();i++){
                        PointType currentPoint = currentCubic.includedPoints.at(i);
                        //проходим по всем дочерним вокселям и определяем, куда добавить точку

                        if(currentPoint.x >=  childCubic.x &&
                                currentPoint.y >=  childCubic.y &&
                                currentPoint.z >=  childCubic.z &&
                                currentPoint.x <  childCubic.x + currentVoxelSize &&
                                currentPoint.y <  childCubic.y + currentVoxelSize &&
                                currentPoint.z <  childCubic.z + currentVoxelSize){
                            childCubic.includedPoints.push_back(currentPoint);


                        }
                    }
                    if(childCubic.includedPoints.size()>0){
                        voxel_recursive(childCubic,voxelSize,voxels);
                    }
                }

            }
        }
    }
}


template<typename PointType>
void voxelDistribution(PointCloud<PointType> &src,
                       PointCloud<PointType> &dst,
                       float cell){
    float min_x = 1e9;
    float min_y = 1e9;
    float min_z = 1e9;
    float max_x = -1e9;
    float max_y = -1e9;
    float max_z = -1e9;
    for(unsigned int i = 0; i < src.points.size();i++){
        PointType currentPoint = src.points.at(i);
        if(currentPoint.x > max_x){
            max_x = currentPoint.x;
        }
        if(currentPoint.y > max_y){
            max_y = currentPoint.y;
        }
        if(currentPoint.z > max_z){
            max_z = currentPoint.z;
        }
        if(currentPoint.x < min_x){
            min_x = currentPoint.x;
        }
        if(currentPoint.y < min_y){
            min_y = currentPoint.y;
        }
        if(currentPoint.z < min_z){
            min_z = currentPoint.z;
        }
    }
    float abs_min = min_x;
    float abs_max = max_x;
    if(min_y < abs_min){
        abs_min = min_y;
    }
    if(min_z < abs_min){
        abs_min = min_z;
    }
    if(max_y > abs_max){
        abs_max = max_y;
    }
    if(max_z > abs_max){
        abs_max = max_z;
    }
    float currentVoxelSize = cell;
    while(currentVoxelSize < (abs_max - abs_min)){
        currentVoxelSize = currentVoxelSize * 2;
    }

    //создавем масив вокселей и внедряем туда первый воксель
    vector<cubic<PointType>> cubicArray;
    cubic<PointType> currentCubic;
    currentCubic.x = abs_min;
    currentCubic.y = abs_min;
    currentCubic.z = abs_min;
    currentCubic.includedPoints = src.points;
    currentCubic.size = currentVoxelSize;

    //3. рекурсивное разделение на кубики
    voxel_recursive(currentCubic,cell,cubicArray);
    //4 анализируем воксели и усредняем точки в них

    dst.points.clear();
    for(unsigned int j = 0;j < cubicArray.size();j++){
        float a_x = 0, a_y = 0, a_z = 0;
        for(unsigned int i = 0; i < cubicArray.at(j).includedPoints.size();
            i++){
            a_x += cubicArray.at(j).includedPoints.at(i).x;
            a_y += cubicArray.at(j).includedPoints.at(i).y;
            a_z += cubicArray.at(j).includedPoints.at(i).z;
        }
        a_x /= cubicArray.at(j).includedPoints.size();
        a_y /= cubicArray.at(j).includedPoints.size();
        a_z /= cubicArray.at(j).includedPoints.size();
        PointType point = cubicArray.at(j).includedPoints.at(0);
        point.x = a_x;
        point.y = a_y;
        point.z = a_z;
        dst.points.push_back(point);
    }
}
//фильтр - способ реализации 2 - округление
#endif // VOXELCLOUDFILTER_H
