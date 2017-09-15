#include <iostream>

/*
     a  b  c  d  e  f  g  h  i
   ----------------------------
  1| 0  1  2  3  4  5  6  7  8|
  2| 9 10 11 12 13 14 15 16 17|
  3|18 19 20 21 22 23 24 25 26|
  4|27 28 29 30 31 32 33 34 35|
  5|36 37 38 39 40 41 42 43 44|
  6|45 46 47 48 49 50 51 52 53|
  7|54 55 56 57 58 59 60 61 62|
  8|63 64 65 66 67 68 69 70 71|
  9|72 73 74 75 76 77 78 79 80|
   ----------------------------
  9で割った商で何行目かわかり、9で割った余りで何列目かわかる。
*/

class Board{
public:
  Board(); //すべてのcellを空白に。
  void out_board(); //boardを表示。
  void set_board(int, int); //b_state_[引数1] = 'x'か'o';
  int report(int); //指定cellについて 空:0, x:1, o:2 を返す。
  bool judge(int); //勝利判定。falseなら続行。
private:
  char b_state_[81];
};
Board::Board(){
  for(int i = 0; i < 81; i++) b_state_[i] = ' ';
}
void Board::out_board(){
  char c_num;
  std::cout << std::endl << " ";
  for(int i = 1; i <= 9; i++){
    c_num = i + 96;
    std::cout << " " << c_num;
  }
  std::cout << std::endl << " -------------------" << std::endl;
  for(int i = 0; i < 9; i++){
    std::cout << i + 1 << "|";
    for(int j = 0; j < 9; j++){
      std::cout << b_state_[i * 9 + j] << "|";
    }
    std::cout << std::endl;
  }
  std::cout << " -------------------" << std::endl;

}
void Board::set_board(int n, int p){
  switch(p){
  case 1:
    b_state_[n] = 'x';
    break;
  case 2:
    b_state_[n] = 'o';
    break;
  }
}
int Board::report(int cell){
  switch(b_state_[cell]){
  case ' ':
    return 0;
  case 'x':
    return 1;
  case 'o':
    return 2;
  }
}
bool Board::judge(int p){
  int r = 0, d = 0, rd = 0, ld = 0;
  char mark;
  switch(p){
  case 1:
    mark = 'x';
    break;
  case 2:
    mark = 'o';
    break;
  }
  for(int i = 0; i < 81; i++){
    if((i / 9 <= 4 && i % 9 <= 4) && b_state_[i] == mark){
      for(int look = 1; look <= 4; look++){ //3方向チェック。
        if(b_state_[i + look] == mark) r++;
        if(b_state_[i + look * 9] == mark) d++;
        if(b_state_[(i + look * 9) + look] == mark) rd++;
      }
      std::cout << "r:" << r << " d:" << d << " rd:" << rd << std::endl;
      if(r == 4 || d == 4 || rd == 4) return true;
      r = 0; d = 0; rd = 0;
    }
    if((i / 9 <= 4 && i % 9 >= 4) && b_state_[i] == mark){
      for(int look = 1; look <= 4; look++) //左斜めチェック。
        if(b_state_[(i + look * 9) - look] == mark) ld++;
      std::cout << "ld:" << ld << std::endl;
      if(ld == 4) return true;
      ld = 0;
    }
  }
  return false;
}

class GM{
public:
  int ask_cell(int);
};
int GM::ask_cell(int p){
  char get_i;
  char get_j;
  int cell;
  while(true){
    switch(p){
    case 1:
      std::cout << "1P[x]の手を入力: ";
      break;
    case 2:
      std::cout << "2P[o]の手を入力: ";
      break;
    }
    std::cin >> get_i;
    std::cin >> get_j;
    cell = ((get_i - 48) - 1) * 9 + ((get_j - 96) - 1);
    if(cell >= 0 && cell <= 80) return cell;
    std::cout << "[!]無効な入力です。" << std::endl;
  }
}

int change_turn(int p){ //手番の入れ替え。
  switch(p){
  case 1:
    return 2;
  case 2:
    return 1;
  }
}

//////////////////// ここからメイン ////////////////////
int main(){
  int player = 1; //手番。
  int get; //playerの手を一時保存。
  int count = 0; //何手か数える。
  Board board;
  GM master;

  board.out_board();
  while(true){
    get = master.ask_cell(player);
    switch(board.report(get)){ //置き石がないかチェック。
    case 0:
      count++;
      board.set_board(get, player);
      board.out_board();
      if(board.judge(player)){ //勝負あり。
        std::cout << count << "手で" << player << "Pの勝ち!!" << std::endl;
        return false;
      }
      player = change_turn(player);
      break;
    default:
      std::cout << "[!]そこには置けません。" << std::endl;
      break;
    }
  }

  return 0;
}
