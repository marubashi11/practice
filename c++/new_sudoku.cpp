#include <iostream>
#include <random>
#define SIZE 9
#define HINT 30
#define COORDINATE 100

class Board{
public:
  Board(); //answer_, board_を作成し、cursor_を初期化。
  void out_board(); //盤面を出力。
  void set_number(int, char); //board_に数字をセットする。
  void set_cursor(int); //cursor_を指定の座標に移動させる。
  bool answer_match(); //答え合わせ。
  bool check_num(int, int); //縦、横、ブロック内に同じ数字がないかチェック。
  void make_memo(int); //自動で指定座標のmemoを作成する。
private:
  char answer_[SIZE][SIZE];
  char board_[SIZE][SIZE];
  char cursor_[SIZE][SIZE];
  char memo_[SIZE];
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
    std::cout << " " << n;
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
  std::cout << "auto_memo:: ";
  for(int i = 0; i < 9; i++)
    std::cout << memo_[i];
  std::cout << std::endl;
}
void Board::set_number(int cd, char num){
  int x = cd % SIZE;
  int y = cd / SIZE;
  if(num != '0')
    board_[y][x] = num;
}
void Board::set_cursor(int cd){
  for(int i = 0; i < SIZE; i++)
    for(int j = 0; j < SIZE; j++)
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
bool Board::check_num(int num, int cd){
  int x = cd % SIZE;
  int y = cd / SIZE;
  int x1 = (x / 3) * 3;
  int y1 = (y / 3) * 3;
  bool check[3];

  check[0] = true; //行チェック。
  for(int c = 0; c < SIZE; c++)
    if(board_[y][c] == num + 48) check[0] = false;
  check[1] = true; //列チェック。
  for(int l = 0; l < SIZE; l++)
    if(board_[l][x] == num + 48) check[1] = false;
  check[2] = true; //ブロックチェック。
  for(int bl = 0; bl < 3; bl++)
    for(int bc = 0; bc < 3; bc++)
      if(board_[y1 + bl][x1 + bc] == num + 48) check[2] = false;
  if(check[0] && check[1] && check[2]) return true;
  //すべてのチェックに通過すればtrueを、そうでなければfalseを返す。
  return false;
}
void Board::make_memo(int cd){
  for(int i = 0; i < 9; i++)
    memo_[i] = ' ';
  if(board_[cd / 9][cd % 9] == '.')
    for(int n = 1; n <= 9; n++)
      if(check_num(n, cd)) memo_[n - 1] = n + 48;
}

class GM{
public:
  int ask();
  void congratulate();
};
int GM::ask(){
  int get, cd;
  while(true){
    std::cout << "                     X    Y" << std::endl
              << "数字[1~9]または座標[1~9][1~9]を入力: ";
    std::cin >> get;
    if(get >= 1 && get <= 9)
      return get;
    else if(get >= 11 && get <= 99){
      cd = (get % 10 - 1) * 9 + get / 10 - 1;
      if(cd >= 0 && cd <= 80)
        return cd + COORDINATE; //識別用に100を足して返す。
      std::cout << "[!]無効な入力です。" << std::endl;
    }
    else std::cout << "[!]無効な入力です。" << std::endl;
  }
}
void GM::congratulate(){
  std::cout << "<< Congratulations!! >>"<< std::endl
            << "あなたは隠された数字をすべて当てました。"<< std::endl;
}

int main(){
  int get, cd = 0;
  Board sudoku;
  GM gm;

  sudoku.make_memo(cd);
  while(true){
    sudoku.out_board();
    get = gm.ask();
    switch(get / COORDINATE){
    case 0: //1~9が入力された。
      sudoku.set_number(cd, get + 48);
      sudoku.make_memo(cd);
      if(sudoku.answer_match()){
        sudoku.out_board();
        gm.congratulate();
        return 0;
      }
      break;
    case 1: //11~99(座標)が入力された。
      cd = get - COORDINATE;
      sudoku.set_cursor(cd);
      sudoku.make_memo(cd);
      break;
    }
  }

  return 0;
}
