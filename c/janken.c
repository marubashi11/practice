#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

	int com;
	int play;
	int gros = 0;
	int win = 0;
	float rate;
	while(1){
		srand(time(NULL));
		com = rand()%3 +1;
		gros = gros+1;
		rate = win*100/gros;

		printf("--------------------\nグーなら1、チョキなら2、パーなら3を入力\n");
		scanf("%d", &play);

		if (play != 1 && play != 2 && play != 3){
			gros = gros-1;
			printf("失格!!\n--------------------\n");
			break;
		}
		else if(com == play){
			printf("あいこ\n\n");
			printf("試行回数:%d\n勝った回数:%d\n勝率:%f％\n--------------------\n", gros, win, rate);
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
