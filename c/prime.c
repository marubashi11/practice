#include <stdio.h>

int main(void){

  int lim;
  int nn;
  int scan;
  int jud = 0;
  int k = 0;
  
  printf("好きな自然数を入力:");
  scanf("%d", &lim);

  if(lim <= 0){
    while(lim <= 0){
      printf("\n好きな'自然数'を入力:");
      scanf("%d", &lim);
    }
  }
  else if(lim == 1){
    printf("\n1以下の素数はナシ。\n");
  }
  else{

    int pri[lim];
  
    for(nn = 3 ; nn <= lim ; nn++){
      for(scan = 2 ; scan <= nn-1 ; scan++){
        if(nn%scan == 0){
          jud++;//判定。nnが素数ならjud == 0となるはず。
        }
      }
      if(jud == 0){
        pri[k] = nn;//素数を格納していく。
        k++;
      }
      jud = 0;//判定器リセット。
    }
    int end = k;//kが最大いくつかわからないので拾っておく。
  
    printf("\n%d以下の素数は{2,", lim);
    for(k = 0 ; k < end ; k++){
      printf("%d,", pri[k]);
    }
    printf("以上!}\n");
  }
  
  return 0;
}
