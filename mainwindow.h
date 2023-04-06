#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <fstream>
#include "cloudvisualizer.h"
#include "cloudtransformation.h"
#include "voxelcloudfilter.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_cloud_clicked();

    void on_pushButton_open_file_clicked();

    void on_pushButton_clear_clicked();

    void on_doubleSpinBox_t_y_valueChanged(double arg1);

    void on_doubleSpinBox_t_z_valueChanged(double arg1);


    void on_doubleSpinBox_t_x_valueChanged(double arg1);

    void on_doubleSpinBox_r_z_valueChanged(double arg1);

    void on_doubleSpinBox_r_x_valueChanged(double arg1);

    void on_doubleSpinBox_r_y_valueChanged(double arg1);

    void on_pushButton_filterCloud_clicked();

private:
    Ui::MainWindow *ui;

    CloudVisualizer visualizer;
    CloudTransformation Tr;
    PointCloud<PointXYZ> currentPointCloud;
    PointCloud<PointXYZI> currentPointCloud_intensity;
    QString current_status;
    //параметры трансформации
    float tx,ty,tz,rx,ry,rz;
};

#endif // MAINWINDOW_H
