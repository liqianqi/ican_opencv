#ifndef ICANVISION_H
#define ICANVISION_H
#define AVERAGE_N 15

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <mutex>
#include "serial.h"
#include "dector.h"
#define N 10
using namespace cv;
using namespace std;
using namespace Eigen;

enum BufferSize{
    IMGAE_BUFFER = 5
};
enum class SerialState
{
    SEND,
    RECEIVE,
    WAIT
};

class IcanVision{
public:
    IcanVision():
    serial_state(SerialState::SEND)
    {}

    void ImageProducer();
    void ImageConsumer();
    void SerialSendReceive();

    Point3f smoothFiter(Point3f num[N]){
        float numberx = 0;
        float numbery = 0;
        float numberz = 0;
        for(int i = 0;i < N; i++){
            numberx = numberx + num[i].x;
        }
        numberx = numberx/N;

        for(int i = 0;i < N; i++){
            numbery = numbery + num[i].y;
        }
        numberz = numberz/N;

        for(int i = 0;i < N; i++){
            numberz = numberz + num[i].z;
        }
        numberz = numberz/N;
        Point3f point;
        point.x = numberx;
        point.y = numbery;
        point.z = numberz;
        return point;
    }

public:

    Mat image_buffer_[IMGAE_BUFFER];
    volatile unsigned int image_buffer_front_ = 0;
    volatile unsigned int image_buffer_rear_ = 0;

    DataControler datacontroler;

    DataControler::VisionData vision_data;

    SerialState serial_state;
};

#endif //
