#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>


using namespace std;

#define FOR(i,a,b) for( int i=(a),_n=(b); i<=_n; ++i )
#define N 1000

class Edge {
public:
	int u, v;
	double distance;

	Edge( int _u=0, int _v=0, double _d=0 ):
		u(_u), v(_v), distance(_d) {}

	const bool operator<( const Edge &op ) const {
		return distance < op.distance;
	}
};

int t;
int n, m;
double x[N];
double y[N];
int s[N];
int k;
Edge edge[N*N];

int findSet( int p )
{
	if( s[p] < 0 ) 
		return p;
	return s[p] = findSet(s[p]);
}

void unionSet( int p, int q )
{
	p = findSet(p);
	q = findSet(q);

	if( p!=q )
		s[p] = q;
}

inline double dis( int a, int b )
{
	return (x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]);
}

int main( void )
{
	int u, v;
	int count;

	scanf( "%d", &t );

	while( t-- ) {

		scanf( "%d", &n );
		FOR( i, 1, n ) scanf( "%lf%lf", &x[i], &y[i] );
		memset( s, -1, sizeof(s) );

		scanf( "%d", &m );
		FOR( i, 1, m ) {
			scanf( "%d%d", &u, &v );
			unionSet( u, v );
		}

		k = 0;
		FOR( i, 1, n ) FOR( j, i+1, n ) 
			edge[++k] = Edge( i, j, dis(i,j) );
		
		sort( edge+1, edge+1+k );
		count = 0;

		FOR( i, 1, k ) {
			u = edge[i].u;
			v = edge[i].v;

			if( findSet(u) != findSet(v) ) {
				unionSet( u, v );
				printf( "%d %d\n", u, v );
				++count;
			}
		}

		if( !count )
			puts("No new highways need");
	
		if( t )
			cout << endl;
	}
	
	return 0;
}