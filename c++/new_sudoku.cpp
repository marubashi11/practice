#include <iostream>
#include <random>
#define SIZE 9
#define HINT 30

class Board{
public:
  Board(); //cursor_, answer_, board_を作成。
  void out_board();
  void set_number(int, char);
  void set_cursor(int);
  bool answer_match();
private:
  char answer_[9][9];
  char board_[9][9];
  char cursor_[9][9];
};
Board::Board(){
  int r, x, y;
  char buff;
  std::random_device rnd;
  char sample_1[81] = { '1', '4', '7', '2', '5', '8', '3', '6', '9', '2', '5', '8', '3', '6', '9', '4', '7', '1', '3', '6', '9', '4', '7', '1', '5', '8', '2', '4', '7', '1', '5', '8', '2', '6', '9', '3', '5', '8', '2', '6', '9', '3', '7', '1', '4', '6', '9', '3', '7', '1', '4', '8', '2', '5', '7', '1', '4', '8', '2', '5', '9', '3', '6', '8', '2', '5', '9', '3', '6', '1', '4', '7', '9', '3', '6', '1', '4', '7', '2', '5', '8' };
  char sample_2[81] = { '8', '9', '7', '6', '3', '5', '4', '1', '2', '1', '6', '3', '2', '4', '7', '5', '8', '9', '2', '4', '5', '8', '1', '9', '6', '3', '7', '7', '8', '6', '9', '5', '3', '2', '4', '1', '3', '5', '4', '1', '8', '2', '9', '7', '6', '9', '1', '2', '7', '6', '4', '8', '5', '3', '5', '2', '8', '3', '7', '6', '1', '9', '4', '6', '7', '1', '4', '9', '8', '3', '2', '5', '4', '3', '9', '5', '2', '1', '7', '6', '8' };

  switch(rnd() % 2){
  case 0:
    for(int k = 0; k < 81; k++){
      int I = k / 9;
      int J = k % 9;
      answer_[I][J] = sample_1[k];
    }
    break;
  case 1:
    for(int k = 0; k < 81; k++){
      int I = k / 9;
      int J = k % 9;
      answer_[I][J] = sample_2[k];
    }
    break;
  }
  for(int sh = 0; sh < 50; sh++){
    x = (rnd() % 3) * 3;
    r = rnd() % 2 + 1;
    for(int l = 0; l < 9; l++){ //列入れ替え。
      buff = answer_[l][x];
      answer_[l][x] = answer_[l][x + r];
      answer_[l][x + r] = buff;
    }
    y = (rnd() % 3) * 3;
    r = rnd() % 2 + 1;
    for(int c = 0; c < 9; c++){ //行入れ替え。
      buff = answer_[y][c];
      answer_[y][c] = answer_[y + r][c];
      answer_[y + r][c] = buff;
    }
    r = (rnd() % 2 + 1) * 3;
    for(x = 0; x < 3; x++) //3列入れ替え。
      for(int l = 0; l < 9; l++){
        buff = answer_[l][x];
        answer_[l][x] = answer_[l][x + r];
        answer_[l][x + r] = buff;
      }
    r = (rnd() % 2 + 1) * 3;
    for(y = 0; y < 3; y++) //3行入れ替え。
      for(int c = 0; c < 9; c++){
        buff = answer_[y][c];
        answer_[y][c] = answer_[y + r][c];
        answer_[y + r][c] = buff;
      }
  }

  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      board_[i][j] = '.';
  for(int hi = 0; hi < HINT; hi++){
    int rm = rnd() % 81;
    if(board_[rm / 9][rm % 9] == '.')
      board_[rm / 9][rm % 9] = answer_[rm / 9][rm % 9];
    else hi--;
  }
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      cursor_[i][j] = ' ';
  cursor_[0][0] = '>';
}
void Board::out_board(){
  std::cout << "  ";
  for(int n = 1; n <= 9; n++){
    char c_num = n + 96;
    std::cout << " " << c_num;
    if(n % 3 == 0)
      std::cout << "  ";
  }
  std::cout << std::endl
            << " ";
  for(int i = 0; i < SIZE * 2 + (SIZE / 3) * 2 + 1; i++)
    std::cout << "-";
  std::cout << std::endl;
  for(int i = 0; i < SIZE; i++){
    std::cout << i + 1 << "|";
    for(int j = 0; j < SIZE; j++){
      std::cout << cursor_[i][j] << board_[i][j];
      if(j % 3 == 2) std::cout << " |";
    }
    std::cout << std::endl;
    if(i % 3 == 2){
      std::cout << " ";
      for(int i = 0; i < SIZE * 2 + (SIZE / 3) * 2 + 1; i++)
        std::cout << "-";
      std::cout << std::endl;
    }
  }
}
void Board::set_number(int cd, char num){
  int x = cd % 9;
  int y = cd / 9;
  board_[y][x] = num;
}
void Board::set_cursor(int cd){
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      cursor_[i][j] = ' ';
  cursor_[cd / SIZE][cd % SIZE] = '>';
}
bool Board::answer_match(){
    for(int i = 0; i < 9; i++)
      for(int j = 0; j < 9; j++)
        if(board_[i][j] != answer_[i][j])
          return false;
    return true;
}

class GM{
public:
  int ask_cd();
  char ask_num();
  void congratulate();
};
int GM::ask_cd(){
  char x, y;
  int cd;
  while(true){
  std::cout << "座標を指定してください[x][y]:";
  std::cin >> x;
  std::cin >> y;
  cd = ((y - 1) - 48) * 9 + ((x - 1) - 96);
  std::cout << "変換完了:" << cd << std::endl; //後で消す。
  if(cd >= 0 && cd <= 80) return cd;
  std::cout << "[!]無効な入力" << std::endl;
  }
}
char GM::ask_num(){
  int get;
  char num;
  while(true){
    std::cout << "数字を入力してください[1~9]:";
    std::cin >> get;
    if(get >= 1 && get <= 9){
      num = get + 48;
      return num;
    }
    std::cout << "[!]無効な入力" << std::endl;
  }
}
void GM::congratulate(){
  std::cout << "<< Congratulations!! >>"<< std::endl
            << "あなたはすべての数字を当てました。"<< std::endl;
}

int main(){
  int cd;
  Board sudoku;
  GM gm;

  while(true){
    sudoku.out_board();
    cd = gm.ask_cd();
    sudoku.set_cursor(cd);
    sudoku.out_board();
    sudoku.set_number(cd, gm.ask_num());
    if(sudoku.answer_match()){
      sudoku.out_board();
      gm.congratulate();
      break;
    }
  }

  return 0;
}
