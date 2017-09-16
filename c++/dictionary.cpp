#include <iostream>
#include <cstring> //strcmp用。

int main(){
  char word[5][1000]; //入力受け取り用。
  char* w_address[5];
  char* buff;

  std::cout << "入力された5つの単語を辞書順に並べ替えます。" << std::endl;
  for(int i = 0; i < 5; i++){
    std::cout << i + 1 << "つ目の単語を入力: ";
    std::cin >> word[i];
    w_address[i] = word[i];
  }
  std::cout << "入力された単語は:" << std::endl;
  for(int i = 0; i < 5; i++)
    std::cout << i + 1 << ". " << w_address[i] << std::endl;
  std::cout << std::endl;

  std::cout << "~~~~~~~~~~~~~~~ 並び替え中 ~~~~~~~~~~~~~~~" << std::endl;
  for(int re = 0; re < 5; re++) //適当な回数処理を繰り返す。
    for(int i = 0; i < 4; i++){
      if(strcmp(w_address[i], w_address[i + 1]) > 0){
        buff = w_address[i];
        w_address[i] = w_address[i + 1];
        w_address[i + 1] = buff;
        std::cout << w_address[i] << " <-> " << w_address[i + 1] << std::endl;
      }
    }
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl << std::endl;

  std::cout << "並び替え完了!:" << std::endl;
  for(int i = 0; i < 5; i++)
    std::cout << i + 1 << ". " << w_address[i] << std::endl;
  std::cout << std::endl;

  return 0;
}
