// shortest path -- Dijkstra
#include <cstdio>
#include <queue>

using namespace std;

enum {NORTH, EAST, WEST, SOUTH, SIZE = 48, MAX = 0x7fffffff};

struct info {
	int r, c; // position
	int cur; // weight: current time
	info(int _r, int _c, int _cur) : r(_r), c(_c), cur(_cur) {}
	bool operator <(const info &ano) const
	{
		return cur > ano.cur;
	}
};

static int S[SIZE][SIZE], W[SIZE][SIZE], T[SIZE][SIZE];

// wait time to cross north-south 
static int
waitns(int cur, int s, int w, int t)
{
	if (cur < t) {
		if (t - cur <= w)
			return t - cur;
		return 0;
	} else {
		cur = (cur - t) % (s + w);
		if (cur < s)
			return 0;
		return s + w - cur;
	}
}

// wait time to cross west-east
static int
waitwe(int cur, int s, int w, int t)
{
	if (cur < t) {
		if (t - cur <= w)
			return 0;
		return t - cur - w;
	} else {
		cur = (cur - t) % (s + w);
		if (cur < s)
			return s - cur;
		return 0;
	}
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
	static bool out[SIZE][SIZE];
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
		for (int j = 0; j < m; j++) {
			out[i][j] = false;
			best[i][j] = MAX;
		}
	priority_queue<info> pq;
	pq.push(info(n-1, 0, 0));
	best[n-1][0] = 0;

	// run
	while (!pq.empty()) {
		info now = pq.top();
		int r = now.r, c = now.c, cur = now.cur;
		if (r == 0 && c == m - 1)
			return cur;
		pq.pop();
		if (out[r][c])
			continue;
		out[r][c] = true;
		// north, east, west, south
		static int const dir[4][2] = {{-1,0}, {0,1}, {0,-1}, {1,0}};
		for (int i = 0; i < 4; i++) {
			int nr = r + dir[i][0], nc = c + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m)
				continue;
			int ncur = cur + delta(r, c, cur, i);
			if (ncur < best[nr][nc]) {
				//printf("(%d,%d) %d => (%d,%d) %d\n", r, c, cur, nr, nc, ncur);
				best[nr][nc] = ncur;
				pq.push(info(nr, nc, ncur));
			}
		}
	}
	return -1; // shouldnt reach here
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
