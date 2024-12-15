#include <stdio.h>

#define T int
#include "calc.c"

#undef T
#define T float
#include "calc.c"

void
main(void) {
	printf("int: 5 + 6 = %d\n", int_add(5, 6));
	printf("float: 5.1 + 6.98 = %f\n", float_add(5.1, 6.98));
	printf("float: 5.1 * 6.98 = %f\n", float_mul(5.1, 6.98));
	return;
}