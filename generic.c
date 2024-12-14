#include <stdio.h>
#include <stdbool.h>

#define typeof(x) _Generic(x, bool: BOOL, char: CHAR, int: INT, long: LONG, float: FLOAT, double: DOUBLE, char*: CHARPTR, void*: VOIDPTR, default: OTHER)
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
	CHARPTR,
	VOIDPTR
};

double parseString(void* value);
double toDouble(void* value, enum Type type);
double genericSum(void* a, enum Type a_t, void* b, enum Type b_t);

void main()
{
	int a = 5;
	char b = '9';
	bool c = true;
	float d = 3.14;
	double e = 3.14;
	int f = -3;
	char* g = "145";
	char* h = "-10.514";

	printf("%d + '%c' = %lf\n", a, b, sum(a, b));
	printf("%s + %f = %lf\n", c ? "true" : "false", d, sum(c, d));
	printf("%lf + %d = %lf\n", e, f, sum(e, f));
	printf("\"%s\" + \"%s\" = %lf\n", g, h, sum(g, h));

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
		case CHARPTR:
			result = parseString(value);
			break;
	}
	
	return result;
}

double parseString(void* value)
{
	double result = 0;
	int index = 0;
	char select = 0;
	bool isMinus = false;
	bool isDecimal = false;
	double fraction = 0;
	int decimalPoints = 0;
	
	uintptr_t ptr = *(uintptr_t*)value;
	char* string = (char*)ptr;
	
	do
	{
		select = *(string + index);
		
		if (index++ == 0 && select == '-')
		{
			isMinus = true;
			continue;
		}
		if (select == '.')
		{
			if (isDecimal)
			{
				printf("Invalid number, can't have two decimal points.\n");
				return 0;
			}
			
			isDecimal = true;
			continue;
		}
		
		if (select >= '0' && select <= '9')
		{
			if (isDecimal)
			{
				decimalPoints++;
				fraction *= 10;
				fraction += select - '0';
			}
			else
			{
				result *= 10;
				result += select - '0';
			}
		}
		else if (select != 0)
		{
			printf("Invalid digit: %c\n", select);
			return 0;
		}
	}
	while(select > 0);
	
	if (isDecimal)
	{
		for(int i = 0; i < decimalPoints; i++)
			fraction /= 10;
		
		result += fraction;
	}
	
	if (isMinus)
		result *= -1;
	
	return result;
}