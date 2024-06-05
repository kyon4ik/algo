#include <algo/trie.hpp>
#include <iostream>

using std::cin, std::cout, std::endl;

int main() {
    int n;
    cin >> n;
    algo::BinaryTrie<int> trie(n);
    
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        trie.add(x);
    }

    int q;
    cin >> q;
    while (q--) {
        int x, t;
        cin >> t >> x;
        if (t == 1) cout << "Contains: " << trie.contains(x) << endl;
        else cout << "Remove: " << trie.remove(x) << endl;
    }
}
