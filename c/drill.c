#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

  int q1;
  int q2;
  int shuf;
  int col;
  int ans;
  int No = 0;
  int end;
  int t1;
  int t2;
 
  
  printf("希望する問題数を入力:");
  scanf("%d", &end);

  t1 = time(NULL); 
  
  while(No < end){
    srand(time(NULL));
    q1 = rand()%100;
    q2 = rand()*2%10;
    shuf = rand()%3;

    printf("\n残り問題数:%d\n\n", end-No);

    if(shuf == 0){
      printf("%d + %d = ", q1, q2);
      col = q1+q2;
      scanf("%d", &ans);
      if(ans != col){
	while(ans != col){
	  printf("\n\nやり直し!\n");
	  scanf("%d", &ans);
	}
      }
      else if(ans == col){
	printf("\n\n正解!!\n");
	No = No+1;
      }
	}
    else if(shuf == 1){
      printf("%d - %d = ", q1, q2);
      col = q1-q2;
      scanf("%d", &ans);
      if(ans != col){
	while(ans != col){
	  printf("\n\nやり直し!\n");
	  scanf("%d", &ans);
	}
      }
      else if(ans == col){
	printf("\n\n正解!!\n");
	No = No+1;
      }
	}
    else if(shuf == 2){
      printf("%d × %d = ", q1, q2);
      col = q1*q2;
      scanf("%d", &ans);
      if(ans != col){
	while(ans != col){
	  printf("\n\nやり直し!\n");
	  scanf("%d", &ans);
	  }
      }
      else if(ans == col){
	printf("\n\n正解!!\n");
	No = No+1;
      }
    }
}
  t2 = time(NULL);
  printf("\n\nかかった時間:%d秒\n", t2-t1);
  printf("1問あたりの平均:%d秒\n", (t2-t1)/end);
  
  return 0;
}
