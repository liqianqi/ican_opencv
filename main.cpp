#include <iostream>
#include <thread>
#include "icanvision.h"
using namespace std;

int main(){
    IcanVision icanvision;

    //thread thread1(&IcanVision::ImageProducer, ref(icanvision));

    //thread thread2(&IcanVision::ImageConsumer, ref(icanvision));

    //thread thread3(&IcanVision::SerialSendReceive,ref(icanvision));

    //thread1.join();
icanvision.ImageProducer();
   // thread2.join();

    //thread3.join();

    return 0;
}
