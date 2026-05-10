#include <iostream>
#include <fstream>
using namespace std;

// 求父节点
int parent(int x) {
    return (x - 1) / 2;
}

// 求节点深度（根节点深度 0）
int getDepth(int x) {
    int depth = 0;
    while (x) {
        x = parent(x);
        depth++;
    }
    return depth;
}

void solve() {
    int n, u, v;
    cin >> n >> u >> v;

    int depthU = getDepth(u);
    int depthV = getDepth(v);

    while (depthU > depthV) {
        u = parent(u);
        depthU--;
    }
    while (depthV > depthU) {
        v = parent(v);
        depthV--;
    }

    while (u != v) {
        u = parent(u);
        v = parent(v);
    }

    cout << u << '\n';
}

int main()
{
    // 文件输入
    ifstream instream("input2.txt");
    if (!instream.is_open()) {
        cout << "open file failed" << endl;
        return 1;
    }
    cin.rdbuf(instream.rdbuf());

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}