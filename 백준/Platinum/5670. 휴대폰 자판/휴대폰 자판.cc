#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct TrieNode
{
    std::unordered_map<char, TrieNode*> child;
    bool is_end;

    TrieNode() {
        is_end = false;
    }
};

//트라이 자료구조
class Trie
{
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    TrieNode* insert(TrieNode* node, char ch) {
        //해당 노드 자식이 없는 경우 생성
        if (!node->child[ch]) {
            node->child[ch] = new TrieNode();
        }
        //포인터 이동
        return node->child[ch];
    }

    //최소 타자 수 검색
    int search(std::string str) {
        //첫번째 타자 고정
        int sum = 1;
        TrieNode* point = root->child[str[0]];
        for (int i = 1; i < str.length(); i++) {
            //밑에 자식이 하나를 초과하는 경우
            if (point->child.size() > 1) sum++;
            //그게 아니더라도 접두어가 있는 경우
            else if (point->is_end) sum++;
            //자식으로 포인터 이동
            point = point->child[str[i]];
        }
        return sum;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    while (std::cin >> n) {
        std::vector<std::string> vec(n);
        Trie trie;
        TrieNode* point;
        for (int i = 0; i < n; i++) {
            std::string str;
            std::cin >> str;
            vec[i] = str;
            point = trie.root;
            //포인터를 이동해가며 하나씩 트라이에 넣기
            for (int j = 0; j < str.length(); j++) {
                point = trie.insert(point, str[j]);
            }
            //맨 끝 문자 is_end flag
            point->is_end = true;
        }

        int total = 0;
        for (int i = 0; i < n; i++) {
            total += trie.search(vec[i]);
        }

        double result = (double)total / n;
        std::cout << std::fixed;
        std::cout.precision(2);
        std::cout << result << "\n";
    }
}