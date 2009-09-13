#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

static void
doit()
{
	char num[40];
	scanf("%s", num);
	vector<int> d;
	for (int i = 0; num[i]; i++)
		d.push_back(num[i] - '0');
	if (!next_permutation(d.begin(), d.end())) {
		d.push_back(0);
		sort(d.begin(), d.end());
		if (d[0] == 0) {
			for (int i = 1; ; i++)
				if (d[i]) {
					swap(d[0], d[i]);
					break;
				}
		}
	}
	for (int i = 0; i < d.size(); i++)
		printf("%d", d[i]);
	printf("\n");
}

int
main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		printf("Case #%d: ", i);
		doit();
	}
	return 0;
}
