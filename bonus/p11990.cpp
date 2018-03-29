#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

int N,M;
int A[200010];
struct Arr{
    int cnt,pre_sum;
};
struct  Brr{
    int X[200010],Y[200010];
    void insert(int x,int y){X[y] = x;Y[x] = y;}
    void decrease(int x,int y){X[y] = -1 ; Y[x] = -1;}
};
Arr arr[450][450];
Brr brr;
void update(int a,int b)
{
    int sum = (a>0? arr[a-1][b].pre_sum:0);
    for(int i = a ; i <= N/450; ++i)
    {
        sum+=arr[i][b].cnt;
        arr[i][b].pre_sum = sum;
    }
}

void increase(int x,int y)
{
    brr.insert(x,y);
    int a = x/450,b = y/450;
    ++arr[a][b].cnt;
    update(a,b);
}

void decrease(int x,int y)
{
    brr.decrease(x,y);
    int a = x/450,b = y/450;
    --arr[a][b].cnt;
    update(a,b);
}

int sum(int x,int y)
{
    int a = (x+1)/450;
    int b = (y+1)/450;
    int cnt =0;
    for(int i =0 ; i<b ; ++i){if(a>0)cnt+=arr[a-1][i].pre_sum;}
    for(int i = a*450 ; i<=x ; ++i)
    {
        if(brr.Y[i]!=-1 && brr.Y[i]<b*450)cnt++ ;
    }
    for(int i = 450*b; i<=y ; ++i)
        if(brr.X[i]!=-1 && brr.X[i]<=x)cnt++;
    return cnt;
}

int inverse(int x,int y)
{
    int res = 0;
    int sum_xy = sum(x,y);
    res+=sum(x,N-1)-sum_xy;
    res+=sum(N-1,y)-sum_xy;
    return res;
}

int main()
{
    while(scanf("%d %d",&N,&M)!=EOF)
    {
        for(int i=0 ; i<N ; ++i)
        {
            scanf("%d",&A[i]);A[i]--;
        }
        long long inversion =0;
        memset(arr,0,sizeof(arr));
        memset(brr.X,-1,sizeof(brr.X));
        memset(brr.Y,-1,sizeof(brr.Y));
        for(int i=0 ; i<N ; ++i)
        {
            increase(i,A[i]);
            inversion += inverse(i,A[i]);

        }
        while(M--)
        {
            int index;
            scanf("%d",&index);
            index--;
            printf("%lld\n",inversion);
            inversion -= inverse(brr.X[index],index);
            decrease(brr.X[index],index);
        }
    }

    return 0;
}