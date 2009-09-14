// shortest path -- state: (position, value).
//
// this implemetation is a plain Dijkstra using STL priority queue
// non-optimized -- a lot of (maybe unnecessary) copy.
//
// can be faster if you use a specilized heap, cut STL sh1t, or adopt
// a better/advanced algorithm like A* -- but that would add more code
// complexity.
//
// so this version is not _very_ fast but it's fast _enough_
// g++ -O2  -- 30s for large input
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct info {
	int p, v, s; // postion, val, steps
	string z; // path
	info(int _p, int _v, int _s, string &_z) : p(_p), v(_v), s(_s), z(_z) {}
	bool operator <(const info &ano) const
	{
		if (s != ano.s)
			return s > ano.s; // first by steps
		return z > ano.z; // then the path string
	}
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
	vector<map<int,bool> > out(24*24);
	vector<map<int,int> > best(24*24);
	vector<map<int,string> > path(24*24);
	priority_queue<info> pq;
	string e = "";
	pq.push(info(w * w, 0, 0, e));
	best[w * w][0] = 0;
	path[w * w][0] = e;
	int left = q;

	// run
	while (!pq.empty()) {
		info now = pq.top();
		int p = now.p, v = now.v, s = now.s + 1;
		string &z = now.z;
		pq.pop();

		if (out[p][v])
			continue;
		out[p][v] = true;

		//cout << "now: " << z << endl;
		if (vals.find(v) != vals.end() && vals[v] == "") { // got one?
			vals[v] = z;
			//cout << "got: " << v << "=" << z << endl;
			if (--left == 0)
				break;
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
			if (best[np].find(nv) == best[np].end() ||
			    s < best[np][nv] ||
			    (s == best[np][nv] && z < path[np][nv])) {
				string zz = z;
				zz += x;
				//cout << z << " to " << zz << endl;
				best[np][nv] = s;
				path[np][nv] = zz;
				pq.push(info(np, nv, s, zz));
			}
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
