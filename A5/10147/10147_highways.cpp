#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>
using namespace std;


set<pair<int, int>> builtSet;

template<class T>
ostream& operator << (ostream& os, vector<T> v) {
    os << "[ ";
    for (const auto& i : v) {
        os << i << " ";
    }
    os << "]";
    return os;
}

template<class P1, class P2>
ostream& operator << (ostream& os, pair<P1, P2> p) {
    os << "{";
    os << p.first << ", " << p.second;
    os << "}";
    return os;
}

template<class T>
ostream& operator << (ostream& os, set<T> v) {
    os << "[ ";
    for (const auto& i : v) {
        os << i << " ";
    }
    os << "]";
    return os;
}



struct UnionFindSet {
    vector<int> parent;
    void init(int nn) {
        parent.resize(nn + 1);
        for (int i = 0; i < parent.size(); i++)
            parent[i] = i;
    }

    void merge(int x, int y) {
        parent[find(x)] = find(y);
    }
    int find(int x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }
    bool together(int x, int y) {
        return find(x) == find(y);
    }
};

struct Graph {
    struct Edge {
        int from;
        int to;
        double len;
    };
    friend ostream& operator << (ostream& os, Edge e) {
        os << "{ " << e.from << " " << e.to << " " << e.len << " }";
        return os; 
    }

    const static int MAXNODE = 3 * 1e5 + 2;
    vector<int> g[MAXNODE];
    vector<Edge> edge;
    int n;
    void init(int nn) {
        n = nn;
        for (int i = 0; i <= n; i++)
            g[i].clear();
        edge.clear();
    }

    void add_e(int x, int y, double len) {
        g[x].push_back(edge.size());
        edge.push_back((Edge){x, y, len});
        // g[y].push_back(edge.size());
        // edge.push_back((Edge){y, x, len});
    }

    void update_e(int x, int y, double len) {
        for (auto& e : edge) {
            if (e.from == x && e.to == y) {
                e.len = len;
            } else if (e.from == y && e.to == x) {
                e.len = len;
            } 
        }
    }

    void show() {
    	for (int i = 0; i <= n; i++) {
    		printf("%d:", i);
    		for (int ie : g[i])
    			printf(" %d", edge[ie].to);
    		printf("\n");
    	}
    	printf("\n");
    }

    // 
    // ---- start of Minimum Spanning Tree ---
    // 
    UnionFindSet ufs;
    void mst() {
    	ufs.init(n);
    	vector<Edge> eee = edge;
    	sort(eee.begin(), eee.end(), [](const Edge& a, const Edge& b) {
            if (a.len == b.len) {
                if (a.from == b.from){
                    return a.to<b.to;
                }
                // return max(a.from, a.to) < max(b.from, b.to);
                return a.from < b.from;
            } else {
                return a.len < b.len;
            }
    	});
        // cout << "eee: " << eee << endl;

        int counter = 0;

    	int need = n - 1;
    	for (const auto& e : eee) {
    		if (!ufs.together(e.from, e.to)) {
    			// add Edge e
    	        ufs.merge(e.from, e.to);
                if (builtSet.find(make_pair(e.from, e.to)) == builtSet.end()) {
                    // if (e.from < e.to) 
                    //     // cout << e.from + 1 << " " << e.to + 1<<'\n';
                    //     printf( "%d %d\n", e.from + 1, e.to + 1 );
                    // else 
                    //     // cout << e.to + 1 << " " << e.from + 1<<'\n';
                    //     printf( "%d %d\n", e.to + 1, e.from + 1 );
                    // // if (&e !=&eee.back() ) cout<<endl;
                    printf( "%d %d\n", e.from + 1, e.to + 1 );
                    counter++;
                }
        		need--;
    			if (!need)
    				break;
    		}
    	}
        if (counter == 0) {
            cout << "No new highways need";
        }
    }
    // 
    // ---- end of Minimum Spanning Tree ---
    // 
};

inline double euclidean(const pair<int, int>& p1, const pair<int, int>& p2) {
    // return pow(p1.first - p2.first, 2.0) + pow(p1.second - p2.second, 2.0);
    return (p1.first - p2.first)*(p1.first - p2.first)+(p1.second - p2.second)*(p1.second - p2.second);
}

int main(int argc, char const *argv[])
{
    /* code */
    int cases = 0;
    scanf("%d\n", &cases);

    for (int i = 0; i < cases; ++i) {
        int cities = 0;
        scanf("%d\n", &cities);

        Graph g;
        g.init(cities);

        vector<pair<int, int>> coord;
        for (int city = 0; city < cities; ++city) {
            int x,y;
            scanf("%d %d\n", &x, &y);
            coord.push_back(make_pair(x, y));
            // g.add_e(x, y, euclidean(coord[x-1], coord[y-1]));
        }

        // for (int ii = 0; ii < cities; ++ii) {
        //     for (int ij = 0; ij < ii; ++ij) {
        //         if (ii != ij) {
        //             g.add_e(ii, ij, euclidean(coord[ii], coord[ij]));
        //         }
        //     }
        // }
        for (int ii =0; ii < cities;++ii){
            for (int ij =ii+1l ;ij < cities;++ij){
                g.add_e(ii,ij,euclidean(coord[ii],coord[ij]));
            }
        }

        // for (auto& e : g.edge) {
        //     cout << e.from << " " << e.to << " " << e.len << endl;
        // }
        // g.show();

        int highways = 0;
        scanf("%d\n", &highways);
        for (int h = 0; h < highways; h++) {
            int x,y;
            scanf("%d %d\n", &x, &y);
            if (x<y){
                g.update_e(x-1, y-1, 0.0);
                builtSet.insert(make_pair(x - 1, y - 1));    
            }
            else {
                g.update_e(y-1, x-1, 0.0);
                builtSet.insert(make_pair(y - 1, x - 1));    
            }
            
            

        }

        // cout << builtSet << endl;

        // cout << "After: " << endl;
        // for (auto& e : g.edge) {
        //     cout << e.from << " " << e.to << " " << e.len << endl;
        // }

        g.mst();

        // for (int i = 0; i < cities; ++i) {
        //     cout << g.ufs.find(i) << " ";
        // }
        if (i != cases - 1) {
            printf("\n");
        }
    }

    return 0;
}