#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <bits/stdc++.h>

using namespace std;

struct SuffixArray
{
    int sa[110005], h[110005], n;
    char str[110005];

    int w[110005], ta[110005], tb[110005]; // buffer
    void sort(int *x, int *y, int m)
    { // radix sort
        static int i;
        for (i = 0; i < m; i++)
            w[i] = 0;
        for (i = 0; i < n; i++)
            w[x[y[i]]]++;
        for (i = 1; i < m; i++)
            w[i] += w[i - 1];
        for (i = n - 1; i >= 0; i--)
            sa[--w[x[y[i]]]] = y[i];
    }
    bool cmp(int *r, int a, int b, int l)
    {
        if (r[a] == r[b])
        {
            if (a + l >= n || b + l >= n)
                return false;
            return r[a + l] == r[b + l];
        }
        return false;
    }

    void build()
    { // x: rank, y: second key(array index)
        int i, k, m = 128, p;
        int *x = ta, *y = tb, *z;
        n = strlen(str);
        x[n] = 0;
        for (i = 0; i < n; i++)
            x[i] = str[i], y[i] = i;
        sort(x, y, m);
        for (k = 1, p = 1; p < n; k *= 2, m = p)
        {
            for (p = 0, i = n - k; i < n; i++)
                y[p++] = i;
            for (i = 0; i < n; i++)
            {
                if (sa[i] >= k)
                {
                    y[p++] = sa[i] - k;
                }
            }
            sort(x, y, m);
            z = x, x = y, y = z;
            for (i = 1, p = 1, x[sa[0]] = 0; i < n; i++)
                x[sa[i]] = cmp(y, sa[i - 1], sa[i], k) ? p - 1 : p++;
        }
    }
};

SuffixArray SA;

vector<int> v;

vector<int> kasai(string s, vector<int> sa)
{
    int n = s.size(), k = 0;
    vector<int> lcp(n, 0);
    vector<int> rank(n, 0);

    for (int i = 0; i < n; i++)
        rank[sa[i]] = i;

    for (int i = 0; i < n; i++)
    {
        cout << rank[i];
    }

    for (int i = 0; i < n; i++, k ? k-- : 0)
    {
        if (rank[i] == n - 1)
        {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
        {
            k++;
            cout << " k = *" + k;
        }
        lcp[rank[i]] = k;
    }
    return lcp;
}

string strg;
int main()
{
    int split1 = 7;
    int split2 = 15;
    strg = "abcdefg.bcdefgh";

    // int n = strg.length();

    // // declaring character array
    // char s[n+1];

    char s[] = "abcdefg.bcdefgh";

    // copying the contents of the
    // string to char array
    // strcpy(s, strg.c_str());

    // SuffixArray suffix(s);
    // v = suffix.GetSuffixArray();

    // for (int i = 0; i < v.size(); i++) {
    //     cout << v[i] << " ";

    //     printf("%.*s\n", 15, s + i);

    // }

    strcpy(SA.str, strg.c_str());

    SA.build();

    kasai(strg, v);

    // for (int i = 0; i < 15; i++) {
    //     cout << res[i] << " ";
    // }

    // build_h(s);

    // int ta[110005], h[110005];
    // int i, j, k;
    // for(i = 0; i < 15; i++)  ta[v[i]] = i;
    // for(i = 0; i < 15; i++) {
    //     if(ta[i] == 0) {
    //         h[ta[i]] = 0;
    //         continue;
    //     }
    //     if(i == 0 || h[v[i-1]] <= 1)
    //         k = 0;
    //     else
    //         k = h[ta[i-1]]-1;
    //     while(s[v[ta[i]-1]+k] == s[v[ta[i]]+k])
    //         k++;
    //     h[ta[i]] = k;
    // }

    // for (int i = 0; i < 15; i++) {
    //     cout << h[i] << " ";
    // }

    // getHeight(15);
    // int rank[1004], height[1004];
    // int i, j, k = 0, n = 15;
    // for(i = 0; i < n; i++) {
    //     rank[v[i]] = i;
    //     cout << rank[v[i]];
    // }
    // for(i = 0; i < n; i++) {
    //     if(k) {
    //         k--;
    //     }
    //     int j = v[rank[i]-1];
    //     while(s[i+k] == s[j+k]) {
    //         k++;
    //         cout << "YYYYY";
    //     }
    //     height[rank[i]] = k;
    // }

    // for (int i = 0; i < 15; i++) {
    //     cout << height[i] << " ";
    // }

    // cout<< suffix.LongestCommonPrefix(split1+1, split2+1);
}
