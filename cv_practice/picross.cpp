#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

class Picross{
public:
  void make_image(); //30*30の二値化画像を作成、bool配列に格納。
  void set_board();
  void make_hint_row(int);
  void make_hint_col(int);
  void out_board();
private:
  bool image_[30][30];
  char board_[30][30];
  int hint_row_[15];
  int hint_col_[15];

  cv::Mat bin_img_;
};

void Picross::make_image(){
  cv::Mat gray_img = cv::imread("/home/marubashi/デスクトップ/mona_liza.JPG", 0);
  cv::resize(gray_img, gray_img, cv::Size(), 30.0/gray_img.cols, 30.0/gray_img.rows, cv::INTER_AREA); //30*30pixelにリサイズ。

  cv::threshold(gray_img, bin_img_, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
  //THRESH_OTSUはなんかいい感じに閾値を决めてくれる。

  for(int i = 0; i < 30; i++)
    for(int j = 0; j < 30; j++)
      if(bin_img_.data[i * bin_img_.step + j * bin_img_.elemSize()] != 0)
        image_[i][j] = true;
  //二値化画像データをtrueとfalseでint型配列image_に格納。
}
void Picross::set_board(){
  for(int i = 0; i < 30; i++)
    for(int j = 0; j < 30; j++)
      board_[i][j] = '.';
  for(int i = 0; i < 30; i++)
    for(int j = 0; j < 30; j++)
      if(image_[i][j])
        board_[i][j] = '#';
}
void Picross::make_hint_row(int row){
  int p = 0;
  int n = 0;

  for(int k = 0; k = 15; k++)
    hint_row_[k] = 0;

  for(int j = 0; j < 30; j++){
    if(image_[row][j])
      p++;
    else if(p != 0){
      hint_row_[n] = p;
      p = 0;
      n++;
    }
  }
}
void Picross::out_board(){
  for(int i = 0; i < 37; i++)
    std::cout << "-";
  std::cout << std::endl;
  for(int i = 0; i < 30; i++){
    make_hint_row(i);
    std::cout << "hint: ";
    for(int n = 0; n < 15; n++)
      std::cout << hint_row_[n] << " ";
    if((i + 1) % 5 == 0)
      std::cout << "[";
    else std::cout << "|";
    for(int j = 0; j < 30; j++){
      std::cout << board_[i][j];
      if((j + 1) % 5 == 0)
        if((i + 1) % 5 == 0)
          std::cout << "[";
        else std::cout << "|";
    }
    for(int i = 0; i < 37; i++)
      std::cout << "-";
    std::cout << std::endl;
  }
}

void img_info(cv::Mat img)
{
  std::cout << "<< 二値化画像 >>" << std::endl
            << "行数: " << img.rows << std::endl
            << "列数: " << img.cols << std::endl
            << "チャンネル数: " << img.channels() << std::endl
            << "要素のサイズ: " << img.elemSize1() << "Byte" << std::endl << std::endl;
}

int main(int argc, char *argv[])
{
  Picross pic;
  //  std::string path;
  /*
  std::cout << "使用したい画像の絶対パスを入力: ";
  std::cin >> path;
  */
  pic.make_image();
  pic.set_board();
  pic.out_board();

  return 0;
}
