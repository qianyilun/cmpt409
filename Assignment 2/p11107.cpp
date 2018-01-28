#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>

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

int check(int mid,int m,int n)
{
    int pos = -1;
    int cc = 0;
    int tmp = -1;
    for(int i = 1;i <= n;i++)
    {
        if(i == 1)
        {
            if(n - SA.sa[i] >= mid)
            {
                cc = 1;
                tmp = SA.sa[i];
            }
            else
            {
                cc = 0;
                tmp = -1;
            }
        }
        else if(height[i] >= mid)
        {
            tmp = max(SA.sa[i],tmp);
            cc++;
        }
        else
        {
            if(n - SA.sa[i] >= mid)
            {
                cc = 1;
                tmp = SA.sa[i];
            }
            else
            {
                cc = 0;
                tmp = -1;
            }
        }
        if(cc >= m) pos = max(pos,tmp);

    }
    if(pos != -1)
    {
        ans_pos = pos;
        return 1;
    }
    else return 0;
}

string strg;
// int main () 
// {
//     int senario = 3;


//     string v = "abcdefg.bcdefgh.cdefghi";
    
//     int n = v.length();
    
//     // declaring character array
//     char s[n+1];
    
//     // copying the contents of the
//     // string to char array
//     strcpy(SA.str, v.c_str());
    
//     SA.build();

    
//     build_h();

//     for (int i = 0; i < n; i++) {
//         cout << " ";
//         cout << SA.sa[i];
//         printf(" %.*s\n", n, SA.str + SA.sa[i]);
//     }


//     for (int i = 0; i < n; i++) {
        
//         printf(" %d ", height[i]);
//     }
    


//     int l = 1,r = n;
//     int ans = 0;
//     while( l <= r)
//     {
//         int mid = (l + r) / 2;
//         if(check(mid,senario,n))
//         {
//             ans = mid;
//             l = mid + 1;
//         }
//         else r = mid - 1;
//     }

//     if(ans)
//     {
//         printf("\n%d %d\n",ans,ans_pos);
//         printf(" %.*s\n", ans, SA.str + ans_pos);
//     }
//     else puts("?");
//     return 0;
// }

// int main() {

//     int senario = 0;
//     cin >> senario;

//     for (int i = 0; i < senario; i++) {
//         char str;
//         scanf("%s", str);
//         cout << str;
//     }    

//     return 0;
// }

// char *convert(const std::string & s)
// {
//    char *pc = new char[s.size()+1];
//    std::strcpy(pc, s.c_str());
//    return pc; 
// }

int forms;
string inputLine;
string v;
            
int main () {
    int temp = 0;
    while (scanf("%d", &forms) == 1 && forms) {
        if (temp) printf("\n");
	    else temp = 1;
        if (forms == 1) {
            cin >> inputLine;
            cout << inputLine << "\n";
            continue;
	    }

        for (int i = 0; i < forms; i++) {
            cin >> inputLine;

            v += inputLine;
            v += ".";
        }
        v.pop_back();
        strcpy(SA.str, v.c_str());
        
        // finish str initialize
        cout << v << "\n";
        for (int i = 0; i < v.length(); i++) {
            cout << SA.str[i];
        }

        SA.n = v.length();
        SA.build();

        // for (int i = 0; i < v.length(); i++) {
        //     cout << " ";
        //     cout << SA.sa[i];
        // }

        build_h();

        // for (int i = 0; i < v.length(); i++) {
        //     cout << " ";
        //     cout << height[i];
        // }

        int n = v.length();
        int l = 1,r = n;
        int ans = 0;
        while( l <= r)
        {
            int mid = (l + r) / 2;
            if(check(mid,forms,n))
            {
                ans = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }

        if(ans)
        {
            // printf("\n%d %d\n",ans,ans_pos);
            printf("\n%.*s\n", ans, SA.str + ans_pos);
        }
        else puts("?");

        cout << "\n";
    }
    return 0;
}








//  * 先将所有串连接起来,中间用不同的没有出现的值隔开,求出后缀数组和height数组后
//  * 利用height数组进行分组, 二分判断是否存在长度长度为L的串满足条件
//  * 将满足条件的长度对应的多个不同子串的开始位置保存起来即可, 简单的height数组分组应用


// 简单的后缀数组height数组分组的运用, 首先将所有的串都连接起来, 
// 中间用不同的没有出现在n个字符串中的字符隔开, 然后二分子串长度L判断是否存在满足条件的长度为子串, 
// 对于多个解用vector存储一下其起始位置,最后还原字符串排序后输出即可