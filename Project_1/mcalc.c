/*----------------------------------------------------------------------------*/
/* Title:   mcal.c                                                           */
/*----------------------------------------------------------------------------*/
/* File that contains the definitions of all functions                       */
/* To be used in the makefile                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "mcalc.h"

/*
Add your code that contains the
definitions of all the functions
declared in "mcalc.h"
*/

int add(int x, int y) {
    return x + y;
}

int sub(int x, int y) {
    return x - y;
}

int mul(int x, int y) {
    return x * y;
}

int div(int x, int y) {
    return x / y;
}

int mod(int x, int y) {
    return x % y;
}
