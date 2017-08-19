#include <iostream>
using namespace std;

class Rocket{
  int fuel;
  int speed;
public:
  Rocket(int x);
  /*
    ↑コンストラクタ(宣言のみ)。
    (int x)と、適当な変数を引数に書いたが、(int)だけでもOK。
  */
  void accel(); //加速させる関数を使う宣言。
};

Rocket:: Rocket(int x) : fuel(x), speed(0){}
/*
  ↑コンストラクタを定義。
  引数として与えられた値をfuelに入れ、speedは0に設定しただけ。
*/
void Rocket:: accel(){
  if(fuel >= 2){
    speed += 2; //"+="は右辺を左辺に足す。
    fuel -= 2;
    cout << "現在の燃料は" << fuel << "です。\n"
         << "現在の速度は" << speed << "です。\n";
  }
  else{
    cout << "燃料切れです。加速できません。漂流です。\n";
  }  
}
/*
  ↑クラスの動作(accel)を定義。
  燃料が2以上なら燃料を消費して加速、それ未満なら漂流。
*/

int main(){
  cout << "ロケットに燃料(整数)を入れてください。\n";
  int f;
  cin >> f;

  Rocket ohtori(f);
  cout << "加速します。\n";
  ohtori.accel();
  cout << "また、加速します。\n";
  ohtori.accel();
  cout << "またまた、加速してみます。\n";
  ohtori.accel();
  cout << "鳳号の冒険は終わりました。\n";
  return 0;
}
