#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
  int com;
  int play;
  int gros = 0;
  int win = 0;
  int rate;
  while(1){
    srand(time(NULL));
    com = rand()%3 +1;
    rate = win*100/gros;

    printf("----------------------------------------\nグーなら1、チョキなら2、パーなら3を入力\n");
    scanf("%d", &play);
    


  }





}
