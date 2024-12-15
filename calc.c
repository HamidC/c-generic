#define GNAME_PASTER(x, y) x ## _ ## y
#define GNAME_EVALUATOR(x, y) GNAME_PASTER(x, y)
#define GNAME(n) GNAME_EVALUATOR(T, n)

T
GNAME(add)(T a, T b) {
	return a + b;
}

T
GNAME(mul)(T a, T b) {
	return a * b;
}