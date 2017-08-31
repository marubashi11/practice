#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Brave{
  int hp;
  int atk;
public:
  Brave(): hp(100), atk(100){}
  int get_attack(int x); //攻撃力に変化を加えて返す。
  int get_hp(int y); //HPに変化を加えて返す。
};
int Brave:: get_attack(int a){
  atk = atk + a;
  return atk;
}
int Brave:: get_hp(int b){
  hp = hp + b;
  return hp;
}

class Witch{
  int hp;
public:
  Witch(): hp(50){}
  int attack_up(){return 10;}
};

int main(){
  Brave brave;
  Witch witch;
  int bhp;
  int batk;
  int up = 0;
    
  for(int i = 0; i < 3; i++){
    
    bhp = brave.get_hp(0);
    batk = brave.get_attack(up);
    cout << "勇者HP:" << bhp
         << "\n勇者atk:" << batk << endl;
    cout << "魔女は呪文を唱えた!\n";
    up = witch.attack_up();
  }
}
