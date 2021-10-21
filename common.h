#ifndef COMMON_H
#define COMMON_H
#include "opencv2/opencv.hpp"
using namespace cv;
class Target{
public:
    Point2f left_up;
    Point2f left_down;
    Point2f right_up;
    Point2f right_down;
    float area;
    Target(){
        left_up.x = 0;
        left_up.y = 0;
        left_down.x = 0;
        left_down.y = 0;
        right_up.x = 0;
        right_up.y = 0;
        right_down.x = 0;
        right_down.y = 0;
        area = 0;
    }
};
#endif // COMMON_H
