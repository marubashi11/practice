#include <stdio.h>

int main(void){

  char word[100][30];
  char hold;
  int wc;
  int i;//iは単語番号
  int j;//jは文字番号

  printf("並べたい単語の数を決定:");
  scanf("%d", &wc);
  getchar();//scanfで拾った\nを処分
  if(wc >= 100) printf("100個目の単語まで受け付けます。\n");
  
  for(i = 0 ; i <= 99 && i <= wc-1 ; i++){
    printf("\n%dつ目の単語を入力:", i+1);
  
    for(j = 0 ; j < 30 && word[i][j-1] != '\n' ; j++){
      word[i][j] = getchar();
      if(65 <= word[i][j] && word[i][j] <= 90){
        word[i][j] = word[i][j]+32;//大文字を小文字に変換
      }
    }
    if(word[i][j-1] == '\n') word[i][j-1] = '\0';
  }
  
  for(int rpt = 0 ; rpt <= 99 ; rpt++){//比較入れ替えを100回実行
    for(i = 0 ; word[i+1][0] != '\0' ; i++){//列だけを動かす
    
      for(j = 0 ; word[i][j] != '\0' && word[i+1][j] != '\0' ; j++){//文字だけを動かす
        if(word[i][j] < word[i+1][j]) break;//順番通りなので何もしない
        else if(word[i][j] > word[i+1][j] || (word[i][j+1] != '\0' && word[i+1][j+1] == '\0')){
          for(int k = 0 ; k <= 29 ; k++){
            hold = word[i][k]; 
            word[i][k] = word[i+1][k];
            word[i+1][k] = hold;
          }
          break;//順番が逆なので文字列を入れ替えて終了
        }
      }
    }
  }

  printf("\n辞書順に並べ替えると、\n");
  for(i = 0 ; i < wc ; i++){
    printf("\"%s\"\n", word[i]);
  }
  
  return 0;
}
