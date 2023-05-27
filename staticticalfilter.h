#ifndef STATISTICALFILTER_H
#define STATISTICALFILTER_H
#include "pointcloud.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "cloudvisualizer.h"
using namespace std;

const int POINTS_DIM = 2;

template <typename PointType>
class Node {
public:
    PointType point;

    Node *left;
    Node *right;
    Node(PointType p) {
        point = p;
        left = nullptr;
        right = nullptr;
    }
};



template <class PointType>
class Buffer {
private:
    vector<PointType> buffer_points;
    vector<float> distances;
public:
    Buffer(int size) {
        buffer_points.resize(size);
        distances.resize(size, 1e9);
    }
    bool tryToAdd(PointType target, float distance) {

        bool isAdd = false;
        int i = 0;
        while(i < buffer_points.size() && !isAdd) {
            if(distance < distances.at(i) && distance > 0) {
                //Добавление точки
                for(int j = buffer_points.size() - 1;j > i;j--){
                    buffer_points.at(j) = buffer_points.at(j - 1);
                    distances.at(j) = distances.at(j-1);
                }
                distances.at(i) = distance;
                buffer_points.at(i) = target;
                isAdd = true;
                break;
            }
            i++;
        }
    }
    //    bool tryToAdd(PointType target,PointType point,float bestDist,int n) {
    //        PointType menatel;
    //        PointType menateldop;
    //        for(int i = 0;i < n;i++){
    //            float dist = distance(buffer_points.at(i), target);//------------------------------альфа для тру ту адд
    //            if(dist < bestDist){
    //                menatel = buffer_points.at(i);
    //                buffer_points.at(i) = point;
    //                for(int j = i+1;j<n;j++){
    //                    menateldop = buffer_points.at(j);
    //                    buffer_points.at(j) = menatel;
    //                    menatel = menateldop;

    //                }
    //                bestDist = distance(target,buffer_points.at(n));
    //                break;
    //            }
    //        }
    //    }


    vector<PointType> getPoints() {
        return buffer_points;
    }
    PointType at(unsigned int i) {
        return buffer_points.at(i);
    }
    unsigned int size() {
        return buffer_points.size();
    }
    float tresholddist(){
        return distances.at(size()-1);
    }
};
template <class PointType>
float distance(PointType p1, PointType p2){
    float d = sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2) + pow(p1.z - p2.z,2));
    return  d;

}

template <typename PointType>
class KDtreesearch
{
public:

    //здесь функции для внешнего доступа к функционалу дерева
    //конструктор для построения дерева
    KDtreesearch(PointCloud<PointType> &cloud) {
        root = buildKDtree(cloud.points,0);
    }

