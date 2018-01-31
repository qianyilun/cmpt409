#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#define MAXN 100 * 10000 + 10
#define pii pair<int, int>
using namespace std;
struct Node
{
    pii v;
    int p;
    friend bool operator<(const Node &p1, const Node &p2)
    {
        return (p1.v < p2.v);
    }
} tsa[MAXN];

char s[MAXN];
int T, n;
int b[1050], p[MAXN], ans[MAXN];
int rk[MAXN], sa[MAXN];
void build_sa()
{
    for (int i = 1; i <= n; i++)
    {
        rk[i] = s[i] - 96;
    }
    for (int k = 1; k <= n; k <<= 1)
    {
        for (int i = 1; i <= n - k; i++)
        {
            tsa[i].v = make_pair(rk[i], rk[i + k]);
            tsa[i].p = i;
        }
        for (int i = n - k + 1; i <= n; i++)
        {
            tsa[i].v = make_pair(rk[i], 0);
            tsa[i].p = i;
        }
        sort(tsa + 1, tsa + n + 1);
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!cnt || tsa[i].v != tsa[i - 1].v)
            {
                cnt++;
            }
            rk[tsa[i].p] = cnt;
        }
        if (cnt >= n)
            break;
    }
    for (int i = 1; i <= n; i++)
    {
        sa[rk[i]] = i;
    }
}
int height[MAXN];
void build_height()
{
    int k = 0;
    for (int i = 1; i <= n; i++)
    {
        if (k)
            k--;
        int j = sa[rk[i] - 1];
        while (s[i + k] == s[j + k])
        {
            k++;
        }
        height[rk[i]] = k;
    }
}
void init()
{
    n = 0;
    char tmp = 'z' + 1;
    for (int i = 1; i <= T; i++)
    {
        scanf("%s", s + n + 1);
        int t = n;
        n = strlen(s + 1);
        s[++n] = (tmp++);
        for (int j = t + 1; j <= n; j++)
        {
            p[j] = i;
        }
    }
    build_sa();
    build_height();
}
int check(int x)
{
    memset(b, 0, sizeof(b));
    int cnt = 0;
    int ret = 0;
    for (int i = 1; i <= n; i++)
    {
        if (height[i] >= x)
        {
            if (!cnt)
            {
                if (p[sa[i]] == p[sa[i - 1]])
                {
                    cnt = 1;
                }
                else
                {
                    cnt = 2;
                }
                b[p[sa[i]]] = b[p[sa[i - 1]]] = 1;
            }
            else if (!b[p[sa[i]]])
            {
                b[p[sa[i]]] = 1;
                cnt++;
            }
            if (cnt > T / 2)
            {
                ans[sa[i]] = 1;
                ret = 1;
            }
        }
        else
        {
            memset(b, 0, sizeof(b));
            cnt = 0;
        }
    }
    return ret;
}
vector<string> vs;
string ept;
void print(int x)
{
    vs.clear();
    string ts(s, n + 1);
    for (int i = 1; i <= n; i++)
    {
        if (ans[i])
        {
            string t;
            t = ept;
            for (int j = i; j <= i + x - 1; j++)
            {
                t += s[j];
            }
            vs.push_back(t);
        }
    }
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());
    for (int i = 0; i < vs.size(); i++)
    {
        cout << vs[i] << endl;
    }
}
void solve()
{
    //    for(int i=1;i<=n;i++){
    //        for(int j=sa[i];j<=n;j++){
    //            printf("%c",s[j]);
    //        }
    //        printf("\n");
    //    }
    //    for(int i=6;i<=n;i++){
    //        printf("%d\n",check(i));
    //    }
    int L = 0, R = n;
    while (R - L > 1)
    {
        int mid = (L + R) / 2;
        if (check(mid))
        {
            L = mid;
        }
        else
        {
            R = mid;
        }
    }
    memset(ans, 0, sizeof(ans));
    if (R && check(R))
    {
        print(R);
    }
    else
    {
        if (L && check(L))
        {
            print(L);
        }
        else
        {
            printf("?\n");
        }
    }
}
int main()
{
    //    freopen("data.in","r",stdin);
    //    freopen("my.out","w",stdout);
    int flag = 0;
    while (1)
    {
        scanf("%d", &T);
        if (!T)
            break;
        if (flag)
        {
            printf("\n");
        }
        else
        {
            flag = 1;
        }
        if (T == 1)
        {
            scanf("%s", s + 1);
            printf("%s\n", s + 1);
            continue;
        }
        init();
        solve();
    }
    return 0;
}