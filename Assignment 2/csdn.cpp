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

int pos[110100];
char str[1300];

class SuffixArray
{
    public:
        static const int N = 110100;
        int init[N];
        int X[N];
        int Y[N];
        int Rank[N];
        int sa[N];
        int height[N];
        int buc[N];
        bool vis[1200];
        int size;
        set <string> st;

        void clear()
        {
            size = 0;
        }

        void insert(int n)
        {
            init[size++] = n;
        }

        bool cmp(int *r, int a, int b, int l)
        {
            return (r[a] == r[b] && r[a + l] == r[b + l]);
        }

        void getsa(int m = 256)
        {
            init[size] = 0;
            int l, p, *x = X, *y = Y, n = size + 1;
            for (int i = 0; i < m; ++i)
            {
                buc[i] = 0;
            }
            for (int i = 0; i < n; ++i)
            {
                ++buc[x[i] = init[i]];
            }
            for (int i = 1; i < m; ++i)
            {
                buc[i] += buc[i - 1];
            }
            for (int i = n - 1; i >= 0; --i)
            {
                sa[--buc[x[i]]] = i;
            }
            for (l = 1, p = 1; l <= n && p < n; m = p, l *= 2)
            {
                p = 0;
                for (int i = n - l; i < n; ++i)
                {
                    y[p++] = i;
                }
                for (int i = 0; i < n; ++i)
                {
                    if (sa[i] >= l)
                    {
                        y[p++] = sa[i] - l;
                    }
                }
                for (int i = 0; i < m; ++i)
                {
                    buc[i] = 0;
                }
                for (int i = 0; i < n; ++i)
                {
                    ++buc[x[y[i]]];
                }
                for (int i = 1; i < m; ++i)
                {
                    buc[i] += buc[i - 1];
                }
                for (int i = n - 1; i >= 0; --i)
                {
                    sa[--buc[x[y[i]]]] = y[i];
                }
                int i;
                for (swap(x, y), x[sa[0]] = 0, p = 1, i = 1; i < n; ++i)
                {
                    x[sa[i]] = cmp(y, sa[i - 1], sa[i], l) ? p - 1 : p++;
                }
            }
        }

        void getheight()
        {
            int h = 0, n = size;
            for (int i = 0; i <= n; ++i)
            {
                Rank[sa[i]] = i;
            }
            height[0] = 0;
            for (int i = 0; i < n; ++i)
            {
                if (h > 0)
                {
                    --h;
                }
                int j = sa[Rank[i] - 1];
                for (; i + h < n && j + h < n && init[i + h] == init[j + h]; ++h);
                height[Rank[i] - 1] = h;
            }
        }

        bool check(int k, int n)
        {
            int cnt = 1;
            memset(vis, 0, sizeof(vis));
            vis[pos[sa[1]]] = 1;
            for (int i = 1; i < size; ++i)
            {
                if (height[i] >= k)
                {
                    if (pos[sa[i + 1]] != -1 && !vis[pos[sa[i + 1]]])
                    {
                        ++cnt;
                        vis[pos[sa[i + 1]]] = 1;
                    }
                }
                else
                {
                    if (cnt > n / 2)
                    {
                        return 1;
                    }
                    memset(vis, 0, sizeof(vis));
                    cnt = 1;
                    if (pos[sa[i + 1]] != -1)
                    {
                        vis[pos[sa[i + 1]]] = 1;
                    }
                }
            }
            return 0;
        }

        void solve(int n)
        {
            int l = 1, r = size, mid;
            int ans = 0;
            while (l <= r)
            {
                mid = (l + r) >> 1;
                if (check(mid, n))
                {
                    ans = mid;
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
            if (!ans)
            {
                printf("?\n");
            }
            else
            {   
                st.clear();
                int cnt = 1;
                memset(vis, 0, sizeof(vis));
                vis[pos[sa[1]]] = 1;
                for (int i = 0; i < size; ++i)
                {
                    if (height[i] >= ans)
                    {
                        if (!vis[pos[sa[i + 1]]])
                        {
                            ++cnt;
                            vis[pos[sa[i + 1]]] = 1;
                        }
                        for (int j = sa[i + 1]; j < sa[i + 1] + ans; ++j)
                        {
                            str[j - sa[i + 1]] = (char)init[j];
                        }
                        str[ans] = '\0';
                        st.insert(str);
                    }
                    else if (height[i] < ans)
                    {
                        if (cnt > n / 2)
                        {
                            set <string> :: iterator it;
                            for (it = st.begin(); it != st.end(); ++it)
                            {
                                printf("%s\n", it -> c_str());
                            }
                        }
                        st.clear();
                        cnt = 1;
                        memset(vis, 0, sizeof(vis));
                        vis[pos[sa[i + 1]]] = 1;
                    }
                }
            }
        }
}SA;

int main()
{
    int n;
    bool flag = 0;
    while (~scanf("%d", &n), n)
    {
        int maxs = 0;
        SA.clear();
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%s", str);
            int len = strlen(str);
            for (int j = 0; j < len; ++j)
            {
                SA.insert((int)str[j]);
                maxs = max(maxs, (int)str[j]);
                pos[cnt++] = i;
            }
            SA.insert((int)('z') + i);
            pos[cnt++] = -1;
        }
        if (flag)
        {
            printf("\n");
        }
        else
        {
            flag = 1;
        }
        SA.getsa();
        SA.getheight();
        SA.solve(n);
    }
    return 0;
}