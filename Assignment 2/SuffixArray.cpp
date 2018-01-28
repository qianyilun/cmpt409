//
//  main.cpp
//  cmpt
//
//  Created by Yilun Qian on 2018-01-26.
//  Copyright © 2018 Yilun Qian. All rights reserved.
//
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>

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
        n = strlen(str);
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

void build_h(char* str) {
    int i, j, k;
    for(i = 0; i < 15; i++)  ta[SA.sa[i]] = i;
    for(i = 0; i < 15; i++) {
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
    
    for (int i = 0; i < 15; i++) {
        cout << height[i] << " ";
    }
}

int answerNum = 0;
int answerPosition[110005];

// bool valid(int len, int n) {
//     bool result = false;
//     int begin = 0, end = 0;
//     for (int i = 1; i < n; i++) {
//         if (height[i] >= len) {
//             end++;
//         } else {
//             if (solve(begin, end)) {
//                 if (!result) {
//                     answerNum = 0;
//                 }
//                 result = true;
//                 answerPosition[answerNum++] = SA.sa[begin];
//             }
//             begin = i;
//             end = i;
//         }
//     }
//     if (begin < end) {
//         if (solve(begin, end) {
//             if (!result) {
//                 answerNum = 0;
//                 result = true;
//                 answerPosition[answerNum++] = SA.sa[begin];
//             }
//         }
//     }
//     return result;
// }

// bool visited[10005];    
// bool solve(int begin, int end) 
// {
//   int total = 0;
//   int strNum = 2;
//   int temp = strNum / 2; // the number of cases
//   for (int i = 0; i < strNum; i++) {
//     visited[i] = false;
//   }
//   for (int i = begin, i < end + 1; i++) {
//     if (!visited[])
//   }
// }            

bool isValid(int n, int m, int mid) {
  set<int> visited;
  visited.insert()
}


string strg;
int main() {
    int split1 = 7;
    int split2 = 15;
    strg = "abcdefg.bcdefgh";
    
    int n = strg.length();
    
    // declaring character array
    char s[n+1];
    
    // copying the contents of the
    // string to char array
    strcpy(SA.str, strg.c_str());
    
    SA.build();
    
    for (int i = 0; i < n; i++) {
        cout << " ";
        cout << SA.sa[i];
        printf(" %.*s\n", 15, SA.str + SA.sa[i]);
    }
    
    build_h(s);

    
    int left = 0, right = n;
    while (left + 1< right) {
        int mid = left + (right - left) / 2;
        
        if (valid(mid, n)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    
    return 0;
}
