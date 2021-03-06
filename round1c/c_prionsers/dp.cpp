#include <cstdio>

static int	id[104], best[104][104];

static int
get()
{
	int p, q;
	scanf("%d%d", &p, &q);
	id[0] = 0;
	for (int i = 1; i <= q; i++)
		scanf("%d", &id[i]);
	id[++q] = p + 1;
	for (int i = 0; i < q; i++)
		for (int j = 0; j < q; j++)
			best[i][j] = i == j ? 0 : p * q;
	for (int len = 2; len <= q; len++)
		for (int i = 0; i + len <= q; i++) {
			int j = i + len - 1;
			for (int k = i; k < j; k++) {
				int t = best[i][k] + best[k+1][j] + id[j+1] - id[i] - 2;
				if (t < best[i][j])
					best[i][j] = t;
			}
		}
	return best[0][q - 1];
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
