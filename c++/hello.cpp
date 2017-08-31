#include <iostream>
//c++でのヘッダ。iostremは標準的な入出力に必要。
using namespace std;
/*
これを書いておくと命令ごとに"std::"と書くのを省略できる。
この"std::"は同じ名前の命令を区別するための苗字のようなもの。
*/

int main (){
  cout << "Hello, c++ world!\n" << "Nice to meet you.\n";
/*
coutは画面のこと。"a << b"はbをaに出力することを表す。
今回は同じ"cout"への出力なので上のように続けて書いてよい。
*/
return 0;
}
