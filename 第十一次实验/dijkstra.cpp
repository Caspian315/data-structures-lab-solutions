#include<iostream>
#include<cmath>
#include<vector>
#include<iomanip>

using namespace std;

const double INFINITE = 1e8 * 1.0;

struct Point{
    double x;
    double y;

    Point() : x(0.0), y(0.0) {}
    Point(double x,double y) : x(x), y(y){}
};

double computeDist(Point& a, Point& b){
    double res = sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)); 
    return res;
}

vector<vector<double>> buildGraph(int n){
    //邻接矩阵
    vector<vector<double>> graph(n + 1,vector<double>(n + 1,INFINITE));
    for(int i = 1;i <= n; ++i){
        graph[i][i] = 0;
    }
    vector<Point> points(n + 1);//顶点从1开始数
    for(int i = 1;i <= n; ++i){
        double x,y;cin >> x >> y;
        points[i] = Point(x,y);
    }

    int m;cin >> m;
    for(int step = 0;step < m; ++step){
        int u,v;cin >> u >> v;
        double dist = computeDist(points[u],points[v]);
        graph[u][v] = dist;
        graph[v][u] = dist;//无向图
    }

    return graph;
}

double dijkstra(vector<vector<double>>& graph,int s,int t,int n){
    //这里只需要求最短路径长度，故不需要pre数组
    vector<bool> mask(n + 1,0);
    vector<double> dist(n + 1,0.0);

    //initial
    for(int i = 1;i <= n; ++i){
        dist[i] = graph[i][s];
    }
    dist[s] = 0.0;
    mask[s] = true;

    for(int i = 0; i < n - 1; ++i){
    int m = 0;double minD = INFINITE;
    for(int i = 1;i <= n; ++i){
        //先找出到s最短的点(贪心)
        if(!mask[i] && dist[i] < minD){
            m = i;
            minD = dist[i];
        }
    }
    if (m == 0) break; // 防越界
    mask[m] = true;
    for(int k = 1;k <= n; ++k){
        if(!mask[k] && dist[m] + graph[m][k] < dist[k]){
            dist[k] = dist[m] + graph[m][k];
        }
    }
    }
  
    return dist[t];
}

void solve(){
    int n;cin >> n;
    vector<vector<double>> graph = buildGraph(n);

    int s,t;cin >> s >> t;
    double minDist = dijkstra(graph,s,t,n);

    cout << fixed << setprecision(2) << minDist << '\n';
}


int main(){
ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    solve();
    return 0;
}