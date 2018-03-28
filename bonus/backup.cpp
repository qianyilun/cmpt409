#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
#include<string>
#include<sstream>
#include<map>
#include<algorithm>
#define maxn 200010
#define BUCKET_SIZE 450

using namespace std;
typedef long long LL;
int N,M;
int A[maxn];
struct Bucket{
    int cnt,pre_sum;
};
Bucket bucket[BUCKET_SIZE][BUCKET_SIZE];
struct  Space{
    int X[maxn],Y[maxn];
    void insert(int x,int y){X[y] = x;Y[x] = y;}
    void remove(int x,int y){X[y] = -1 ; Y[x] = -1;}
};
Space space;
void update_pre_sum(int bx,int by)
{
    int sum = (bx>0? bucket[bx-1][by].pre_sum:0);
    for(int i = bx ; i<=N/BUCKET_SIZE ; ++i)
    {
        sum+=bucket[i][by].cnt;
        bucket[i][by].pre_sum = sum;
    }
}

void add(int x,int y)
{
    space.insert(x,y);
    int bx = x/BUCKET_SIZE,by = y/BUCKET_SIZE;
    ++bucket[bx][by].cnt;
    update_pre_sum(bx,by);
}

void remove(int x,int y)
{
    space.remove(x,y);
    int bx = x/BUCKET_SIZE,by = y/BUCKET_SIZE;
    --bucket[bx][by].cnt;
    update_pre_sum(bx,by);
}

int sum(int x,int y)
{
    int bx = (x+1)/BUCKET_SIZE;
    int by = (y+1)/BUCKET_SIZE;
    int cnt =0;
    for(int i =0 ; i<by ; ++i){if(bx>0)cnt+=bucket[bx-1][i].pre_sum;}
    for(int i = bx*BUCKET_SIZE ; i<=x ; ++i)
    {
        if(space.Y[i]!=-1 && space.Y[i]<by*BUCKET_SIZE)cnt++ ;
    }
    for(int i = BUCKET_SIZE*by; i<=y ; ++i)
        if(space.X[i]!=-1 && space.X[i]<=x)cnt++;
    return cnt;
}

int Inv(int x,int y)
{
    int res = 0;
    int sum_xy = sum(x,y);
    res+=sum(x,N-1)-sum_xy;
    res+=sum(N-1,y)-sum_xy;
    return res;
}

int main()
{
    //freopen("H:\\c++\\file\\stdin.txt","r",stdin);

    while(scanf("%d %d",&N,&M)!=EOF)
    {
        for(int i=0 ; i<N ; ++i)
        {
            scanf("%d",&A[i]);A[i]--;
        }
        LL inv =0;
        memset(bucket,0,sizeof(bucket));
        memset(space.X,-1,sizeof(space.X));
        memset(space.Y,-1,sizeof(space.Y));
        for(int i=0 ; i<N ; ++i)
        {
            add(i,A[i]);
            //printf("%d\n",sum(i,N-1)-sum(i,A[i]));
            inv += Inv(i,A[i]);

        }
        while(M--)
        {
            int idx;
            scanf("%d",&idx);
            idx--;
            printf("%lld\n",inv);
            inv-=Inv(space.X[idx],idx);
            remove(space.X[idx],idx);

        }
    }

    return 0;
}