    //поиск ближайшего соседа
    Buffer<PointType> nearestNeighbor(PointType target, int n){
        Buffer<PointType> buf(n);

        float distanceBest = 1e9;

        Node<PointType> *best = nullptr;
        search(root,target,best,distanceBest,0,buf);
        return buf;
    }
private:
    //корень дерева
    Node<PointType> *root;
    //рекурсивное  построение дерева
    Node<PointType>* buildKDtree(vector<PointType> &cloud,
                                 int depth) {// глубина)

        //проверка наличия точек
        if(cloud.size() == 0){
            return nullptr;
        }
        if(cloud.size() == 1){
            return new Node<PointType>(cloud.at(0));
        }

        //определяем текущую ось
        int axis = depth % POINTS_DIM;

        //чтобы найти медианное значение, наминужно предварительно
        //отсортировать массив в порядке возрастания
        //для этого используем стандартную функцию из бмбмлеотеки
        //algorithm для сортировки
        sort(cloud.begin(),
             cloud.end(),
             [axis](const PointType &a, const PointType &b) {
            if(axis == 0){
                return a.x < b.x;
            }
            else if(axis == 1) {
                return a.y < b.y;
            }
            else if(axis == 2) {
                return a.z < b.z;
            }


        });
        //находим медиану
        int median = cloud.size() / 2;
        //новый узел будет иметь медианное значение текущего множества
        Node<PointType> *node = new Node<PointType>(cloud.at(median));
        //первую половину множества помещаем в левую часть
        vector<PointType> l_vector(cloud.begin(),
                                   cloud.begin()+median);
        vector<PointType> r_vector(cloud.begin() + median + 1,
                                   cloud.end());
        node->left = buildKDtree(l_vector,
                                 depth + 1);
        node->right = buildKDtree(r_vector,
                                  depth + 1);
        //возврашаем текущий узел
        return node;
    }
    //рекурсивная функция для поиска ближайшего соседа
    void search(Node<PointType> *node,
                PointType target,
                Node<PointType> *&best,
                float &tresholdDist,
                int depth, //текущая глубина
                Buffer<PointType> &currentBuffer) {
        //условие на первый круг чтобы создать
        //проверка на существование текуцщего узла
        if(node == nullptr){
            return;
        }
        //вычисление расстояния от текущего узла до цель точки

        //если текущее расояние лучше чем лучшее
//        if(tresholdDist < distance(target,node->point)){
            currentBuffer.tryToAdd(node->point,distance(target,node->point));
//            tresholdDist = currentBuffer.tresholddist();
//        }
        //вычисляем текущую ось
        int axis = depth % POINTS_DIM;
        //отправляемся на поиск в поддеревья
        if(axis == 0){
            //если целевой х меньше текущего то идем влево
            if(target.x < node->point.x){
                search(node->left,target,best,tresholdDist, depth + 1, currentBuffer);
                //но если разница не большая то сходим и вправво
                if(abs(node->point.x - target.x)<tresholdDist){
                    search(node->right,target,best,tresholdDist, depth + 1, currentBuffer);
                }
            }
            else {
                search(node->left,target,best,tresholdDist, depth + 1, currentBuffer);
                //но если разница не большая то сходим и вправво
                if(abs(node->point.x - target.x)<tresholdDist){
                    search(node->right,target,best,tresholdDist, depth + 1, currentBuffer);
                }
            }
        }
        else if(axis == 1){
            //если целевой х меньше текущего то идем влево
            if(target.y < node->point.y){
                search(node->right,target,best,tresholdDist, depth + 1, currentBuffer);
                //но если разница не большая то сходим и вправво
                if(abs(node->point.y - target.y)<tresholdDist){
                    search(node->left,target,best,tresholdDist, depth + 1, currentBuffer);
                }
            }
            else {
                search(node->right,target,best,tresholdDist, depth + 1, currentBuffer);
                //но если разница не большая то сходим и вправво
                if(abs(node->point.y - target.y)<tresholdDist){
                    search(node->left,target,best,tresholdDist, depth + 1, currentBuffer);
                }
            }
        }
        else if(axis == 2){
            //если целевой х меньше текущего то идем влево
            if(target.z < node->point.z){
                search(node->right,target,best,tresholdDist, depth + 1, currentBuffer);
                //но если разница не большая то сходим и вправво
                if(abs(node->point.z - target.z)<tresholdDist){
                    search(node->left,target,best,tresholdDist, depth + 1, currentBuffer);
                }
            }
            else {
                search(node->right,target,best,tresholdDist, depth + 1, currentBuffer);
                //но если разница не большая то сходим и вправво
                if(abs(node->point.z - target.z)<tresholdDist){
                    search(node->left,target,best,tresholdDist, depth + 1, currentBuffer);
                }
            }
        }
    }


};

template <typename PointType>
class statisticalfilter
{
private:

public:

    statisticalfilter() {

    }

    void filterCloud(PointCloud<PointType> &source,
                     PointCloud<PointType> &dst,
                     float k,
                     int n) {

        KDtreesearch<PointType> searcher(source);
        dst.points.clear();
        for(unsigned int i = 0;i < source.points.size(); i++){
            float procent = i/source.points.size();
            if(procent = (int)procent) {
                cout<<procent<<endl;
            }
            PointType currentPoint = source.points.at(i);
            //            cout<<i<<endl;
            Buffer<PointType> bestPoints = searcher.nearestNeighbor(currentPoint, n);
            float dcred = 0;
            float cymma_dcred = 0;
            float bestdistmass[n];
            for(int j = 0;j < n;j++){
                float dist = distance(bestPoints.at(j), currentPoint);
                cymma_dcred = cymma_dcred + dist;
                bestdistmass[j] = dist;
            }
            dcred = cymma_dcred/n;
            float cigma_cym = 0;
            for(int l = 0;l < n;l++){
                cigma_cym = cigma_cym + pow(bestdistmass[l] - dcred,2);
            }
            float cigma = 0;
            cigma = sqrt(cigma_cym/n);
            float treshold = k*cigma;
            int chet = 0;
            for(int y = 0;y < n;y++){
                if(treshold >= bestdistmass[y]){
                    chet++;

                }
            }
            cout<<"chet: "<<chet<<endl;
            if(chet >= n/2){
                dst.points.push_back(currentPoint);
            }
        }
    }
};

#endif // STATISTICALFILTER_H
