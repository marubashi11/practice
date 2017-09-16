#include <iostream>
#include <random>
#define SIZE 6

/*

   ----------------------------
  0| 0  1  2| 3  4  5| 6  7  8|
  1| 0  1  2| 3  4  5| 6  7  8|
  2| 0  1  2| 3  4  5| 6  7  8|
   ----------------------------
  3| 0  1  2| 3  4  5| 6  7  8|
  4| 0  1  2| 3  4  5| 6  7  8|
  5| 0  1  2| 3  4  5| 6  7  8|
   ----------------------------
  6| 0  1  2| 3  4  5| 6  7  8|
  7| 0  1  2| 3  4  5| 6  7  8|
  8| 0  1  2| 3  4  5| 6  7  8|
  ----------------------------

*/

class Board{
 public:
  Board(); //numbers_すべてに0を代入。
  void set_numbers(); //条件を満たすように数字を散りばめる。
  void out_numbers(); //盤面を出力。
 private:
  int numbers_[SIZE][SIZE];
};
Board::Board(){
  for(int i = 0; i < SIZE; i++)
    for(int j = 0; j < SIZE; j++)
      numbers_[i][j] = 0;
}
void Board::set_numbers(){
  std::random_device rn;
  std::mt19937 mrn(rn()); //軽量版乱数生成器。
  int num;

  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      while(true){ //numが審査を通るまでループ
        bool check = true;
        num = mrn() % SIZE + 1;
        for(int k = 1; k <= i; k++)
          if(numbers_[i - k][j] == num) check = false;
        for(int l = 1; l <= j; l++)
          if(numbers_[i][j - l] == num) check = false;
        if(check) break;
      }
      numbers_[i][j] = num;
      std::cout << i + 1 << "行" << j + 1 << "列セット完了" << std::endl;
    }
  }
}
void Board::out_numbers(){
  std::cout << std::endl;
  for(int i = 0; i < SIZE * 2 + (SIZE / 3) * 2 + 1; i++)
    std::cout<< "-";
  std::cout << std::endl;
  for(int i = 0; i < SIZE; i++){
    std::cout << "|";
    for(int j = 0; j < SIZE; j++){
      std::cout << " " << numbers_[i][j];
      if(j % 3 == 2) std::cout << " |";
    }
    std::cout << std::endl;
    if(i % 3 == 2){
      for(int i = 0; i < SIZE * 2 + (SIZE / 3) * 2 + 1; i++)
        std::cout<< "-";
      std::cout << std::endl;
    }
  }
}

int main(){
  Board sudoku;
  sudoku.set_numbers();
  sudoku.out_numbers();

  return 0;
}
