#include <iostream>
#include <string>
#include <map>

struct TrieNode
{
    std::string str;
    std::map<std::string, TrieNode*> child;
    int level;
};

class Trie
{
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
        root->str = "";
        root->level = 0;
    }

    TrieNode* insert(TrieNode* node, std::string str) {
        if (!node->child[str]) {
            node->child[str] = new TrieNode();
            node->child[str]->str = str;
            node->child[str]->level = node->level + 1;
        }
        return node->child[str];
    }

    void print(TrieNode* node) {
        if (node != root) {
            for (int i = 1; i < node->level; i++) std::cout << "--";
            std::cout << node->str << "\n";
        }
        for (auto child = node->child.begin(); child != node->child.end(); ++child) {
            print(child->second);
        }
    }
};

int main() {
    Trie trie;
    TrieNode* point;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int m;
        std::cin >> m;
        point = trie.root;
        for (int j = 0; j < m; j++) {
            std::string str;
            std::cin >> str;
            point = trie.insert(point, str);
        }
    }

    trie.print(trie.root);
}