#include <stdio.h>

int main(void){
  
  char word[30];
  char hold;
  int i;
  
  printf("\n並べ替えたい文字列を入力:");
  for(i = 0 ; i < 30 && word[i-1] != '\n' ; i++){
    word[i] = getchar();
  }
  if(word[i-1] = '\n') word[i-1] = '\0';
  printf("\n入力した文字列は\"%s\"\n", word);
  for(int rep = 0 ; rep < 30 ; rep++){
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
