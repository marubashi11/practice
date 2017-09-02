#include <iostream>
#include <string>
#include <random>

void detect(int p_i, int p_j, int under[][9], int det, std::string field[][9]){ //地雷の探知とその数の代入を行う関数。
  if(p_i != 1){
    if(p_j != 1 && under[p_i - 2][p_j - 2] == 1) det++;
    if(under[p_i - 2][p_j - 1] == 1) det++;
    if(p_j != 9 && under[p_i - 2][p_j] == 1) det++;
  }
  if(p_j != 1 && under[p_i - 1][p_j - 2] == 1) det++;
  if(p_j != 9 && under[p_i - 1][p_j] == 1) det++;
  if(p_i != 9){
    if(p_j != 1 && under[p_i][p_j - 2] == 1) det++;
    if(under[p_i][p_j - 1] == 1) det++;
    if(p_j != 9 && under[p_i][p_j] == 1) det++;
  }
  field[p_i - 1][p_j - 1] = det + 48;
  det = 0;
}

int main(){
  int mine_i; int mine_j; int mine_total;
  char get_i; char get_j; int p_i; int p_j;
  char get_fi; char get_fj; int f_i; int f_j;
  int det = 0; //周りのbomの数を数える。
  int jud = 0; //勝利判定用。
  std::string field[9][9];
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      field[i][j] = "\""; //すべてのfieldを草地に
    }
  }
  int under[9][9];
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      under[i][j] = 0; //安全なfieldはunder = 0。
    }
  }

  while(1){
    std::cout << "Please set the total number of mines:";
    std::cin >> mine_total;
    if(mine_total <= 0 || mine_total >= 81)
      std::cout << "Please input again.\n";
    else break;
  }
  std::random_device rnd;
  for(int b = 0; b < mine_total; b++){ //mineを10個セット。
    mine_i = rnd() % 9;
    mine_j = rnd() % 9;
    if(under[mine_i][mine_j] != 0) b--;
    under[mine_i][mine_j] = 1; //mineがあるfieldはunder = 1。
  }

  while(1){
    std::cout << "\n  a b c d e f g h i\n"
	      << " -------------------\n";
    for(int i = 0; i < 9; i++){
      std::cout << i + 1 << "|";
      for(int j = 0; j < 9; j++){
	std::cout << field[i][j] << " ";
      }
      std::cout << "|" << std::endl;
    }
    std::cout << " -------------------\n";
    while(1){
      std::cout << "Where are you going to dig\?:"; //日本語は文字化けする。
      std::cin >> get_i;
      std::cin >> get_j;
      if((get_i != '1' && get_i != '2' && get_i != '3' && get_i != '4'&& get_i != '5' && get_i != '6' && get_i != '7' && get_i != '8' && get_i != '9'))
	std::cout << "[!]Please input again.\n";
      else{
	p_i = get_i - 48;
	p_j = get_j - 96;
	if(field[p_i - 1][p_j - 1] != "\"")
	  std::cout << "[!]Please input again.\n";
	else break;
      }
    }
    if(get_i != 'f' && under[p_i - 1][p_j - 1] == 1){
      for(int i = 0; i < 9; i++){
	for(int j = 0; j < 9; j++){
	  field[i][j] = "*"; //すべてのfieldを焼け野原に。
	}
      }
      std::cout << "\n  a b c d e f g h i\n"
		<< " -------------------\n";
      for(int i = 0; i < 9; i++){
	std::cout << i + 1 << "|";
	for(int j = 0; j < 9; j++){
	  std::cout << field[i][j] << "|";
	}
	std::cout << std::endl;
      }
      std::cout << " -------------------\n";
      std::cout << "<< YOU LOSE >>\n"
		<< "You've trampled the mines.\n"; //日本語は文字化けする。
      break;
    }
    
    detect(p_i, p_j, under, det, field);
    if(p_i != 1){
      if(p_j != 1 && under[p_i - 2][p_j - 2] != 1)
	detect(p_i - 1, p_j - 1, under, det, field);
      if(under[p_i - 2][p_j - 1] != 1)
	detect(p_i - 1, p_j, under, det, field);
      if(p_j != 9 && under[p_i - 2][p_j] != 1)
	detect(p_i - 1, p_j + 1, under, det, field);
    }
    if(p_j != 1 && under[p_i - 1][p_j - 2] != 1)
      detect(p_i, p_j - 1, under, det, field);
    if(p_i != 9 && under[p_i - 1][p_j] != 1)
      detect(p_i, p_j + 1, under, det, field);
    if(p_i != 9){
      if(p_j != 1 && under[p_i][p_j - 2] != 1)
	detect(p_i + 1, p_j - 1, under, det, field);
      if(under[p_i][p_j -1] != 1)
	detect(p_i + 1, p_j, under, det, field);
      if(p_j != 9 && under[p_i][p_j] != 1)
	detect(p_i + 1, p_j + 1, under, det, field);
    }

    for(int i = 0; i < 9; i++){ //勝利判定。
      for(int j = 0; j < 9; j++){
	if(field[i][j] == "\"") jud++;
      }
    }
    if(jud == mine_total){
      std::cout << "\n<< Congratulations!! >>\n"
		<< "You've found all the mines.\n";
      break;
    }
    jud = 0;
  }
  return 0;
}
