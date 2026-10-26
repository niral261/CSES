#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* children[2];
    TrieNode() {
        children[0] = nullptr;
        children[1] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(int num) {
        TrieNode* node = root;
        for(int i=30;i>=0;i--) {
            int bit = (num >> i) & 1;
            if(node->children[bit] == nullptr) {
                node->children[bit] = new TrieNode();
            }
            node = node->children[bit];
        }
    }

    int query(int num) {
        TrieNode* node = root;
        int max_xor = 0;

        for(int i=30;i>=0;i--) {
            int bit = (num >> i) & 1;
            int desired_bit = 1 - bit;
            if(node->children[desired_bit] == nullptr) {
                node = node->children[bit];
            } else {
                max_xor |= (1<<i);
                node = node->children[desired_bit];
            }
        }
        return max_xor;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (!(cin >> n)) return 0;

    Trie trie;
    trie.insert(0);

    int current_xor = 0;
    int max_xor = 0;

    for(int i=0;i<n;i++) {
        int x;
        cin >> x;
        current_xor ^= x;
        int query_xor = trie.query(current_xor);
        max_xor = max(max_xor, query_xor);
        trie.insert(current_xor);
    }
    cout << max_xor << endl;
    
    return 0;
}