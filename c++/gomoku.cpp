#include <iostream>
#include <string>
  
int main(){
  char get_i1; char get_j1; //i:行 j:列
  char get_i2; char get_j2;
  int i1; int j1;
  int i2; int j2;
  int count = 0; //終了まで何手かをカウントする。
  int sw = 1; //1P,2P切り替え用。
  int p = 0; int jud = 0; //この2つは判定用。
  std::string mark; //前の手番のマークを記録(x|, o|)。
  std::string board[9][9];
  for(int i = 0; i < 9; i++){ //まずすべてのマスを空白に。
    for(int j = 0; j < 9; j++){
      board[i][j] = " |";
    }
  }

  std::cout << "---------------------------------------------------------------\n"
            << "| 下の入力例のように行、列の順に半角で座標を指定してください。|\n"
            << "| 入力例) 1p[x]の手を入力:4d                                  |\n"
            << "---------------------------------------------------------------\n";

  while(1){
    count++;
    if(count == 82){
      std::cout << "<< 引き分け >>" << std::endl;
      break;
    }
    
    if(sw == 1) mark = "o|";
    else if(sw == 2) mark = "x|";
                       
    std::cout << "\n  a b c d e f g h i\n";
    std::cout << " -------------------\n";
    for(int i = 0; i < 9; i++){
      std::cout << i + 1 << "|";
      for(int j = 0; j < 9; j++){
        std::cout << board[i][j];
        /////////////// 石が置かれるごとに判定 ///////////////
        if(board[i][j] == mark){
          if(j <= 4){
            for(int s = 1; s <= 4; s++){ //横チェック。
              if(board[i][j + s] == mark) p++;
            }
            if(p == 4) jud = 1; //終了を検出したらjud = 1;。
            p = 0;
          }
          if(i <= 4){
            for(int v = 1; v <= 4; v++){ //縦チェック。
              if(board[i + v][j] == mark) p++;
            }
            if(p == 4) jud = 1;
            p = 0;
          }
          if(i <= 4 && j <= 4){
            for(int rd = 1; rd <= 4; rd++){ //右斜めチェック。
              if(board[i + rd][j + rd] == mark) p++;
            }
            if(p == 4) jud = 1;
            p = 0;
          }
          if(i <= 4 && j >= 4){
            for(int ld = 1; ld <= 4; ld++){ //左斜めチェック。
              if(board[i + ld][j - ld] == mark) p++;
            }
            if(p == 4) jud = 1;
            p = 0;
          }
        }
        //////////////////////////////////////////////////////
      }
      std::cout << std::endl;
    }
    std::cout << " -------------------\n";
    
    if(jud >= 1){ //終了を宣言。
      std::cout << "<< " << count - 1 << "手で";
      if(mark == "x|"){ std::cout << "1P[x]"; }
      else std::cout << "2P[o]";
      std::cout << "の勝ち!! >>" << std::endl;
      break;
    }
    
    switch(sw){
    case 1:
      while(1){
        std::cout << "1P[x]の手を入力:";
        std::cin >> get_i1;
        std::cin >> get_j1;
        //規定外の入力がないかチェック。
        if((get_i1 != '1' && get_i1 != '2' && get_i1 != '3' && get_i1 != '4' && get_i1 != '5' && get_i1 != '6' && get_i1 != '7' && get_i1 != '8' && get_i1 != '9') || (get_j1 != 'a' && get_j1 != 'b' && get_j1 != 'c' && get_j1 != 'd' && get_j1 != 'e' && get_j1 != 'f' && get_j1 != 'g' && get_j1 != 'h' && get_j1 != 'i'))
          std::cout << "[!]入力しなおしてください。\n";
        else{
          i1 = get_i1 - 48;
          j1 = get_j1 - 96;
          //既に石が置かれていないかチェック。
          if(board[i1 - 1][j1 - 1] != " |")
            std::cout << "[!]入力しなおしてください。\n";
          else break;
        }
      }
      board[i1 - 1][j1 - 1] = "x|";
      sw = 2;
      break;
    case 2:
      while(1){
        std::cout << "2P[o]の手を入力:";
        std::cin >> get_i2;
        std::cin >> get_j2;
        if((get_i2 != '1' && get_i2 != '2' && get_i2 != '3' && get_i2 != '4' && get_i2 != '5' && get_i2 != '6' && get_i2 != '7' && get_i2 != '8' && get_i2 != '9') || (get_j2 != 'a' && get_j2 != 'b' && get_j2 != 'c' && get_j2 != 'd' && get_j2 != 'e' && get_j2 != 'f' && get_j2 != 'g' && get_j2 != 'h' && get_j2 != 'i'))
          std::cout << "[!]入力しなおしてください。\n";
        else{
          i2 = get_i2 - 48;
          j2 = get_j2 - 96;
          if(board[i2 - 1][j2 - 1] != " |")
            std::cout << "[!]入力しなおしてください。\n";
          else break;
        }
      }
      board[i2 - 1][j2 - 1] = "o|";
      sw = 1;
      break;
    }
  }
  
  return 0;
}
