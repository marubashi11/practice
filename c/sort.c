#include <stdio.h>

int main(void){
  
  char word[30];
  char hold;
  int i;
  int rep;
  
  printf("\n並べ替えたい文字列を入力:");
  scanf("%s", word);
  printf("\n入力した文字列は\"%s\"\n", word);
  for(rep = 0 ; rep < 100 ; rep++){
    for(i = 0 ; word[i+1] != 0 ; i++){
      if(word[i] > word[i+1]){
        hold = word[i];
        word[i] = word[i+1];
        word[i+1] = hold;
      }
    }
  }
  printf("アルファベット順に並べ替えると\"%s\"\n\n", word);
  
  return 0;
}
