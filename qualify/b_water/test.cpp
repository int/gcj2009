#include <cstdio>
#include <cstring>

static int	H, W, num[104][104];
static char	label[104][104];

static inline int
flow(int r, int c, char x)
{
	if (label[r][c])
		return 0;
	static const int dir[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
	int rr = -1, cc, best = num[r][c];
	for (int i = 0; i < 4; i++) {
		int nr = r + dir[i][0], nc = c + dir[i][1];
		if (nr < 0 || nr >= H || nc < 0 || nc >= W)
			continue;
		if (num[nr][nc] < best) {
			best = num[nr][nc];
			rr = nr;
			cc = nc;
		}
	}
	if (rr == -1) {
		// new sink
		label[r][c] = x;
		return 1;
	}
	int ret = flow(rr, cc, x);
	label[r][c] = label[rr][cc];
	return ret;
}

int
main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d%d", &H, &W);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				scanf("%d", &num[i][j]);

		memset(label, 0, sizeof(label));
		char x = 'a';
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				x += flow(i, j, x);

		printf("Case #%d:\n", t);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				printf("%c%c", label[i][j], j == W - 1 ? '\n' : ' ');
	}
	return 0;
}
