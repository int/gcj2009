#include <cstdio>
#include <cstring>

int
main()
{
	int N;
	scanf("%d ", &N);

	const char *p = " welcome to code jam\n";
	const int np = strlen(p + 1);
	static int dp[504][24];

	for (int t = 1; t <= N; t++) {
		printf("Case #%d: ", t);
		static char s[504];
		fgets(s + 1, sizeof(s) - 1, stdin);
		int ns = strlen(s + 1);

		for (int i = 0; i <= ns; i++)
			for (int j = 0; j <= np; j++)
				dp[i][j] = j == 0 ? 1 : 0;

		for (int i = 1; i <= ns; i++)
			for (int j = 1; j <= np; j++) {
				dp[i][j] = dp[i - 1][j];
				if (s[i] == p[j]) {
					dp[i][j] += dp[i - 1][j - 1];
					dp[i][j] %= 10000;
				}
			}

		printf("%04d\n", dp[ns][np]);
	}
	return 0;
}
