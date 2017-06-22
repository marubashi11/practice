#include <stdio.h>
int main(void){
	float num[2];
	printf("x = ");
	scanf("%f", &num[0]);
	printf("y = ");
	scanf("%f", &num[1]);
	printf("\nsum = %f\n", num[0]+num[1]);
	printf("dif = %f\n", num[0]-num[1]);
	printf("pro = %f\n", num[0]*num[1]);
	printf("quo = %f\n", num[0]/num[1]);

	return 0;
}
