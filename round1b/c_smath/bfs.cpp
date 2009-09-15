// shortest path -- state: (position, value).
//
// since the graph weight is always 1, we can simply use BFS.
//
// update when same length and lexicographically smaller,
// but never need to re-push.
//
// also just record the path
// the steps are just the length of the path and we dont need to store it
//
// use less memory and faster than dijkstra.cpp
//
// g++ -O2  -- 15s for large input
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct info {
	int p, v; // postion, val;
	info(int _p, int _v) : p(_p), v(_v) {}
};

static char sq[24][24];

static void
getnext(int now, int w, vector<int> &next)
{
	if (now == w * w) { // virtual start
		for (int i = 0; i < w * w; i++)
			if (isdigit(sq[i / w][i % w]))
				next.push_back(i);
	} else {
		int r = now / w, c = now % w;
		static const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
		for (int i = 0; i < 4; i++) {
			int nr = r + dir[i][0], nc = c + dir[i][1];
			if (nr < 0 || nc < 0 || nr >= w || nc >= w)
				continue;
			next.push_back(nr * w + nc);
		}
	}
}

// same length, lexicographically smaller
static inline void
check(string &a, string &b)
{
	if (a.length() == b.length() && a < b)
		b = a;
}

static void
doit()
{
	// input
	int w, q;
	scanf("%d%d", &w, &q);
	for (int i = 0; i < w; i++)
		scanf("%s", sq[i]);

	static int num[52];
	map<int, string> vals;
	for (int i = 0; i < q; i++) {
		int v;
		scanf("%d", &v);
		num[i] = v;
		vals[v] = "";
	}

	// init
	sq[w][0] = '+'; // virtual vetex to every other vertex
	vector<map<int,string> > path(24*24);
	queue<info> que;
	que.push(info(w * w, 0));
	path[w * w][0] = "";
	int left = q;

	// run
	int ps = 0;
	while (!que.empty()) {
		info now = que.front();
		int p = now.p, v = now.v;
		string &z = path[p][v];
		int s = z.length();
		que.pop();

		if (left == 0 && s > ps)
			break;

		//cout << "now: " << z << endl;
		if (vals.find(v) != vals.end()) { // got one?
			if (vals[v] == "") { // new
				left--;
				vals[v] = z;
				ps = s;
			} else
				check(z, vals[v]);
		}

		// helpers
		int t = 0;
		char c = sq[p / w][p % w];
		if (c == '+')
			t = 1;
		else if (c == '-')
			t = -1;

		// next
		vector<int> next;
		getnext(p, w, next);
		for (int i = 0; i < next.size(); i++) {
			int np = next[i], x = sq[np / w][np % w], nv = v + t * (x - '0');
			string nz = z;
			nz += x;
			if (path[np].find(nv) == path[np].end()) { // new
				path[np][nv] = nz;
				que.push(info(np, nv));
			} else
				check(nz, path[np][nv]);
		}
	}

	for (int i = 0; i < q; i++)
		cout << vals[num[i]] << endl;
}

int
main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		printf("Case #%d: \n", i);
		doit();
	}
	return 0;
}
