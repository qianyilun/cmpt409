#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <queue>
#include <set>

using namespace std;

//#define WIN
#ifdef WIN
typedef __int64 LL;
#define iform "%I64d"
#define oform "%I64d\n"
#define oform1 "%I64d"
#else
typedef long long LL;
#define iform "%lld"
#define oform "%lld\n"
#define oform1 "%lld"
#endif

#define S64I(a) scanf(iform, &(a))
#define P64I(a) printf(oform, (a))
#define P64I1(a) printf(oform1, (a))
#define REP(i, n) for (int(i) = 0; (i) < n; (i)++)
#define REP1(i, n) for (int(i) = 1; (i) <= (n); (i)++)
#define FOR(i, s, t) for (int(i) = (s); (i) <= (t); (i)++)

const int INF = 0x3f3f3f3f;
const double eps = 1e-9;
const double PI = (4.0 * atan(1.0));

const int maxn = 100 + 20;
const int maxl = 1000 + 20;
const int sa_maxl = maxn * maxl;
int s[sa_maxl];
int sa[sa_maxl];
int t[sa_maxl], t2[sa_maxl], c[sa_maxl];

char str[maxn][maxl];
int idx[sa_maxl];

void build_sa(int *s, int *sa, int n, int m)
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

    // int num = sizeof (sa) / sizeof (int);
    //     for (i = 0; i < num; i++) {
    //         printf("%d", sa[i]);
    //    }
}

int rank[sa_maxl], height[sa_maxl];
void getHeight(int n)
{
    int i, j, k = 0;
    for (i = 0; i < n; i++)
        rank[sa[i]] = i;
    for (i = 0; i < n; i++)
    {
        if (k)
            k--;
        int j = sa[rank[i] - 1];
        while (s[i + k] == s[j + k])
            k++;
        height[rank[i]] = k;
    }

    for (int loop = 0; loop < 15; loop++)
        printf("XX%d ", height[loop]);
}

int flag[sa_maxl];
bool good(int L, int R, int n, int limt)
{
    if (R - L < limt)
        return false;
    memset(flag, 0, sizeof(flag));
    int cnt = 0;
    for (int i = L; i < R; i++)
    {
        int x = idx[sa[i]];
        if (x != n && !flag[x])
        {
            flag[x] = 1;
            cnt++;
        }
    }
    return cnt >= limt;
}

void print_sub(int len, int L, int n)
{
    while (idx[L] == n)
        L++;
    int x = sa[L];
    for (int i = 0; i < len; i++)
    {
        putchar(s[x + i] + 'a' - 1);
    }
    putchar('\n');
}

bool judge(int len, int n, int limt, bool print)
{
    int L = 0;
    for (int R = 1; R <= n; R++)
    {
        if (R == n || height[R] < len)
        {
            if (good(L, R, n, limt))
            {
                if (print)
                {
                    print_sub(len, L, n);
                }
                else
                    return true;
            }
            L = R;
        }
    }
    return false;
}

int main()
{
    int n;
    int kase = 1;

    while (scanf("%d", &n) != EOF && n)
    {
        if (kase++ > 1)
            putchar('\n');
        int len = 0;
        int maxlen = 0;
        // str[0] = "abcdefg";
        // str[1] = "bcdefgh";
        // str[2] = "cdefghi";
        for (int i = 0; i < n; i++)
        {
            scanf("%s", str[i]);
            int sz = strlen(str[i]);
            maxlen = max(maxlen, sz);
            for (int j = 0; j < sz; j++)
            {
                s[len] = str[i][j] - 'a' + 1;
                idx[len++] = i;
            }
            s[len] = '.' + i;
            idx[len++] = n;
        }
        s[len] = 0;
        idx[len++] = n;
        int m = '.' + n;
        if (n == 1)
        {
            puts(str[0]);
            continue;
        }
        int limt = n / 2 + 1;
        build_sa(s, sa, len, m);

        for (int i = 0; i < 15; i++)
        {
            printf("%d ", sa[i]);
        }

        for (int i = 0; i < 15; i++)
        {
            printf("%.*s\n", 15, *str + i);
        }

        getHeight(len);
        if (!judge(1, len, limt, false))
        {
            puts("?");
            continue;
        }
        int L = 1, R = maxlen;
        while (L < R)
        {
            int M = L + (R - L + 1) / 2;
            if (judge(M, len, limt, false))
                L = M;
            else
                R = M - 1;
        }
        judge(L, len, limt, true);
    }

    return 0;
}