#include <iostream>
#include <string>

struct TrieNode
{
    TrieNode* child[10];
    bool is_end;
    
    TrieNode() {
        for(int i = 0; i < 10; i++) child[i] = nullptr;
        is_end = false;
    }
};

class Trie
{
public:
    TrieNode* root;
    
    Trie(){
        root = new TrieNode();
    }
    
    bool insert(TrieNode* node, std::string str){
        bool result = true;
        if(node->is_end) return false;
        
        if(str.length() == 0){
            node->is_end = true;
            for(int i = 0; i < 10; i++) if(node->child[i]) return false;
            return true;
        }
        
        if(!node->child[str[0] - '0']) node->child[str[0] - '0'] = new TrieNode();
        
        result = insert(node->child[str[0] - '0'], str.substr(1));
        return result;
    }
};

int main(){
    int T;
    std::cin >> T;
    for(int t = 0; t < T; t++){
        int n;
        bool result = true;
        Trie trie;
        
        std::cin >> n;
        for(int i = 0; i < n; i++){
            std::string str;
            std::cin >> str;
            bool temp;

            if(!trie.root->child[str[0] - '0']) trie.root->child[str[0] - '0'] = new TrieNode();
            temp = trie.insert(trie.root->child[str[0] - '0'], str);
            if(!temp) result = false;
        }
        
        if(result) std::cout << "YES\n";
        else std::cout << "NO\n";
    }
}