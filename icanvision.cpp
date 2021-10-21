#include "icanvision.h"

void IcanVision::ImageProducer(){
    VideoCapture cap;
    cap.open(0);
    Mat image;
    int fd;
    int i = 0;
    for(;;)
    {
        //第一行没有必要加上
        //while(image_buffer_rear_ - image_buffer_front_ > IMGAE_BUFFER);  //若满足这个条件,则让这个函数一只停在这里
        cap >> image;
//imshow("",src);
        if(image.empty())
            break;
        image_buffer_rear_++;
        Mat img;
        //int i = 0;
        Dector dector;
        Target target;

       // MeasureDistance measuredistance;
       // int fd;

        Mat out;
        Point3f point;
        waitKey(1);
        img = image.clone();
        //bilateralFilter(image,img,25,90,90);
        if(img.empty())
           break;

        Mat src = img.clone();
        Size dsize = Size(1280, 960);
        resize(src,src,dsize);

        char sign;
        Point3f target_location;
        bool is_find;
        target = dector.getBestTarget(img,is_find,target_location);
        if(i != 0){
            target_location.x = (point.x + target_location.x)/2;
            target_location.y = (point.y + target_location.y)/2;
            target_location.z = (point.z + target_location.z)/2;
        }
        i++;
        point = target_location;
        // ************fliter***********
            // 开始发送数据
        fd = datacontroler.OpenPort("/dev/ttyUSB0");

        datacontroler.configureSerial(fd);

        serial_state = SerialState::SEND;
        cout << is_find << endl << endl;
        if(is_find == false){
            sign = 0xcc;
        }else{
            sign = 0x0a;
        }

        float angle;
        angle = atan(target_location.x/target_location.z)*(180/CV_PI);

        vision_data.X.f = target_location.x;
        vision_data.Y.f = target_location.y;
        vision_data.Z.f = target_location.z;
        //angle = 0;
        vision_data.angle.f = angle;
        vision_data.sign = sign;
        //cout<<"ddddd"<<vision_data.X.f <<endl<<endl;
        //cout<<"sssss"<<vision_data.Z.f<<endl<<endl;

        datacontroler.sentData(fd,vision_data);

        {
         char test[100];
         sprintf(test, "tz:%0.4f", vision_data.Z.f);
         cv::putText(src, test, cv::Point(10, 40), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

         sprintf(test, "tx:%0.4f", vision_data.X.f);
         cv::putText(src, test, cv::Point(src.cols/3, 80), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

         sprintf(test, "ty:%0.4f", vision_data.Y.f);
         cv::putText(src, test, cv::Point(2*src.cols/3, 120), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

         sprintf(test, "targrt.x:%0.4f", target.left_up.x);
         cv::putText(src, test, cv::Point(2*src.cols/3, 200), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

         sprintf(test, "target.y:%0.4f", target.left_up.y);
         cv::putText(src, test, cv::Point(2*src.cols/3, 280), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

         sprintf(test, "vision_data:%0.4f", vision_data.angle.f);
         cv::putText(src, test, cv::Point(2*src.cols/3, 360), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

         //sprintf(test, "fps:%c", sign);
         //cv::putText(src, test, cv::Point(2*src.cols/3, 420), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

        }
       imshow("Print data",src);



    }
}

//void IcanVision::ImageConsumer(){

//    Mat img;
//    //int i = 0;
//    Dector dector;
//    Target target;
//    double t = 0;
//    double fps;
//   // MeasureDistance measuredistance;
//   // int fd;
//    while(1){
//        // 这一行必须加上
//        while(image_buffer_rear_ <= image_buffer_front_);    //若满足这个条件,则让这个函数一只停在这里

//        image_buffer_front_ = image_buffer_rear_ - 1;

//        img = image_buffer_[image_buffer_front_%IMGAE_BUFFER];

//        Mat out;

//        bilateralFilter(img,out,25,100,100);
//        waitKey(1);

//        if(img.empty())
//           break;

//        Point3f target_location;
//        bool is_find;
//        target = dector.getBestTarget(img,is_find,target_location);



//        //cout << target.left_up.x << "\t" << target.left_up.y << endl;

//        //**************测距****************

//        //**************测距****************

//        //**************滤波处理*************
////        vector<Point3f> location_seq;

////        location_seq.push_back(target_location);

////        target_location = smoothFiter(location_seq);
////        if(i >= 20){
////            i = 0;
////            location_seq.clear();
////        }

//        //**************滤波处理*************

//        // 开始发送数据


//        //cout << "hello wodld" << endl;
//        //fd = datacontroler.OpenPort("/dev/ttyUSB0");

//        //datacontroler.configureSerial(fd);


//        serial_state = SerialState::SEND;

//        float angle;
//        angle = atan(target_location.x/target_location.z)*(180/CV_PI);

//        vision_data.X.f = target_location.x;
//        vision_data.Y.f = target_location.y;
//        vision_data.Z.f = target_location.z;
//        vision_data.angle.f = angle;

//        //datacontroler.sentData(fd,vision_data);

//        Mat src = img.clone();
//        Size dsize = Size(1280, 960);
//        resize(src,src,dsize);

//        t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
//        fps = 1.0 / t;

//        {
//        char test[100];
//        sprintf(test, "tz:%0.4f", target_location.z);
//        cv::putText(src, test, cv::Point(10, 40), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

//        sprintf(test, "tx:%0.4f", target_location.x);
//        cv::putText(src, test, cv::Point(src.cols/3, 80), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

//        sprintf(test, "ty:%0.4f", target_location.y);
//        cv::putText(src, test, cv::Point(2*src.cols/3, 120), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

//        sprintf(test, "targrt.x:%0.4f", target.left_up.x);
//        cv::putText(src, test, cv::Point(2*src.cols/3, 200), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

//        sprintf(test, "target.y:%0.4f", target.left_up.y);
//        cv::putText(src, test, cv::Point(2*src.cols/3, 280), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

//        sprintf(test, "vision_data:%0.4f", vision_data.angle.f);
//        cv::putText(src, test, cv::Point(2*src.cols/3, 360), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);

//        sprintf(test, "fps:%0.4f", fps);
//        cv::putText(src, test, cv::Point(2*src.cols/3, 420), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 5, 8);


//        }
//        imshow("Print data",src);

//    }

//}

//void IcanVision::SerialSendReceive(){

//    int fd;

//    fd = datacontroler.OpenPort("/dev/ttyUSB0");

//    datacontroler.configureSerial(fd);

//    while(true){

//        //发数
//        if(serial_state == SerialState::SEND){
//            //自瞄
//            datacontroler.sentData(fd,vision_data);
//        }
//    }

//}

