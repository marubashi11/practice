#include <iostream>
#include <random>

/*
  今度はfieldを一次元配列で考える。
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

class Field{
public:
  Field(); //すべてのcellを草地に設定。
  void out_field(int); //fieldを表示。引数はmine数。
  void set_field(int, char); //f_state_[int] = char;を実行。
  int report(int); //指定cellが… 草: 0、'0': 1、'x': 2、他: 3。
  void blow(int); //指定cellを爆破させる。
  int judge(int); //勝利判定。終了なら1を返す。引数はmine数。
private:
  char f_state_[81];
};
Field::Field(){
  for(int i = 0; i < 81; i++){
    f_state_[i] = '\"';
  }
}
void Field::out_field(int mine){
  char c_num;
  std::cout << std::endl << " ";
  for(int i = 1; i <= 9; i++){
    c_num = i + 96;
    std::cout << " " << c_num;
  }
  std::cout << std::endl << " --------------------" << std::endl;
  for(int i = 0; i < 9; i++){
    std::cout << i + 1 << "|";
    for(int j = 0; j < 9; j++){
      std::cout << f_state_[i * 9 + j] << " ";
    }
    std::cout << "|" << std::endl;
  }
  std::cout << " --------------------   total mine: " << mine << std::endl;
}
void Field::set_field(int cell, char info){
  f_state_[cell] = info;
}
int Field::report(int cell){
  if(cell == 482) return 482;
  else if(f_state_[cell] == '\"') return 0;
  else if(f_state_[cell] == '0') return 1;
  else if(f_state_[cell] == 'x') return 2;
  else return 3;  
}
int Field::judge(int mine){
  int jud = 0;
  for(int i = 0; i < 81; i++)
    if(f_state_[i] == '\"' || f_state_[i] == 'x') jud++;
  if(jud == mine) return 1;
  else return 0;
}

class Underground{
public:
  Underground(int); //与えられた数だけ地雷を埋め込む。
  char sonar(int); //指定cellの周囲8マスを探知し地雷数をchar型で返す。
  bool step_on(int); //地雷cellを踏んだか確認する。
private:
  bool u_state_[81];
  int mine_cell_;
};
Underground::Underground(int mine_total){
  for(int i = 0; i < 81; i++){
    u_state_[i] = false;
  }
  std::random_device rnd;
  for(int b = 0; b < mine_total; b++){
    mine_cell_ = rnd() % 81;
    if(u_state_[mine_cell_] == true) b--;
    else u_state_[mine_cell_] = true;
  }
}
char Underground::sonar(int cell){
  int l_start = 0;
  int l_end = 2;
  int c_start = 0;
  int c_end = 2;
  int det = 0;
  switch(cell / 9){
  case 0: //最上段のこと。
    l_start = 1;
    break;
  case 8: //最下段のこと。
    l_end = 1;
    break;
  }
  switch(cell % 9){
  case 0: //最左列のこと。
    c_start = 1;
    break;
  case 8: //最右列のこと。
    c_end = 1;
    break;
  }
  for(int l = l_start; l <= l_end; l++){
    for(int c = c_start; c <= c_end; c++){
      if(u_state_[cell - 10 + l * 9 + c]) det++;
    }
  }
  char info = det + 48;
  return info;
}
bool Underground::step_on(int cell){
  return u_state_[cell];
}

class Host{
public:
  Host(); //入力説明を行う。
  int ask_mine_number();
  int ask_cell(int); //引数1でflagモードに変化。
  bool announce_result(int); //1:クリア 2:ゲームオーバー
};
Host::Host(){
  std::cout << "++++++++++++++++++++++++++++ INSTRUCTION +++++++++++++++++++++++++++" << std::endl
	    << "1) First, you set the total number of mines as an integer." << std::endl
	    << "   (Recommended setting is 15.)" << std::endl
	    << "2) When you dig the field, please enter the number as example below." << std::endl
	    << std::endl << "    example>> Where are you going to dig\?: 4c" << std::endl << std::endl
	    << "3) If you want to switch to flag mode, please enter \"ff\"." << std::endl
	    << "   (do the same input when you want to finish flag mode.)" << std::endl
	    << "4) Do not cry even if you step on a mine with the first step!" << std::endl
	    << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
}
int Host::ask_mine_number(){
  int total;
  while(true){
    std::cout << "Please set the total number of mines: ";
    std::cin >> total;
    if(total >= 1 && total <= 80){
      std::cout << total << " mines was set up." << std::endl;
      return total;
    }
    std::cout << "[!]You entered incorrect number.";
  }
}
int Host::ask_cell(int mode){
  char get_i = '\0';
  char get_j = '\0';
  int cell = 0;
  while(true){
    switch(mode){
    case 0:
      std::cout << std::endl << "Where are you going to dig\?: ";
      break;
    case 1:
      std::cout << ":: Flag mode ::" << std::endl
		<< "Where do you want to put up a flag\?: ";
      break;
    }
    std::cin >> get_i;
    std::cin >> get_j;
    cell = ((get_i - 48) - 1) * 9 + ((get_j - 96) - 1);
    if((cell >= 0 && cell <= 80) || cell == 482)
      return cell;
    std::cout << "[!]You entered incorrect number.";
  }
}
bool Host::announce_result(int r){
  switch(r){
  case 1:
    std::cout << std::endl << "<< CONGRATULATIONS!! >>" << std::endl
	      << "You've found all the mines." << std::endl;
    return true;
    break;
  case 2:
    std::cout << "<< YOU LOSE >>" << std::endl
	      << "You stepped on the mines." << std::endl;
    return false;
    break;
  }
}

///////////////////////// ここからメイン /////////////////////////
int main(){
  void detect(int, Underground*, Field*);
  //↑指定cellの周囲8マスでunder.sonarを実行し結果をf_state_に格納する関数、の宣言。
  int buff[2];
  Field field;
  Host host;
  field.out_field(0);
  int total_mine = host.ask_mine_number();
  Underground under(total_mine);
  Underground* address_u =&under; //メンバ関数の参照に必要。
  Field* address_f =&field; //メンバ関数の参照に必要。

  while(true){
    buff[1] = 0;
    buff[0] = host.ask_cell(0);
    
    if(buff[0] != 482 && under.step_on(buff[0])){
      for(int i = 0; i < 81; i++)
	if(under.step_on(i) && field.report(i) != 2)
	  field.set_field(i, '#');
      field.out_field(0);
      host.announce_result(2);
      break;
    }
    
    switch(buff[0]){
    case 482: //Flag mode
      while(buff[1] != 482){ //もう一度"ff"が入力されたら終了。
	buff[1] = host.ask_cell(1);
	switch(field.report(buff[1])){
	case 0:    
	  field.set_field(buff[1], 'x');
	  field.out_field(total_mine);
	  break;
	case 2:
	  field.set_field(buff[1], '\"');
	  field.out_field(total_mine);
	  break;
	case 482:
	  std::cout << "::    end    ::" << std::endl;
	  break;
	default:
	  std::cout << "[!]You can NOT enter there." << std::endl;
	  break;
	}
      }
      break;
    default:
      detect(buff[0], address_u, address_f);
      for(int re = 0; re < 9; re++) //re < 9;は適当に行数と同じにしただけ。
	for(int i = 0; i < 81; i++)
	  if(field.report(i) == 1) detect(i, address_u, address_f);
      field.out_field(total_mine);
      break;
    }
    if(host.announce_result(field.judge(total_mine))) break;
  }
  return 0;
}
//////////////////////////////////////////////////////////////////
void detect(int buff, Underground* address_u, Field* address_f){
  int L_start = 0; int L_end = 2;
  int C_start = 0; int C_end = 2;
  switch(buff / 9){
  case 0: //最上段のこと。
    L_start = 1;
    break;
  case 8: //最下段のこと。
    L_end = 1;
    break;
  }
  switch(buff % 9){
  case 0: //最左列のこと。
    C_start = 1;
    break;
  case 8: //最右列のこと。
    C_end = 1;
    break;
  }
  for(int L = L_start; L <= L_end; L++){
    for(int C = C_start; C <= C_end; C++){
      int checking_cell = buff - 10 + L * 9 + C;
      if(!((*address_u).step_on(checking_cell)))
	(*address_f).set_field(checking_cell, (*address_u).sonar(checking_cell));
    }
  }
}
