/*----------------------------------------------------------------------------*/
/* Title:   calc.c                                                           */
/*----------------------------------------------------------------------------*/
/* Calclulator Program                                                        */
/* To be used in the makefile                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include "mcalc.h"

int main(){
	/* Add your code ' */
	int a, b;
	char operator;

	while(scanf("%d %c %d", &a, &operator, &b) == 3)
	{
		switch (operator) {
		case '+':
			printf("%d\n", (add(a, b)));
			break;

		case '-':
			printf("%d\n", (sub(a, b)));
			break;

		case '*':
			printf("%d\n", (mul(a, b)));
			break;

		case '/':
			printf("%d\n", (div(a, b)));
			break;

		case '%':
			printf("%d\n", (mod(a, b)));
			break;

		default:
			printf("Invalid\n");
			break;
		}
	}
	return 0;
}