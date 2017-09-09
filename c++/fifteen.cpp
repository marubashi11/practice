#include <iostream>
#include <string>
#include <random>

void out_board(std::string board[]){
  std::cout << "-------------" << std::endl;
  for(int i = 0; i < 4; i++){
	std::cout << "|";
	for(int j = 0; j < 4; j++){
	  std::cout << board[i * 4 + j] << "|";
	}
	std::cout << std::endl;
  }
  std::cout << "-------------" << std::endl;
  std::cout << "       up[w]" << std::endl
			<< "left[a]     right[s]" << std::endl
			<< "      down[z]" << std::endl;
}
int shuffle(char dir, int a, std::string board[]){
  std::string buff;
  switch(dir){
  case 'z': //入力は@@の動きとは真逆になる。
	if(a / 4 != 0){
	  buff = board[a];
	  board[a] = board[a - 4];
	  board[a - 4] = buff;
	  a = a - 4;
	}
	return a;
  case 's':
	if(a % 4 != 0){
	  buff = board[a];
	  board[a] = board[a - 1];
	  board[a - 1] = buff;
	  a = a - 1;
	}
	return a;
  case 'a':
	if(a % 4 != 3){
	  buff = board[a];
	  board[a] = board[a + 1];
	  board[a + 1] = buff;
	  a = a + 1;
	}
	return a;
  case 'w':
	if(a / 4 != 3){
	  buff = board[a];
	  board[a] = board[a + 4];
	  board[a + 4] = buff;
	  a = a + 4;
	}
	return a;
  }
}

int main(){
  std::string board[16] = { " 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "10", "11", "12", "13", "14", "15", "@@" };
  std::string buff;
  char dir;
  int a = 15; //配列中の@@の位置。
  std::random_device r;

  for(int i = 0; i < 200; i++){ //comがぐちゃぐちゃにする。
	switch(r() % 4){
	case 0:
	  dir = 'w';
	  break;
	case 1:
	  dir = 'a';
	  break;
	case 2:
	  dir = 's';
	  break;
	case 3:
	  dir = 'z';
	  break;
	}
	a = shuffle(dir, a, board);
  }

  while(true){ //playerの手番。
	out_board(board);
	if(board[0] == " 1" && board[1] == " 2" && board[2] == " 3" && board[3] == " 4" && board[4] == " 5" && board[5] == " 6" && board[6] == " 7" && board[7] == " 8" && board[8] == " 9" && board[9] == "10" && board[10] == "11" && board[11] == "12" && board[12] == "13" && board[13] == "14" && board[14] == "15" && board[15] == "@@"){
	  std::cout << "<< CONGRATULATIONS >>" << std::endl;
	  break;
	}
	std::cin >> dir;
	a = shuffle(dir, a, board);
  }

  return 0;
}
