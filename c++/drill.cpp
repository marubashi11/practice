#include <iostream>
#include <cstdlib>//rand()を扱うのに必要。
#include <ctime>//例によって秒数で乱数を決めるのに必要。
using namespace std;

void jud(int x, int ans){//正解するまでループさせる関数。
  if(ans != x){
    while(ans != x){
      cout << "\nやり直し!\n";
      cin >> ans;
    }
    cout << "正解!!\n";
  }
  else{
    cout << "正解!!\n";
  }
}

int main(void){
  int stime;
  int ftime;
  int num;
  int opr;
  int a;
  int b;
  int x;
  int ans;

  cout << "問題数を選択:";
  cin >> num;
  if(num <= 0){
    while(num <= 0){
      cout << "\n自然数で入力してください。\n";
      cin >> num;
    }
  }
  stime = time(NULL);

  for(int i = 0; i < num; i++){//決めた問題数をこなすまでループ。
    cout << "\n\n残り" << num - i <<"問\n";
    
    srand((unsigned)time(NULL));
    int opr = rand()%3;
    int a = rand()%99 + 1;
    int b = rand()*2%9 + 1;
    if(b == 0){b++;}//bの値に何故か0やマイナスが登場するので。
    else if(b < 0){b = -b;}
    
    if(opr == 0){
      x = a + b;
      cout << a << " + " << b << " = ";
      cin >> ans;
      jud(x, ans);
    }
    else if(opr == 1){
      x = a - b;
      cout << a << " - " << b << " = ";
      cin >> ans;
      jud(x, ans);
    }
    else{
      x = a * b;
      cout << a << " × " << b << " = ";
      cin >> ans;
      jud(x, ans);
    }
  }
  ftime = time(NULL);
  
  cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
       << "1問あたりにかかった平均時間:" << (ftime - stime)/num << "秒\n"
       << "\nお疲れ様でした。\n";
  return 0;
}
