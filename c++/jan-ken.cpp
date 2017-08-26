#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

void out_hand(int h){ //手を表示する関数。
  switch(h){
  case 1:
    std::cout << "グー   |\n";
    break;
  case 2:
    std::cout << "チョキ |\n";
    break;
  case 3:
    std::cout << "パー   |\n";
    break;
  }
}
void info_win(int w, int t){ //勝率を出力する関数。
  std::cout << "|| 勝った回数: " << w << "回\n"
            << "|| 現在の勝率: " << w*100/t << "%\n";
}
int ask(){ //再戦を尋ねる関数。
  std::string ans;
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n( - - ) < もう1戦??\n再戦する場合はyes[y]を入力:";
  std::cin >> ans;
  if(ans == "y" || ans == "yes"){
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    return 1;
  }
  else std::cout << "( . . ) < お疲れ様でした!\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

class Janken{
public:
  Janken(); //playerの入力を貰い、hand_を設定。
  void get_comhand(); //comhand_を設定。
  int judge(); //じゃんけんの勝敗をresult_に設定後、その値をjudgeに返す。
  void out_each_hand(int); //両者の手を出力。
  void out_result(); //じゃんけんゲームの結果を出力。
  ////////////////////ここからglico用メンバ関数////////////////////
  void get_dist(int); //glicoの距離を設定。
  void get_glico(); //glico用にcomhand_を設定。
  void get_cord(int); //座標を更新。
  int out_cord(); //両者の座標を表示。
  void out_300m(int); //glicoの結果を出力。
private:
  int hand_; //playerの手。
  int comhand_; //comの手。
  int result_; //0:引き分け、1:player勝ち、2:com勝ち。
  int distance_;
  int Pcord_;
  int Ccord_;
};
Janken::Janken(){
  std::string input;
  std::cout << "( - - )o < ジャン、ケン…\n\n"
            <<"          グー[g]\nチョキ[c]         パー[p]\n入力:";
  std::cin >> input;
  if(input == "1" || input == "g" || input == "rock")
    hand_ = 1;
  else if(input == "2" || input == "c" || input == "scissors")
    hand_ = 2;
  else if(input == "3" || input == "p" || input == "paper")
    hand_ = 3;
  else std::cout << "[!]無効な入力: 前回と同じ手を出します。\n";
}
void Janken::get_comhand(){
  std::srand((unsigned)time(NULL));
  comhand_ = rand() % 3 + 1;
}
int Janken::judge(){
  result_ = (comhand_ - hand_ + 3) % 3;
  return result_;
}
void Janken::out_each_hand(int j){
  std::cout << "\n--------------\n| you:";
  out_hand(hand_);
  std::cout << "| com:";
  out_hand(comhand_);
  std::cout << "--------------\n";
  std::cout << "( ";
  switch(j){
  case 0:
    std::cout << "- - ";
    break;
  case 1:
    std::cout << "* * ";
    break;
  case 2:
    std::cout << "^ ^ ";
    break;
  }
  std::cout <<")";
  switch(comhand_){
  case 1:
    std::cout << "o ";
    break;
  case 2:
    std::cout << "v ";
    break;
  case 3:
    std::cout << "w ";
  }
  std::cout << "< ポン!!\n";
}
void Janken::out_result(){
  switch(result_){
  case 0:
    std::cout << "\n<<あいこ>>\n\n";
    break;
  case 1:
    std::cout << "\n<<あなたの勝ち>>\n\n";
    break;
  case 2:
    std::cout << "\n<<あなたの負け>>\n\n";
    break;
  }
}

class LookThisWay{
public:
  LookThisWay(int); //あっちむいてホイを実行。
  int out_result(int); //あっちむいてホイの勝敗を出力し、あいこの場合0、playerの勝ちなら1をこの関数に返す。
private:
  int dir_;
  int comdir_;
};
LookThisWay::LookThisWay(int j){
  std::srand((unsigned)time(NULL));
  comdir_ = rand() * 3 % 4; //何故か0~3に収まらないことがある。
  
  std::string input;

  switch(j){
  case 1:
    std::cout << "\n+++++++<あなたのターン>+++++++\n"
              << "\n(- - ;)  あっちむいて… >\n";
    break;
  case 2:
    std::cout << "\n+++++++<comのターン>+++++++\n"
              << "\n( ' - ) < あっちむいて…\n";
    break;
  }
  std::cout << "       up[w]\nleft[a]     right[s]\n      down[z]        入力:";
  std::cin >> input;
  if(input == "w" || input == "up" || input == "u") dir_ = 1;
  else if(input == "a" || input == "left" || input == "l") dir_ = 2;
  else if(input == "s" || input == "right" || input == "r") dir_ = 3;
  else if(input == "z" || input == "down" || input == "d") dir_ = 4;
  else std::cout << "[!]無効な入力: 前回と同じ手を出します。\n";
  std::cout << std::endl;
  switch(comdir_){
  case 1:
    std::cout << "( ゜゜)↑";
    break;
  case 2:
    std::cout << "(- -  )←";
    break;
  case 3:
    std::cout << "(  - -)→";
    break;
  case 4:
    std::cout << "( . . )↓";
    break;
  }
  switch(j){
  case 1:
    std::cout << "        ホイ!! >\n\n";
    break;
  case 2:
    std::cout << "  < ホイ!!\n\n";
    break;
  }
}
int LookThisWay::out_result(int x){
  if((comdir_ + 1) == dir_){
    std::cout << "<<あなたの";
    switch(x){
    case 1:
      std::cout << "勝ち>>\n\n";
      return 1;
      break;
    case 2:
      std::cout << "負け>>\n\n";
      break;
    }
  }
  else{
    std::cout << "\n++++++++<<あいこ>>+++++++++\n";
    return 0;
  }
}

void Janken::get_dist(int d){distance_ = d;}
void Janken::get_glico(){
  int get;
  std::srand((unsigned)time(NULL));
  get = rand() % 5;
  if(get == 0 || get == 1) comhand_ = 1;
  else if(get == 2 || get == 3) comhand_ =2;
  else if(get == 4) comhand_ = 3;
}
void Janken::get_cord(int j){
  if(j == 0);
  else if(j == 1){
    switch(hand_){
    case 1:
      Pcord_ = Pcord_ + 3;
      break;
    case 2:
      Pcord_ = Pcord_ + 6;
      break;
    case 3:
      Pcord_ = Pcord_ + 6;
      break;
    }
  }
  else if(j == 2){
    switch(comhand_){
    case 1:
      Ccord_ = Ccord_ + 3;
      break;
    case 2:
      Ccord_ = Ccord_ + 6;
      break;
    case 3:
      Ccord_ = Ccord_ + 6;
      break; 
    }
  }
}
int Janken::out_cord(){
  std::cout << "\n( YOU ): S ";
  if(Pcord_ >= distance_) Pcord_ = distance_;
  for(int i = 0; i < Pcord_; i++) std::cout << "=";
  for(int j = 0; j < (distance_ - Pcord_); j++) std::cout << "-";
  std::cout << " G\n";
  
  std::cout << "( COM ): S ";
  if(Ccord_ >= distance_) Ccord_ = distance_;
  for(int i = 0; i < Ccord_; i++) std::cout << "=";
  for(int j = 0; j < (distance_ - Ccord_); j++) std::cout << "-";
  std::cout << " G\n\n";
  
  if(Pcord_ == distance_) return 1;
  if(Ccord_ == distance_) return 2;
}
void Janken::out_300m(int r){
  std::cout << "\n \\  wwwww  /" << "\n"
            << "  \\( ";
  if(r == 1) std::cout << "YOU";
  else std::cout << "COM";
  std::cout << " )/\n"
            << "    |   |\n"
            << "    |   |\n"
            << "     | |\n"
            << "     | `\n"
            << "     ^\n";
  if(r == 1) std::cout << "<< YOU WIN >>\n";
  else std::cout << ">> YOU LOSE <<\n";
}
///////////////////////////ここからメイン//////////////////////////
int main(){
  int mode;
  int jud[3];
  int total = 0;
  int win = 0;
  int hold;
  
  while(1){ //このwhileは思ったとおりに働いていない。
    std::cout << "( - - ) < どのモードで遊びますか??\n\n"
              << "1:じゃんけんゲーム\n"
              << "2:あっちむいてホイ\n"
              << "3:グリコ\n"
              << "0:exit\n"
              << "\n番号を入力:";
    std::cin >> mode;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    if(mode == 0){ //文字が入力された場合もこれになる？
      std::cout << "( - - ) < さようなら。\n";
      break;
    }
    
    else if(mode == 1){
      while(1){
        Janken janken;
        janken.get_comhand();
        jud[0] = janken.judge();
        janken.out_each_hand(jud[0]);
        janken.out_result();
        if(jud[0] == 0); //あいこは決着ではないのでそのままループ。
        else{
          total++;
          if(jud[0] == 1) win++;
          info_win(win, total);
          if(ask() == 1);
          else break;
        }
      }
    }

    else if(mode == 2){
      while(1){
        Janken janken;
        janken.get_comhand();
        jud[0] = janken.judge();
        if(jud[0] == 0){ //じゃんけんであいこ
          janken.out_each_hand(jud[0]);
          janken.out_result();
        }
        else{
          janken.out_each_hand(jud[0]);
          LookThisWay atti(jud[0]);
          jud[1] = atti.out_result(jud[0]);
          if(jud[1] != 0){ //あいこ以外なら決着。
            total++;
            if(jud[1] == 1) win++;
            info_win(win, total);
            if(ask() == 1);
            else break;
          }
        }
      }
    }

    else if(mode == 3){
      std::cout << "ゴールまでの距離を入力:";
      std::cin >> hold;
      while(1){
        Janken glico;
        glico.get_dist(hold);
        glico.get_glico();
        jud[0] = glico.judge();
        if(jud[0] == 0){
          glico.out_each_hand(jud[0]);
          glico.out_result();
        }
        else{
          glico.out_each_hand(jud[0]);
          glico.out_result();
          glico.get_cord(jud[0]);
          jud[2] = glico.out_cord();
          if(jud[2] == 1 || jud[2] == 2){
            glico.out_300m(jud[2]);
            break;
          }
        }
      }
    }
    else std::cout << "[!]無効な入力: あなたはつまみ出されました。\n";
    break;
  }
  return 0;
}
