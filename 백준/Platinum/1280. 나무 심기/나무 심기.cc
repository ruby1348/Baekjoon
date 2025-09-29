#include <iostream>
#include <vector>
#define MAX 262144
#define MOD 1000000007

class node{
public:
long long num;
long long sum;
node() {num = 0; sum = 0;};
};

std::vector<node> segtree(MAX * 2);

node sum_tree(int start, int end, int left, int right, int point);
void insert(int point, int num);

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);

	int n;
	std::cin >> n;
    long long result = 1;

    long long temp;
    std::cin >> temp;
    insert(temp, temp);
    
	for (int i = 1; i < n; i++) {
		int temp;
		std::cin >> temp;

        node left = sum_tree(0, temp - 1, 0, MAX - 1, 1);
        node right = sum_tree(temp + 1, MAX - 1, 0, MAX - 1, 1);

        long long sum = (temp * left.num - left.sum + right.sum - temp * right.num) % MOD;
        result = (result * sum) % MOD;

        insert(temp, temp);
	}

    std::cout << result;
}

void insert(int index, int num) {
	int point = index + MAX;

	segtree[point].sum += num;
    segtree[point].num++;
	while (point > 0) {
		point /= 2;
		segtree[point].sum += num;
        segtree[point].num++;
	}
}

node sum_tree(int start, int end, int left, int right, int point) {
	if (left > end || right < start) {
        node temp;
        return temp;
    }
	if (start <= left && end >= right) return segtree[point];

	int mid = (left + right) / 2;
    node temp;
    node left_node = sum_tree(start, end, left, mid, point * 2);
    node right_node = sum_tree(start, end, mid + 1, right, point * 2 + 1);
    temp.sum = left_node.sum + right_node.sum;
    temp.num = left_node.num + right_node.num;
	return temp;
}