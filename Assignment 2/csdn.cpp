#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

const int MAXLEN = 200005;

struct Suffix
{

    int s[MAXLEN];
    int sa[MAXLEN], t[MAXLEN], t2[MAXLEN], c[MAXLEN], n;
    int rank[MAXLEN], height[MAXLEN];

    void build_sa(int m)
    {
        int i, *x = t, *y = t2;
        for (i = 0; i < m; i++)
            c[i] = 0;
        for (i = 0; i < n; i++)
            c[x[i] = s[i]]++;
        for (i = 1; i < m; i++)
            c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i--)
            sa[--c[x[i]]] = i;
        for (int k = 1; k <= n; k <<= 1)
        {
            int p = 0;
            for (i = n - k; i < n; i++)
                y[p++] = i;
            for (i = 0; i < n; i++)
                if (sa[i] >= k)
                    y[p++] = sa[i] - k;
            for (i = 0; i < m; i++)
                c[i] = 0;
            for (i = 0; i < n; i++)
                c[x[y[i]]]++;
            for (i = 0; i < m; i++)
                c[i] += c[i - 1];
            for (i = n - 1; i >= 0; i--)
                sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (i = 1; i < n; i++)
                x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
            if (p >= n)
                break;
            m = p;
        }
    }

    void getHeight()
    {
        int i, j, k = 0;
        for (i = 0; i < n; i++)
            rank[sa[i]] = i;
        for (i = 0; i < n; i++)
        {
            if (k)
                k--;
            if (rank[i] == 0)
                continue;
            int j = sa[rank[i] - 1];
            while (s[i + k] == s[j + k])
                k++;
            height[rank[i]] = k;
        }
    }
} gao;

const int N = 1005;

int n, l, r, id[MAXLEN];
char str[N];

bool judge(int x, int bo)
{
    set<int> vis;
    vis.insert(id[gao.sa[1]]);
    for (int i = 2; i < gao.n; i++)
    {
        while (i < gao.n && gao.height[i] >= x)
        {
            vis.insert(id[gao.sa[i]]);
            i++;
        }
        if (vis.size() * 2 > n)
        {
            if (bo == 0)
                return true;
            for (int j = 0; j < x; j++)
                printf("%c", gao.s[gao.sa[i - 1] + j]);
            printf("\n");
        }
        vis.clear();
        vis.insert(id[gao.sa[i]]);
    }
    return false;
}

void solve()
{
    if (!judge(1, 0))
    {
        printf("?\n");
        return;
    }
    l = 1;
    r++;
    while (l < r)
    {
        int mid = (l + r) / 2;
        if (judge(mid, 0))
            l = mid + 1;
        else
            r = mid;
    }
    l--;
    judge(l, 1);
}

int main()
{
    int bo = 0;
    while (~scanf("%d", &n) && n)
    {
        if (bo)
            printf("\n");
        else
            bo = 1;
        if (n == 1)
        {
            scanf("%s", str);
            printf("%s\n", str);
            continue;
        }
        int tot = 0;
        r = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%s", str);
            int len = strlen(str);
            r = max(len, r);
            for (int j = 0; j < len; j++)
            {
                id[tot] = i;
                gao.s[tot++] = str[j];
            }
            id[tot] = i;
            gao.s[tot++] = 'z' + i + 1;
        }
        gao.n = tot;
        gao.build_sa('z' + n + 1);
        gao.getHeight();
        solve();
    }
    return 0;
}