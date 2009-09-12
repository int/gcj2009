// Graph: from a node (n, b), can it reach (1, b)?
// O(largest_n * 10)
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

static char	oksave[1 << 24][11];

static inline int
happy(int n, int b)
{
	int r = 0;
	while (n) {
		int t = n % b;
		r += t * t;
		n /= b;
	}
	return r;
}

static inline int
ok(int n, int b)
{
	if (n == 1)
		return (oksave[n][b] = 2);
	if (oksave[n][b] > 0)
		return oksave[n][b];
	oksave[n][b] = 1; // mark
	return oksave[n][b] = ok(happy(n, b), b);
}

static int
get()
{
	static char line[80];
	static int base[10];
	fgets(line, sizeof(line), stdin);
	int n = 0;
	for (char *p = strtok(line, " \n"); p; p = strtok(NULL, " \n"))
		base[n++] = atoi(p);
	for (int i = 2; ; i++) {
		int j;
		for (j = 0; j < n; j++)
			if (ok(i, base[j]) == 1)
				break;
		if (j == n)
			return i;
	}
	return -1;
}

int
main()
{
	int t;
	scanf("%d ", &t);
	for (int i = 1; i <= t; i++)
		printf("Case #%d: %d\n", i, get());
	return 0;
}
