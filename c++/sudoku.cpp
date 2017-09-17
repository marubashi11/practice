#include <iostream>
#include <random>
#define SIZE 9 //盤面の大きさ。3の倍数推奨。
#define SET 50 //始めにランダムでセットする数字の個数。
/*
   x 0 1 2   3 4 5   6 7 8
 y -------------------------
  0| ?     |       |       |
  1|   0   |   1?  |   2   |
  2|       |       |     ? |
   -------------------------
  3|       |       | ?     |
  4|   3?  |   4   |   5   |
  5|       |     ? |       |
   -------------------------
  6|       | ?     |       |
  7|   6   |   7   |   8?  |
  8|     ? |       |       |
   -------------------------
*'?'の位置にまずランダムに数字を配置し、それをcomが解くように数字を埋めていく。
board[y][x]が属するブロックの左上の座標(x1,y1)は、
    x1 = (x / 3) * 3, y1 = (y / 3) * 3
で求まる。
ブロック番号bは、
    b = (y / 3) * 3 + x / 3
で求まる。
*/

class Board{
 public:
  Board(); //board_すべてに0を代入し、適当にいくつかの数字配置。
  bool check_line(int, int);
  bool check_column(int, int);
  bool check_block(int, int, int);
  bool check(int, int, int); //上記3つのチェックを行う。
  void set_numbers(); //条件を満たすように数字を散りばめる。
  bool check_q(); //問題として成立しているか確認。
  void out_board(); //盤面を出力。
 private:
  int board_[SIZE][SIZE];
};
Board::Board(){
  for(int i = 0; i < SIZE; i++)
    for(int j = 0; j < SIZE; j++)
      board_[i][j] = 0;
}
bool Board::check_line(int num, int y){
  for(int i = 0; i < SIZE; i++)
    if(board_[y][i] == num) return false;
  return true;
}
bool Board::check_column(int num, int x){
  for(int i = 0; i < SIZE; i++)
    if(board_[i][x] == num) return false;
  return true;
}
bool Board::check_block(int num, int x, int y){
  int x1 = (x / 3) * 3;
  int y1 = (y / 3) * 3;
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      if(board_[y1 + i][x1 + j] == num) return false;
  return true;
}
bool Board::check(int num, int x, int y){
  return check_line(num, y) && check_column(num, x) && check_block(num, x, y);
}
void Board::set_numbers(){
  std::random_device rnd;
  int num, X, Y;
  for(int s = 0; s < SET; s++){ //ランダムでSET個の数字セット。
    X = rnd() % 9;
    Y = rnd() % 9;
    num = rnd() % 9 + 1;
    if(board_[Y][X] == 0 && check(num, X, Y)) board_[Y][X] = num;
    else s--;
  }
  std::cout << "初期配置完了!" << std::endl;

  for(int i = 0; i < 9; i++) //数独を解きながら数字セット。
    for(int j = 0; j < 9; j++)
      if(board_[i][j] == 0)
        for(int n = 1; n <= 9; n++){
          if(check(n, j, i)){
            board_[i][j] = n;
            break;
          }
        }
}
bool Board::check_q(){
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      if(board_[i][j] == 0){
        std::cout << "作成失敗" << std::endl;
        return false;
      }
  return true;
}
void Board::out_board(){
  std::cout << std::endl;
  for(int i = 0; i < SIZE * 2 + (SIZE / 3) * 2 + 1; i++)
    std::cout<< "-";
  std::cout << std::endl;
  for(int i = 0; i < SIZE; i++){
    std::cout << "|";
    for(int j = 0; j < SIZE; j++){
      std::cout << " " << board_[i][j];
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
  while(true){
    sudoku.set_numbers();
    sudoku.out_board();
    if(sudoku.check_q()) break;
  }
  sudoku.out_board();
  return 0;
}
