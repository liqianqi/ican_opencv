#ifndef SERIAL_H
#define SERIAL_H

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <sys/ioctl.h>

using namespace std;
//传输数据用的类型三
typedef union{
    float f;
    unsigned char c[4];
}float2uchar;
class DataControler{
public:

    // 视觉向电控传数据
    struct VisionData{
        float2uchar X;
        float2uchar Y;
        float2uchar Z;
        float2uchar angle;
        char sign;
        VisionData(){
            X.f = 0;
            Y.f = 0;
            Z.f = 0;
            angle.f = 0;
        }
    };

public:
    void sentData(int fd,char sign);
    void sentData(int fd,VisionData &data);
    int OpenPort(const char *Portname);
    int configureSerial(int fd);
};

#endif // SERIAL_H
