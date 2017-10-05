#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main(){
  cv::Mat gray_img = cv::imread("/home/marubashi/デスクトップ/sample/shitting.jpg", 0);
  cv::Mat clone_img = gray_img.clone();
  cv::vector<cv::vector<cv::Point> > contours; //輪郭点を行列に格納。

  cv::findContours(clone_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

  double max_size = 0;
  int max_id = -1;

  for(int i = 0; i < contours.size(); i++)
    if(contours[i].size() > max_size){
      max_size = contours[i].size();
      max_id = i;
    }

  cv::Moments mu = cv::moments(contours[max_id]);
  cv::Point2f mc = cv::Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);

  cv::circle(gray_img, mc, 4, cv::Scalar(100), 2, 4);

  std::cout << "x: " << mc.x << "  y: " << mc.y << std::endl;

  cv::imshow("image", gray_img);
  cv::waitKey(0);

  return 0;
}
