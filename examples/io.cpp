#include <algo/io.hpp>
#include <algo/debug.hpp>

using namespace std;
using namespace algo;

void test1() {
    int x, y; 
    string s;
    pair<int, long long> p;
    bitset<20> b;
    read(x, y, p); 
    read(s, b);
    debug(x, y, s, p, b);
}

void test2() {
    int n;
    read(n);
    vector<int> v(n);
    read(v);
    debug(v);
}

void test3() {
    int n, m;
    read(n, m);
    vector<vector<int>> mat(n, vector<int>(m));
    read(mat);
    debug(mat);
}

void test4() {
    int n, m;
    read(n, m);
    vector<vector<int>> g(n+1);
    pair<int, int> e;
    for (int i = 0; i < m; ++i) {
        read(e);
        auto [u, v] = e;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    debug(g);
}

int main() {
    test4();
}
