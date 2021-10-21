#ifndef DECTOR_H
#define DECTOR_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "measure.h"

using namespace cv;
using namespace std;



class Dector{
public:
    Target getBestTarget(Mat &img,bool &is_find,Point3f &target_location);

    void thresholdImg();

    MeasureDistance measure;
private:

    Mat src_target_;
    Mat dstImage;

public:

    static bool armorCmpdistance(const Target &a, const Target &b){
        return a.area < b.area; //距离近的优先
    }
};


#endif // DECTOR_H
