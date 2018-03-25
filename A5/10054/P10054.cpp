#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int graph[2000][2000];
int indegree[55];

void dfs(int i) {
	for (int j = 1; j <= 50; j++) {
		if (graph[i][j] > 0) {
			graph[i][j]--;
			graph[j][i]--;
			dfs(j);
			printf("%d %d\n", j, i);
		}
	}
}
int main(int argc, char const *argv[])
{
	/* code */
	int test_cases = 0;
	int Tcase = 1;
	scanf("%d", &test_cases);
	while (test_cases--) {
		int n = 0;
		scanf("%d", &n);

		memset(graph, 0, sizeof(graph));
		memset(indegree, 0, sizeof(indegree));
		
		for (int i = 0; i < n; i++) {
			int u = 0, v = 0;
			scanf("%d %d", &u, &v);
			indegree[u]++;
			indegree[v]++;
			graph[u][v]++;
			graph[v][u]++;
		}
		bool valid = true;
		for (int i = 1; i <= 50; i++) {
			if (indegree[i] & 1) {
				valid = false;
				break;
			}
		}
		if (Tcase >= 2) {
			cout << endl;
		}

		printf("Case #%d\n",Tcase++);

		if (!valid) {
			printf("some beads may be lost\n");
		} else {
			for (int i = 1; i <= 50; i++) {
				if (indegree[i] > 0) {
					dfs(i);
					break;
				}
			}
		}
	}
	return 0;
}