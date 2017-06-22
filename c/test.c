#include <stdio.h>

int main(void)
{
	char var1;
	var1 = 'A';
	
	int var2;
	var2 = 22;

	float var3;
	var3 = 33.33;

	double var4;
	var4 = 44.444444;
	
	printf("charは%cなどの文字列\nintは%dなどの整数\nfloatは%fなどの小数を含む数字\ndoubleは%fなどのもっと長い小数\nを変数として格納できる!\n", var1, var2, var3,var4);

	return 0;
}
