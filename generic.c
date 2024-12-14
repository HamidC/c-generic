#include <stdio.h>
#include <stdbool.h>

#define typeof(x) _Generic(x, bool: BOOL, char: CHAR, int: INT, long: LONG, float: FLOAT, double: DOUBLE, void*: VOIDPTR, default: OTHER)
#define sum(a, b) genericSum(&a, typeof(a), &b, typeof(b))

enum Type {
	OTHER,
	INT,
	SHORT,
	LONG,
	CHAR,
	BOOL,
	FLOAT,
	DOUBLE,
	VOIDPTR
};

double toDouble(void* value, enum Type type);
double genericSum(void* a, enum Type a_t, void* b, enum Type b_t);

void main()
{
	int a = 5;
	char b = '9';
	bool c = true;
	float d = 3.14;
	double e = 3.14;
	char* g = "145";
	int f = -3;

	printf("%d + '%c' = %lf\n", a, b, sum(a, b));
	printf("%s + %f = %lf\n", c ? "true" : "false", d, sum(c, d));
	printf("%lf + %d = %lf\n", e, f, sum(e, f));
	//printf("\"%s\"\n", g);
	
	return;
}

double genericSum(void* a, enum Type a_t, void* b, enum Type b_t)
{
	double x = toDouble(a, a_t);
	double y = toDouble(b, b_t);
	
	return x + y;
}

double toDouble(void* value, enum Type type)
{
	double result = 0;
	
	switch(type)
	{
		case BOOL:
			result = *(bool*)value;
			break;
		case CHAR:
			if (*(char*)value >= 48 && *(char*)value <= 57)
				result = *(char*)value - 48;
			break;
		case INT:
			result = *(int*)value;
		case LONG:
			result = *(long*)value;
			break;
		case FLOAT:
			result = *(float*)value;
			break;
		case DOUBLE:
			result = *(double*)value;
			break;
	}
	
	return result;
}