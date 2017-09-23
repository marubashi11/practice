#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp> //情報開示用
#include <opencv2/highgui/highgui.hpp>

#define LOW_H 18 / 2 //Hは0~179(0~360を2で割った値)?
#define LOW_S 0.5 * 255 //Sは0~255(0~1に255掛けた値)
#define LOW_V 0 * 255 //VもSに同じ
#define UP_H 35 / 2
#define UP_S 1 * 255
#define UP_V 1 * 255

int main(int argc, char *argv[])
{
  cv::Mat mask_img;
  cv::Mat hsv_img;
  cv::Mat bgr_img = cv::imread("/home/marubashi/デスクトップ/fruits.jpg");

  cv::cvtColor(bgr_img, hsv_img, CV_BGR2HSV);
  cv::inRange(hsv_img, cv::Scalar(LOW_H, LOW_S, LOW_V), cv::Scalar(UP_H, UP_S, UP_V), mask_img);
  /*
  for(int i = 0; i < hsv_img.rows; i = i + 50){ //50pごとに白点
    for(int j = 0; j < hsv_img.cols; j = j + 50){
      hsv_img.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 255, 255);
    }
  }
  */

  std::cout << "<< 元画像 >>" << std::endl;
  std::cout << "行数: " << bgr_img.rows << std::endl;
  std::cout << "列数: " << bgr_img.cols << std::endl;
  std::cout << "次元: " << bgr_img.dims << std::endl;
  std::cout << "チャンネル数: " << bgr_img.channels() << std::endl;
  std::cout << "要素のサイズ: " << bgr_img.elemSize() << " Byte" << std::endl << std::endl;

  std::cout << "<< HSV画像 >>" << std::endl;
  std::cout << "行数: " << hsv_img.rows << std::endl;
  std::cout << "列数: " << hsv_img.cols << std::endl;
  std::cout << "次元: " << hsv_img.dims << std::endl;
  std::cout << "チャンネル数: " << hsv_img.channels() << std::endl;
  std::cout << "要素のサイズ: " << hsv_img.elemSize() << " Byte" << std::endl << std::endl;

  std::cout << "<< マスク画像 >>" << std::endl;
  std::cout << "行数: " << mask_img.rows << std::endl;
  std::cout << "列数: " << mask_img.cols << std::endl;
  std::cout << "次元: " << mask_img.dims << std::endl;
  std::cout << "チャンネル数: " << mask_img.channels() << std::endl;
  std::cout << "要素のサイズ: " << mask_img.elemSize() << " Byte" << std::endl;

  imshow("元画像", bgr_img);
  imshow("HSV画像", hsv_img);
  imshow("マスク画像", mask_img);
  cv::waitKey(0);

  /*
  int h, s, v, x, y;
  while(true){
    std::cout << "知りたいピクセルの座標を入力:" << std::endl
              << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;
    cv::Vec3b p = hsv_img.at<cv::Vec3b>(y, x);
    h = p(0);
    s = p(1);
    v = p(2);
    std::cout << "H: " << h << std::endl
              << "S: " << s << std::endl
              << "V: " << v << std::endl;
  }
  */

  return 0;
}
