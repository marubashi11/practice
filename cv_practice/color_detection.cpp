#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
  cv::Mat mask;
  cv::Mat img = cv::imread("/home/marubashi/デスクトップ/hitogomi.JPG");
  cv::inRange(img, cv::Scalar(0, 0, 150), cv::Scalar(110, 165, 255), mask);

  imshow("image", img);
  imshow("mask", mask);
  cv::waitKey(0);

  return 0;
}
