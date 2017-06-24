#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
  int com;
  char getp;
  int play;
  int gros = 0;
  int win = 0;
  int rate;

  while(1){
    srand(time(NULL));
    com = rand()%3;
    gros = gros+1;
    rate = win*100/gros;
    getp = 'a';

    printf("========================================\n\nグーなら1、チョキなら2、パーなら3を入力\n(終了するにはeを入力)\n");
    getp = getchar();
    if(getp == '1' || getp == 'g'){
      play = 0;
    }
    else if(getp == '2' || getp == 'c'){
      play = 1;
    }
    else if(getp == '3' || getp == 'p'){
      play = 2;
    }
    else if(getp == 'w'){
      if(com == 0){
        play = 2;
      }
      else if(com == 1){
        play = 0;
      }
      else if(com == 2){
        play = 1;
      }
    }
    else if(getp == 'l'){
      if(com == 0){
        play = 1;
      }
      else if(com == 1){
        play = 2;
      }
      else if(com == 2){
        play = 0;
      }
    }
    else if(getp == 'd'){
      play = com;
    }
    else if(getp == 'e'){
      printf("\n<<お疲れ様でした>>\n\n========================================\n");
      break;
    }
    else{
      printf("\n<<あなたの反則負け>>\n\n========================================\n");
      break;      
    }
    getp = getchar();
    
    if(com == 0 && play == 0){
      printf("\ncom:グー\nあなた:グー\n\n<<あいこ>>\n\n");
      printf("試行回数:%d\n勝った回数:%d\n勝率:%d％\n\n========================================\n", gros, win, rate);
    }
    else if(com == 0 && play == 1){
      printf("\ncom:グー\nあなた:チョキ\n\n<<あなたの負け>>\n\n");
      printf("試行回数:%d\n勝った回数:%d\n勝率:%d％\n\n========================================\n", gros, win, rate);
    }
    else if(com == 0 && play == 2){
      win = win+1;
      rate = win*100/gros;
      printf("\ncom:グー\nあなた:パー\n\n<<あなたの勝ち>>\n\n");
      printf("試行回数:%d\n勝った回数:%d\n勝率:%d％\n\n========================================\n", gros, win, rate);
    }
    else if(com == 1 && play == 1){
      printf("\ncom:チョキ\nあなた:チョキ\n\n<<あいこ>>\n\n");
      printf("試行回数:%d\n勝った回数:%d\n勝率:%d％\n\n========================================\n", gros, win, rate);
    }
    else if(com == 1 && play == 2){
      printf("\ncom:チョキ\nあなた:パー\n\n<<あなたの負け>>\n\n");
      printf("試行回数:%d\n勝った回数:%d\n勝率:%d％\n\n========================================\n", gros, win, rate);
    }
    else if(com == 1 && play == 0){
      win = win+1;
      rate = win*100/gros;
      printf("\ncom:チョキ\nあなた:グー\n\n<<あなたの勝ち>>\n\n");
      printf("試行回数:%d\n勝った回数:%d\n勝率:%d％\n\n========================================\n", gros, win, rate);
    }
    if(com == 2 && play == 2){
      printf("\ncom:パー\nあなた:パー\n\n<<あいこ>>\n\n");
      printf("試行回数:%d\n勝った回数:%d\n勝率:%d％\n\n========================================\n", gros, win, rate);
    }
    else if(com == 2 && play == 0){
      printf("\ncom:パー\nあなた:グー\n\n<<あなたの負け>>\n\n");
      printf("試行回数:%d\n勝った回数:%d\n勝率:%d％\n\n========================================\n", gros, win, rate);
    }
    else if(com == 2 && play == 1){
      win = win+1;
      rate = win*100/gros;
      printf("\ncom:パー\nあなた:チョキ\n\n<<あなたの勝ち>>\n\n");
      printf("試行回数:%d\n勝った回数:%d\n勝率:%d％\n\n========================================\n", gros, win, rate);
    }
  }
  return 0;
}
