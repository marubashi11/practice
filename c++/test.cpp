#include <iostream>

int main(){
  int a[8][8];
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      a[i][j] = i * 10 + j;
    }
  }
  for(int n = 0; n < 10; n++){
    std::cout << "中身を表示:\n" << a[0][n] << std::endl;
    }
  return 0;
}
