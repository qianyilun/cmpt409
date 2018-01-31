#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

struct SuffixArray {
    int sa[110005], h[110005], n;
    char str[110005];
    
    int w[110005], ta[110005], tb[110005]; // buffer
    void sort(int *x, int *y, int m) { // radix sort
        static int i;
        for(i = 0; i < m; i++)
            w[i] = 0;
        for(i = 0; i < n; i++)
            w[x[y[i]]]++;
        for(i = 1; i < m; i++)
            w[i] += w[i-1];
        for(i = n-1; i >= 0; i--)
            sa[--w[x[y[i]]]] = y[i];
    }
    bool cmp(int *r, int a, int b, int l) {
        if(r[a] == r[b]) {
            if(a+l >= n || b+l >= n)
                return false;
            return r[a+l] == r[b+l];
        }
        return false;
    }
    void build_h() {
        int i, j, k;
        for(i = 0; i < n; i++)  ta[sa[i]] = i;
        for(i = 0; i < n; i++) {
            if(ta[i] == 0) {
                h[ta[i]] = 0;
                continue;
            }
            if(i == 0 || h[ta[i-1]] <= 1)
                k = 0;
            else
                k = h[ta[i-1]]-1;
            while(str[sa[ta[i]-1]+k] == str[sa[ta[i]]+k])
                k++;
            h[ta[i]] = k;
        }
    }
    void build() {// x: rank, y: second key(array index)
        int i, k, m = 128, p;
        int *x = ta, *y = tb, *z;
        
        x[n] = 0;
        for(i = 0; i < n; i++)
            x[i] = str[i], y[i] = i;
        sort(x, y, m);
        for(k = 1, p = 1; p < n; k *= 2, m = p) {
            for(p = 0, i = n-k; i < n; i++)
                y[p++] = i;
            for(i = 0; i < n; i++) {
                if(sa[i] >= k) {
                    y[p++] = sa[i]-k;
                }
            }
            sort(x, y, m);
            z = x, x = y, y = z;
            for(i = 1, p = 1, x[sa[0]] = 0; i < n; i++)
                x[sa[i]] = cmp(y, sa[i-1], sa[i], k) ? p-1 : p++;
        }
        
        
    }
};
SuffixArray SA;
int ta[110005], height[110005];
int ans_pos;

void build_h() {
    int i, j, k;
    for(i = 0; i < SA.n; i++)  ta[SA.sa[i]] = i;
    for(i = 0; i < SA.n; i++) {
        if(ta[i] == 0) {
            height[ta[i]] = 0;
            continue;
        }
        if(i == 0 || height[SA.sa[i-1]] <= 1)
            k = 0;
        else
            k = height[ta[i-1]]-1;
        while(SA.str[SA.sa[ta[i]-1]+k] == SA.str[SA.sa[ta[i]]+k])
            k++;
        height[ta[i]] = k;
    }
    
}

int len[110];
int pos[110005];
char str[110005];
char s[110005];

int main() {
    int k, n, flag = 0, i, j;
    len[0] = -1;

    while (scanf("%d", &k), k) {
        pos[0] = 0;
        n = 0;
        int t = 30;
        for (i = 1; i <= k; ++i) {
            scanf("%s", str);
            int l = strlen(str);
            for (j = 0; j < l; ++j) {
                s[n++] = str[j] - 'a' + 1;
            }
            len[i] = n;
            s[n++] = t++;
        }
        s[n - 1] = 0;


        SA.n = 23;
        SA.build();

        build_h();

        for (int i = 0; i < 23; i++) {
            cout << " ";
            cout << height[i];
        }
    }
}