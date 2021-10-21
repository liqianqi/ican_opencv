#include "dector.h"

int h_min=53;
int s_min=141;
int v_min=103;

int h_max=78;
int s_max=255;
int v_max=255;
Target Dector::getBestTarget(Mat &img,bool &is_find,Point3f &target_location){
    src_target_ = img.clone();
    Mat src = img.clone();
    Size dsize = Size(1280, 1280);
    resize(src,src,dsize);
    thresholdImg();

    vector<vector<Point>>contours;
    findContours(dstImage,contours,RETR_EXTERNAL,CHAIN_APPROX_NONE);
    vector<Rect>rect(contours.size());
    float width[contours.size()];
    float height[contours.size()];
    Target armor_array_[contours.size()];
    Target zero;
    zero.left_up.x = 0;
    zero.left_up.y = 0;
    zero.right_down.x = 0;
    zero.right_down.y = 0;
    if(contours.size() == 0){
        is_find = false;
        return zero;
    }

    for(unsigned long i = 0;i < contours.size();i++)
    {

        rect[i] = boundingRect(contours[i]);
        float area = contourArea(contours[i]);
//cout<<"area"<<area<<endl<<endl;
        int x = rect[i].x;
        int y = rect[i].y;
        width[i] = rect[i].width;
        height[i] = rect[i].height;

        rectangle(src,Point(x,y),Point(x+width[i],y+height[i]),Scalar(255,0,0),2);

        Target armor;
        armor.left_up.x = rect[i].x;
        armor.left_up.y = rect[i].y;

        armor.right_up.x = rect[i].x+width[0];
        armor.right_up.y = rect[i].y;

        armor.right_down.x = rect[i].x+width[0];
        armor.right_down.y = rect[i].y+height[0];

        armor.left_down.x = rect[i].x;
        armor.left_down.y = rect[i].y+height[0];

        armor.area = area;
//cout<<"ddddd"<<armor.right_up.x - armor.left_down.x<<endl<<endl;
//cout<<"sssss"<<armor.left_down.y - armor.left_up.y<<endl<<endl;
        armor_array_[i] = armor;

    }

    sort(armor_array_,armor_array_+contours.size(),armorCmpdistance);
    imshow("vision_data",src);

    measure.getPoint2D(armor_array_[0]);
    //measure.getPoint3D();
    target_location = measure.pnpResolving();
    return armor_array_[0];

}

void Dector::thresholdImg(){
    // 开灯的参数

    // 较暗的时候
    // int h_min=60;
    // int s_min=70;
    // int v_min=80;

    // int h_max=78;
    // int s_max=200;
    // int v_max=170;

    namedWindow("DaHengCameraDebug", CV_WINDOW_AUTOSIZE);
    createTrackbar("h_min", "DaHengCameraDebug", &h_min,180);

    namedWindow("DaHengCameraDebug", CV_WINDOW_AUTOSIZE);
    createTrackbar("s_min", "DaHengCameraDebug", &s_min,255);

    namedWindow("DaHengCameraDebug", CV_WINDOW_AUTOSIZE);
    createTrackbar("v_min", "DaHengCameraDebug", &v_min,255);

    namedWindow("DaHengCameraDebug", CV_WINDOW_AUTOSIZE);
    createTrackbar("h_max", "DaHengCameraDebug", &h_max,180);

    namedWindow("DaHengCameraDebug", CV_WINDOW_AUTOSIZE);
    createTrackbar("s_max", "DaHengCameraDebug", &s_max,255);

    namedWindow("DaHengCameraDebug", CV_WINDOW_AUTOSIZE);
    createTrackbar("v_max", "DaHengCameraDebug", &v_max,255);

    Size dsize = Size(1280, 1280);
    resize(src_target_,src_target_,dsize);
    //imshow("src",srcImage);
    Mat tempImage = src_target_.clone();
    cvtColor(src_target_,src_target_,CV_BGR2HSV);
    Scalar hsv_min(h_min,s_min,v_min);
    Scalar hsv_max(h_max,s_max,v_max);
    dstImage = Mat::zeros(src_target_.size(),CV_8U);
    inRange(src_target_,hsv_min,hsv_max,dstImage);
    Mat element = getStructuringElement(MORPH_RECT,Size(6,6));

    erode(dstImage, dstImage, element);
    Mat elem = getStructuringElement(MORPH_RECT,Size(7,5));
    morphologyEx(dstImage,dstImage,MORPH_ERODE,elem,Point(-1,-1),1);
    morphologyEx(dstImage,dstImage,MORPH_DILATE,elem,Point(-1,-1),4);


    //dilate(dstImage, dstImage, elem);
    imshow("dst",dstImage);
}
