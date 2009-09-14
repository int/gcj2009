#include <cstdio>

static int	id[104], best[104][104];

static int f(int i, int j)
{
	if (i == j)
		return 0;
	int &r = best[i][j];
	if (r >= 0)
		return r;
	r = 0x3fffffff;
	for (int k = i; k < j; k++) {
		int now = f(i, k) + f(k + 1, j) + id[j + 1] - id[i] - 2;
		if (now < r)
			r = now;
	}
	return r;
}

static int
get()
{
	int p, q;
	scanf("%d%d", &p, &q);
	id[0] = 0;
	for (int i = 1; i <= q; i++)
		scanf("%d", &id[i]);
	id[q + 1] = p + 1;
	for (int i = 0; i <= q; i++)
		for (int j = 0; j <= q; j++)
			best[i][j] = -1;
	return f(0, q);
}

int
main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
		printf("Case #%d: %d\n", i, get());
	return 0;
}
