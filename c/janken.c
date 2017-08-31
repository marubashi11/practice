#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

	int com;
	char inp;
    char trush;
    int play;
	int gros = 0;
	int win = 0;
	float rate;
    
	while(1){
		srand(time(NULL));
		com = rand()%3 +1;
		gros = gros+1;
		rate = win*100/gros;

		printf("--------------------\nグーなら1(g)、チョキなら2(c)、パーなら3(p)を入力\n");
		scanf("%c", &inp);

		if (inp != '1' && inp != '2' && inp != '3' && inp != 'g' && inp != 'c' && inp != 'p'){
          while(inp != '1' && inp != '2' && inp != '3' && inp != 'g' && inp != 'c' && inp != 'p'){
			printf("あなたの反則負け\n試行回数:%d\n勝った回数:%d\n勝率:%f\n\nグーなら1(g)、チョキなら2(c)、パーなら3(p)を入力\n", gros, win, rate);
            inp = trush;
            scanf("%c", &inp);
          }
		}
        else{
          if(inp == '1' || inp == 'g'){
            play = 1;
          }
          else if(inp == '2' || inp == 'c'){
            play = 2;
          }
          else if(inp == '3' || inp == 'p'){
            play = 3;
          }
        }
        
		if(com == play){
			printf("あいこ\n\n");
			printf("試行回数:%d\n勝った回数:%d\n勝率:%f\n--------------------\n", gros, win, rate);
		}
		else if(com == 1 && play == 2){
			printf("あなたの負け\n\ncom:グー\nあなた:チョキ\n\n");
			printf("試行回数:%d\n勝った回数:%d\n勝率:%f％\n--------------------\n", gros, win, rate);
		}
		else if(com == 1 && play == 3){
			win = win+1;
			rate = win*100/gros;
			printf("あなたの勝ち\n\ncom:グー\nあなた:パー\n\n");
			printf("試行回数:%d\n勝った回数:%d\n勝率:%f％\n--------------------\n", gros, win, rate);
		}
		else if(com == 2 && play == 3){
			printf("あなたの負け\n\ncom:チョキ\nあなた:パー\n\n");
			printf("試行回数:%d\n勝った回数:%d\n勝率:%f％\n--------------------\n", gros, win, rate);
		}
		else if(com == 2 && play == 1){
			win = win+1;
			rate = win*100/gros;
			printf("あなたの勝ち\n\ncom:チョキ\nあなた:グー\n\n");
			printf("試行回数:%d\n勝った回数:%d\n勝率:%f％\n--------------------\n", gros, win, rate);
		}
		else if(com == 3 && play == 1){
			printf("あなたの負け\n\ncom:パー\nあなた:グー\n\n");
			printf("試行回数:%d\n勝った回数:%d\n勝率:%f％\n--------------------\n", gros, win, rate);
		}
		else if(com == 3 && play == 2){
			win = win+1;
			rate = win*100/gros;
			printf("あなたの勝ち\n\ncom:パー\nあなた:チョキ\n\n");
			printf("試行回数:%d\n勝った回数:%d\n勝率:%f％\n--------------------\n", gros, win, rate);
		}
	}

	return 0;
}
