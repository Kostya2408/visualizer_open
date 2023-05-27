#include "nnsearch.h"

NNsearch::NNsearch()
{


}
PointXYZ NNsearch::nearestSearch(PointXYZ target_point,
                                  PointCloud<PointXYZ> &cloud){

    float min_distance = 9999999;//vikcitnado
    float x_target = 0;
    float y_target = 0;
    float z_target = 0;
    float i_target = 0;
    float distanse_between_points = 0;
    for(unsigned int i=0; i < cloud.points.size();i++){
        distanse_between_points = (cloud.points.at(i).x - x_target)*(cloud.points.at(i).x - x_target)+
                (cloud.points.at(i).y - y_target)*(cloud.points.at(i).y - y_target)+
                (cloud.points.at(i).z - z_target)*(cloud.points.at(i).z - z_target);
        if(min_distance > distanse_between_points){
            min_distance = distanse_between_points;
            i_target = i;
        }
    }
    return cloud.points.at(i_target);
}
PointXYZI NNsearch::nearestSearch(PointXYZI target_point,
                                  PointCloud<PointXYZI> &cloud){

    float min_distance = 9999999;//vikcitnado
    float x_target = 0;
    float y_target = 0;
    float z_target = 0;
    float i_target = 0;
    float distanse_between_points = 0;
    for(unsigned int i=0; i < cloud.points.size();i++){
        distanse_between_points = (cloud.points.at(i).x - x_target)*(cloud.points.at(i).x - x_target)+
                (cloud.points.at(i).y - y_target)*(cloud.points.at(i).y - y_target)+
                (cloud.points.at(i).z - z_target)*(cloud.points.at(i).z - z_target);
        if(min_distance > distanse_between_points){
            min_distance = distanse_between_points;
            i_target = i;
        }
    }
    return cloud.points.at(i_target);
}
PointXYZRGB NNsearch::nearestSearch(PointXYZRGB target_point,
                                  PointCloud<PointXYZRGB> &cloud){

    float min_distance = 9999999;//vikcitnado
    float x_target = 0;
    float y_target = 0;
    float z_target = 0;
    float i_target = 0;
    float distanse_between_points = 0;
    for(unsigned int i=0; i < cloud.points.size();i++){
        distanse_between_points = (cloud.points.at(i).x - x_target)*(cloud.points.at(i).x - x_target)+
                (cloud.points.at(i).y - y_target)*(cloud.points.at(i).y - y_target)+
                (cloud.points.at(i).z - z_target)*(cloud.points.at(i).z - z_target);
        if(min_distance > distanse_between_points){
            min_distance = distanse_between_points;
            i_target = i;
        }
    }
    return cloud.points.at(i_target);
}
vector<PointXYZ> NNsearch::radiusSearch(PointXYZ target_point,
                                         PointCloud<PointXYZ> &cloud,
                                         float radius){
    float x_target = 0;
    float y_target = 0;
    float z_target = 0;
    float i_target = 0;
    float distanse_between_points = 0;
    vector <PointXYZ> raduisPoints;
    for(int i=0; i < cloud.points.size();i++){
        distanse_between_points = (cloud.points.at(i).x - x_target)*(cloud.points.at(i).x - x_target)+
                (cloud.points.at(i).y - y_target)*(cloud.points.at(i).y - y_target)+
                (cloud.points.at(i).z - z_target)*(cloud.points.at(i).z - z_target);
        if(radius >= distanse_between_points){
            raduisPoints.push_back(cloud.points.at(i));
        }
    }
    return raduisPoints;
}
vector<PointXYZI> NNsearch::radiusSearch(PointXYZI target_point,
                                         PointCloud<PointXYZI> &cloud,
                                         float radius){
    float x_target = 0;
    float y_target = 0;
    float z_target = 0;
    float i_target = 0;
    float distanse_between_points = 0;
    vector <PointXYZI> raduisPoints;
    for(int i=0; i < cloud.points.size();i++){
        distanse_between_points = (cloud.points.at(i).x - x_target)*(cloud.points.at(i).x - x_target)+
                (cloud.points.at(i).y - y_target)*(cloud.points.at(i).y - y_target)+
                (cloud.points.at(i).z - z_target)*(cloud.points.at(i).z - z_target);
        if(radius >= distanse_between_points){
            raduisPoints.push_back(cloud.points.at(i));
        }
    }
    return raduisPoints;
}
