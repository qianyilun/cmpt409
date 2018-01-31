#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <stack>
#include <map>
#include <bitset>
#include <set>
#include <vector>

using namespace std;
int pos[110005];
char str[110005];

struct SufArray {
    int sa[110005], h[110005];
    int bucket[110005], init[110005];
    int X[110005], Y[110005], rank[110005], height[110005];
    bool visited[111];
    int size;
    set <string> hash;

    void insert(int n) {
    	init[size++] = n;
    }

    bool cmp (int *r, int a, int b, int length) {
    	return (r[a] == r[b] && r[a + length] == r[b + length]);
    }

    void getSa() {
    	int m = 256;
        init[size] = 0;
        int l, p, *x = X, *y = Y, n = size + 1;
        for (int i = 0; i < m; ++i) {
            bucket[i] = 0;
        }
        for (int i = 0; i < n; ++i) {
            ++bucket[x[i] = init[i]];
        }
        for (int i = 1; i < m; ++i) {
            bucket[i] += bucket[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            sa[--bucket[x[i]]] = i;
        }
        for (l = 1, p = 1; l <= n && p < n; m = p, l *= 2) {
            p = 0;
            for (int i = n - l; i < n; ++i) {
                y[p++] = i;
            }
            for (int i = 0; i < n; ++i) {
                if (sa[i] >= l) {
                    y[p++] = sa[i] - l;
                }
            }
            for (int i = 0; i < m; ++i) {
                bucket[i] = 0;
            }
            for (int i = 0; i < n; ++i) {
                ++bucket[x[y[i]]];
            }
            for (int i = 1; i < m; ++i) {
                bucket[i] += bucket[i - 1];
            }
            for (int i = n - 1; i >= 0; --i) {
                sa[--bucket[x[y[i]]]] = y[i];
            }
            int i;
            for (swap(x, y), x[sa[0]] = 0, p = 1, i = 1; i < n; ++i) {
                x[sa[i]] = cmp(y, sa[i - 1], sa[i], l) ? p - 1 : p++;
            }
        }
    }

    // https://www.hackerrank.com/topics/lcp-array
    // Kasai construction Algorithm in C++
    // https://pdfs.semanticscholar.org/f5e5/f365acc6f00c014c523c65efd9df6cee2606.pdf
    void getHeight() {
    	int h = 0, n = size;
        for (int i = 0; i <= n; ++i)
        {
            rank[sa[i]] = i;
        }
        height[0] = 0;
        for (int i = 0; i < n; ++i)
        {
            if (h > 0)
            {
                --h;
            }
            int j = sa[rank[i] - 1];
            for (; i + h < n && j + h < n && init[i + h] == init[j + h]; ++h);
            height[rank[i] - 1] = h;
        }
    }

    bool valid(int k, int n) {
        int count = 1;
        memset(visited, 0, sizeof(visited));
        visited[pos[sa[1]]] = 1;
        for (int i = 1; i < size; ++i) {
            if (height[i] >= k) {
                if (pos[sa[i + 1]] != -1 && !visited[pos[sa[i + 1]]]) {
                    ++count;
                    visited[pos[sa[i + 1]]] = 1;
                }
            } else {
                if (count > n / 2) {
                    return 1;
                }
                memset(visited, 0, sizeof(visited));
                count = 1;
                if (pos[sa[i + 1]] != -1) {
                    visited[pos[sa[i + 1]]] = 1;
                }
            }
        }
        return 0;
    }

    void getSolution(int n) {
        int l = 1, r = size, mid;
        int answer = 0;
        // binary search
        while (l <= r) {
            mid = (l + r) >> 1;
            if (valid(mid, n)) {
                answer = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (!answer) {
            printf("?\n");
        } else {   
            printResults(answer, n);
        }
    }

    void printResults(int answer, int n) {
        hash.clear();
        int count = 1;
        memset(visited, 0, sizeof(visited));
        visited[pos[sa[1]]] = 1;
        for (int i = 0; i < size; ++i) {
            if (height[i] >= answer) {
                if (!visited[pos[sa[i + 1]]]) {
                    ++count;
                    visited[pos[sa[i + 1]]] = 1;
                }
                for (int j = sa[i + 1]; j < sa[i + 1] + answer; ++j) {
                    str[j - sa[i + 1]] = (char)init[j];
                }
                str[answer] = '\0';
                hash.insert(str);
            } else if (height[i] < answer) {
                if (count > n / 2) {
                    set <string> :: iterator it;
                    for (it = hash.begin(); it != hash.end(); ++it) {
                        printf("%s\n", it -> c_str());
                    }
                }
                hash.clear();
                count = 1;
                memset(visited, 0, sizeof(visited));
                visited[pos[sa[i + 1]]] = 1;
            }
        }
    }
};

SufArray SA;

int main() {
	int n;
	bool flag = 0;
	while (scanf("%d", &n), n) {

		int temp = 0;

		SA.size = 0;
		int count = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%s", str);
			int length = strlen(str);
			for (int j = 0; j < length; j++) {
				SA.insert((int) str[j]);
				temp = max(temp, (int) str[j]);
				pos[count++] = i;
			}
			SA.insert((int) ('z') + i);
			pos[count++] = -1;
		}
		if (flag) {
			printf("\n");
		} else {
			flag = 1;
		}

		SA.getSa();
		SA.getHeight();
		SA.getSolution(n);
	}
	return 0;
}
