#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char *argv[]){
  cv::Mat img = cv::imread("/home/marubashi/デスクトップ/sample/shitting.jpg");
  cv::CascadeClassifier cascade;
  if(!cascade.empty()){
    std::cout << "[!]分類器の読み込みに失敗" << std::endl;
    return -1;
  }
  else if(!cascade.load("/home/marubashi/opencv/opencv/data/haarcascades/haarcascade_frontalface_alt.xml")){
    std::cout << "[!]該当ファイルなし" << std::endl;
    return -1;
  }

  //カスケード分類器で上半身探索。
  cv::vector<cv::Rect> bodies;
  cascade.detectMultiScale(img, bodies, 1.2, 2, CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

  //上半身探索した結果を描画
  cv::vector<cv::Rect>::const_iterator r = bodies.begin();
  for(; r != bodies.end(); ++r){
    cv::rectangle(img, cv::Point(r->x, r->y), cv::Point(r->x + r->width, r->y + r->height), cv::Scalar(0, 0, 200), 3, CV_AA);
  }

  cv::imshow("検出結果", img);
  cv::waitKey(0);

  return 0;
}
