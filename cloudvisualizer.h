#ifndef CLOUDVISUALIZER_H
#define CLOUDVISUALIZER_H
#include <QGLWidget>
#include <QtOpenGL>
#include <GL/glu.h>
#include "pointcloud.h"
#include <iostream>


struct pointCloudData{
    GLfloat* vertexData;
    GLubyte* colorData;
    unsigned int size;
};

enum class ColorScheme {RAINBOW_X,RAINBOW_Y,RAINBOW_Z,RAINBOW_INTENSITY};

using namespace std;

class CloudVisualizer: public QGLWidget
{
    Q_OBJECT
public:
    CloudVisualizer(QWidget *parent = 0);
    void addCoordinateSystem();

    //добавление облака точек
    void addPointCloud(PointCloud<PointXYZ> &cloud);
    void addPointCloud(PointCloud<PointXYZ> &cloud, ColorScheme scheme);
    void addPointCloud(PointCloud<PointXYZI> &cloud, ColorScheme scheme);
    void clear();
public slots:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    //Управление
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);


private:
    //Параметры камеры
    //Позиция
    float cam_pos_x, cam_pos_y, cam_pos_z;
    //Направление
    float cam_dir_x, cam_dir_y, cam_dir_z;
    //Угол проекции на плоскость
    float cam_angle_x, cam_angle_y;
    //растояние до объекта
    float dist;

    //Флаг визуализации системы координат
    bool isCoordinateSystem;

    //Параметры мыши
    QPoint mouse_prev_pose;
    bool isClickedLeft;
    const float mouse_sens = 0.0005f;

    //данные облака точек
    pointCloudData cloudData;



};

#endif // CLOUDVISUALIZER_H
