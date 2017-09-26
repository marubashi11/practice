#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(){
  int low_b = 0, low_g = 0, low_r = 0, up_b = 50, up_g = 50, up_r = 255;
  cv::Mat image = cv::imread("/home/marubashi/デスクトップ/sample/France.png");
  cv::Mat mask;

  cv::namedWindow("track", 1); //指定したwindowの名前が同じものは同じwindow内に表示される模様。
  cv::createTrackbar("low_B","track", &low_b, 255);
  cv::createTrackbar("low_G","track", &low_g, 255);
  cv::createTrackbar("low_R","track", &low_r, 255);
  cv::createTrackbar("up_B","track", &up_b, 255);
  cv::createTrackbar("up_G","track", &up_g, 255);
  cv::createTrackbar("up_R","track", &up_r, 255);

  while(true){
    cv::inRange(image, cv::Scalar(low_b, low_g, low_r), cv::Scalar(up_b, up_g, up_r), mask);
    cv::imshow("マスク画像", mask);
    int key = cv::waitKey(50); //waitKey(0)だと失敗した。
    if(key > 0) break;
  }

  return 0;
}
