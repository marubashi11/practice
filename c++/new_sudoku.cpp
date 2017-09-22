#include <iostream>
#include <string>
#include <random>

#define SIZE 9
#define IDENTIFY 100
#define MEMO 61
#define SAVE 67
#define LOAD 60

class Board{
public:
  Board(int); //board_, save_を作成、cursor_を初期化。
  void make_answer(); //answer_を作成。
  void out_board(bool); //盤面を出力。
  void set_number(int, char); //board_に数字をセットする。
  void set_cursor(int); //cursor_を指定の座標に移動させる。
  bool answer_match(); //答え合わせ。
  bool check_num(int, int); //縦、横、ブロック内に同じ数字がないかチェック。
  void make_memo(int); //自動で指定座標のmemoを作成する。
  void save_board(); //盤面の一時保存。
  void load_board(); //一時保存した盤面のロード。
private:
  char answer_[SIZE][SIZE];
  char board_[SIZE][SIZE];
  char constant_[SIZE][SIZE]; //最初の数字を変更不可にするため。
  char save_[SIZE][SIZE];
  char cursor_[SIZE][SIZE];
  char memo_[SIZE];
};

Board::Board(int hint){
  std::random_device rnd;
  int rm;

  make_answer();
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      board_[i][j] = '.';
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      constant_[i][j] = '\0';
  for(int h = 0; h < hint; h++){
    rm = rnd() % 81;
    if(board_[rm / 9][rm % 9] == '.'){
      board_[rm / 9][rm % 9] = answer_[rm / 9][rm % 9];
      constant_[rm / 9][rm % 9] = answer_[rm / 9][rm % 9];
    }
    else h--;
  }
  save_board();
  set_cursor(0);
}
void Board::make_answer(){
  int r, x, y;
  char buff;
  std::random_device rnd;
  char sample_1[81] = { '1', '4', '7', '2', '5', '8', '3', '6', '9', '2', '5', '8', '3', '6', '9', '4', '7', '1', '3', '6', '9', '4', '7', '1', '5', '8', '2', '4', '7', '1', '5', '8', '2', '6', '9', '3', '5', '8', '2', '6', '9', '3', '7', '1', '4', '6', '9', '3', '7', '1', '4', '8', '2', '5', '7', '1', '4', '8', '2', '5', '9', '3', '6', '8', '2', '5', '9', '3', '6', '1', '4', '7', '9', '3', '6', '1', '4', '7', '2', '5', '8' };
  char sample_2[81] = { '8', '9', '7', '6', '3', '5', '4', '1', '2', '1', '6', '3', '2', '4', '7', '5', '8', '9', '2', '4', '5', '8', '1', '9', '6', '3', '7', '7', '8', '6', '9', '5', '3', '2', '4', '1', '3', '5', '4', '1', '8', '2', '9', '7', '6', '9', '1', '2', '7', '6', '4', '8', '5', '3', '5', '2', '8', '3', '7', '6', '1', '9', '4', '6', '7', '1', '4', '9', '8', '3', '2', '5', '4', '3', '9', '5', '2', '1', '7', '6', '8' };
  char sample_3[81] = { '7', '4', '5', '9', '8', '3', '6', '2', '1', '9', '8', '1', '2', '5', '6', '3', '4', '7', '2', '6', '3', '1', '4', '7', '5', '9', '8', '1', '2', '6', '5', '7', '4', '9', '8', '3', '4', '5', '7', '3', '9', '8', '1', '6', '2', '8', '3', '9', '6', '2', '1', '7', '5', '4', '5', '7', '2', '8', '3', '9', '4', '1', '6', '3', '1', '8', '4', '6', '5', '2', '7', '9', '6', '9', '4', '7', '1', '2', '8', '3', '5' };
  int s_num = rnd() % 3;

  for(int k = 0; k < 81; k++){
    int I = k / 9;
    int J = k % 9;
    switch(s_num){
    case 0:
      answer_[I][J] = sample_1[k];
      break;
    case 1:
      answer_[I][J] = sample_2[k];
      break;
    case 2:
      answer_[I][J] = sample_3[k];
    }
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

}
void Board::out_board(bool m){
  std::cout << std::endl << "  X";
  for(int n = 1; n <= 9; n++){
    std::cout << " " << n;
    if(n % 3 == 0)
      std::cout << "  ";
  }
  std::cout << std::endl
            << "Y ";
  for(int i = 0; i < SIZE * 2 + (SIZE / 3) * 2 + 1; i++)
    std::cout << "-";
  std::cout << std::endl;
  for(int i = 0; i < SIZE; i++){
    std::cout<< " " << i + 1 << "|";
    for(int j = 0; j < SIZE; j++){
      std::cout << cursor_[i][j] << board_[i][j];
      if(j % 3 == 2) std::cout << " |";
    }
    if(i == 6)
      std::cout << "   [m]自動メモの表示切替え";
    if(i == 7)
      std::cout << "   [s]盤面の一時保存";
    if(i == 8)
      std::cout << "   [l]一時保存した盤面の読み込み";
    std::cout << std::endl;
    if(i % 3 == 2){
      std::cout << "  ";
      for(int i = 0; i < SIZE * 2 + (SIZE / 3) * 2 + 1; i++)
        std::cout << "-";
      std::cout << std::endl;
    }
  }
  if(m){
    std::cout << "auto_memo:: ";
    for(int i = 0; i < 9; i++)
      std::cout << memo_[i];
    std::cout << std::endl;
  }
}
void Board::set_number(int cd, char num){
  int x = cd % SIZE;
  int y = cd / SIZE;
  if(constant_[y][x] != '\0')
    std::cout << "[!]その数字は変更できません。" << std::endl;
  else if(board_[y][x] == num) //既にそこにある数字と同じ数字。
    board_[y][x] = '.';
  else if(!check_num(num - 48, cd))
    std::cout << "[!]そこにその数字は入れられません。" << std::endl;
  else
    board_[y][x] = num;
}
void Board::set_cursor(int cd){
  int x = cd % SIZE;
  int y = cd / SIZE;
  for(int i = 0; i < SIZE; i++)
    for(int j = 0; j < SIZE; j++)
      cursor_[i][j] = ' ';
  cursor_[y][x] = '>';

  if(board_[y][x] != '.'){
    for(int i = 0; i < 9; i++)
      for(int j = 0; j < 9; j++){
        if(board_[i][j] == board_[y][x] && i * 9 + j != cd){
          if(constant_[i][j] != '\0')
            cursor_[i][j] = '['; //同じ数字&変更不可を強調。
          else cursor_[i][j] = '{'; //同じ数字を強調。
        }
      }
  }
}
bool Board::answer_match(){
    for(int i = 0; i < 9; i++)
      for(int j = 0; j < 9; j++)
        if(board_[i][j] == '.')
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
void Board::save_board(){
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      save_[i][j] = board_[i][j];
  std::cout << "### 盤面を一時保存しました ###" << std::endl;
}
void Board::load_board(){
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      board_[i][j] = save_[i][j];
  std::cout << "### 一時保存した盤面を読み込みました ###" << std::endl;
}

class GM{
public:
  int ask_hint();
  int ask_num();
  void congratulate();
};

int GM::ask_hint(){
  char get;
  while(true){
    std::cout << "難易度を選択してください[1~3]:" << std::endl
              << "1. easy" << std::endl
              << "2. normal" << std::endl
              << "3. hard" << std::endl
              << ": ";
    std::cin >> get;
    switch(get){
    case '1':
    case 'e':
      return 40;
    case '2':
    case 'n':
      return 30;
    case '3':
    case 'h':
      return 20;
    default: std::cout << "[!]無効な入力です。";
    }
  }
}
int GM::ask_num(){
  std::string get;
  int ret;

  while(true){
    std::cout << "                     X    Y" << std::endl
              << "数字[1~9]または座標[1~9][1~9]を入力: ";
    std::cin >> get;

    if(get[1] == '\0'){
      ret = get[0] - '0';
      if(ret == MEMO || ret == SAVE || ret == LOAD)
        return ret * IDENTIFY;
      return ret;
    }
    ret = (get[0] - '0') - 1 + ((get[1] -'0') - 1) * 9;
    if(ret >= 0 && ret <= 80)
      return ret + IDENTIFY; //識別用に100を足して返す。
    std::cout << "[!]無効な入力です。" << std::endl;
  }
}
void GM::congratulate(){
  std::cout << std::endl << "<< Congratulations!! >>"<< std::endl
            << "あなたはすべての数字を導き出しました。"<< std::endl;
}

int main(){
  int get, cd = 0;
  bool m; //auto_memoの表示on/off
  GM gm;
  Board sudoku(gm.ask_hint());

  sudoku.make_memo(cd);
  while(true){
    sudoku.out_board(m);
    get = gm.ask_num();
    switch(get / IDENTIFY){
    case 0: //1~9が入力された。
      sudoku.set_number(cd, get + 48);
      sudoku.set_cursor(cd);
      sudoku.make_memo(cd);
      if(sudoku.answer_match()){
        sudoku.out_board(m);
        gm.congratulate();
        return 0;
      }
      break;
    case 1: //11~99(座標)が入力された。
      cd = get - IDENTIFY;
      sudoku.set_cursor(cd);
      sudoku.make_memo(cd);
      break;
    case MEMO:
      m = !m;
      break;
    case SAVE:
      sudoku.save_board();
      break;
    case LOAD:
      sudoku.load_board();
      break;
    default:
      std::cout << "[!]無効な入力です。" << std::endl;
      break;
    }
  }

  return 0;
}
