// Since the graph is relatively small and sparse, we can use Bellman-ford
// 
// slower than dijkstra of course, but less code complexity
#include <cstdio>

enum {NORTH, EAST, WEST, SOUTH, SIZE = 48, MAX = 0x3fffffff};

static int S[SIZE][SIZE], W[SIZE][SIZE], T[SIZE][SIZE];

// wait time to cross north-south 
static int
waitns(int cur, int s, int w, int t)
{
	cur = ((cur - t) % (s + w) + s + w) % (s + w);
	return cur < s ? 0 : s + w - cur;
}

// wait time to cross west-east
static int
waitwe(int cur, int s, int w, int t)
{
	cur = ((cur - t) % (s + w) + s + w) % (s + w);
	return cur < s ? s - cur : 0;
}

static inline int odd(int x) { return x & 1; }
static inline int even(int x) { return !odd(x); }

// time used to go a specified direction
static int
delta(int r, int c, int cur, int d)
{
	int s = S[r/2][c/2], w = W[r/2][c/2], t = T[r/2][c/2];
	switch (d) {
	case NORTH:
		if (odd(r))
			return waitns(cur, s, w, t) + 1;
		return 2;
	case SOUTH:
		if (even(r))
			return waitns(cur, s, w, t) + 1;
		return 2;
	case WEST:
		if (odd(c))
			return waitwe(cur, s, w, t) + 1;
		return 2;
	default: // EAST
		if (even(c))
			return waitwe(cur, s, w, t) + 1;
		return 2;
	}
	return -1; // shouldnt reach here
}

static int
doit()
{
	static int best[SIZE][SIZE];
	int n, m;

	// input
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			scanf("%d%d%d", &S[i][j], &W[i][j], &T[i][j]);
			T[i][j] %= S[i][j] + W[i][j];
		}

	// init
	n *= 2;
	m *= 2;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			best[i][j] = MAX;
	best[n-1][0] = 0;

	// run
	// north, east, west, south
	static int const dir[4][2] = {{-1,0}, {0,1}, {0,-1}, {1,0}};
	for (int i = 0; i < 4 * n * m; i++) {
		bool updated = false;
		for (int j = 0; j < n * m; j++) {
			int r = j / m, c = j % m;
			for (int k = 0; k < 4; k++) {
				int nr = r + dir[k][0], nc = c + dir[k][1];
				if (nr < 0 || nc < 0 || nr >= n || nc >= m)
					continue;
				int t = best[r][c];
				t += delta(r, c, t, k);
				if (t < best[nr][nc]) {
					best[nr][nc] = t;
					updated = true;
				}
			}
		}
		if (!updated)
			break;
	}
	return best[0][m-1];
}

int
main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		printf("Case #%d: %d\n", i, doit());
	return 0;
}
