#include "measure.h"

void MeasureDistance::getPoint2D(Target &target){
    point2D.push_back(target.left_up);
    point2D.push_back(target.right_up);
    point2D.push_back(target.right_down);
    point2D.push_back(target.left_down);
}

void MeasureDistance::getPoint3D(){

    float fHalfX;
    float fHalfY;

    const float kRealSmallArmorHeight = 8.0f;
    const float kRealLargeArmorWidth = 9.5f;

    fHalfX = kRealLargeArmorWidth * 0.5f;
    fHalfY = kRealSmallArmorHeight * 0.5f;

    point3D.push_back(cv::Point3f(-fHalfX,fHalfY, 0.0f));
    point3D.push_back(cv::Point3f(fHalfX,fHalfY, 0.0f));
    point3D.push_back(cv::Point3f(fHalfX,-fHalfY, 0.0f));
    point3D.push_back(cv::Point3f(-fHalfX,-fHalfY, 0.0f));
}

Point3f MeasureDistance::pnpResolving(){

    getPoint3D();
    float tx;
    float ty;
    float tz;
    cv::Mat rvecs = cv::Mat::zeros(3,1,CV_64FC1);
    cv::Mat tvecs = cv::Mat::zeros(3,1,CV_64FC1);
//cout<<"ssstz"<<tz<<endl;
    cv::solvePnP(point3D, point2D, caremaMatrix, distCoeffs, rvecs, tvecs);   //解算x,y,z 三轴偏移量

    tx = tvecs.ptr<double>(0)[0];
    ty = -tvecs.ptr<double>(0)[1];
    tz = tvecs.ptr<double>(0)[2];
//cout<<"ddddddtz"<<tz<<endl;
    Point3f point;
    point.x = tx;
    point.y = ty;
    point.z = tz;

    return point;

}
