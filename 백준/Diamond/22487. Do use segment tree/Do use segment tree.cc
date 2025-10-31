#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 262144
#define MIN -1000000000

class Node {
public:
	long long left = MIN;
	long long right = MIN;
	long long max = MIN;
	long long sum = 0;
};

std::vector<Node> segtree(MAX * 2);
std::vector<long long> lazy(MAX * 2, MIN);
std::vector<std::vector<int>> graph;
std::vector<bool> visit; // 노드 접근
std::vector<int> parent; // 노드 접근
std::vector<int> size; // 노드 접근
std::vector<int> renumber; // 노드 접근
std::vector<int> original; //리넘버링 접근
std::vector<std::pair<int, int>> chain;
std::vector<int> chain_num; // 노드 접근

void insert(int index, int num);
void insert_range(int start, int end, int left, int right, int point, long long num);
void insert_lazy(int left, int right, int point);
Node sum_tree(int start, int end, int left, int right, int point);
int dfs1(int n);
void dfs2(int n);
int count = 1;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);
	int n, m;

	std::cin >> n >> m;
	graph.resize(n + 1);
	parent.resize(n + 1);
	visit.resize(n + 1);
	size.resize(n + 1);
	renumber.resize(n + 1);
	original.resize(n + 1);
	chain_num.resize(n + 1);
	std::vector<int> vec(n + 1);

	for (int i = 1; i <= n; i++) {
		std::cin >> vec[i];
	}

	for (int i = 0; i < n - 1; i++) {
		int temp1, temp2;
		std::cin >> temp1 >> temp2;

		graph[temp1].push_back(temp2);
		graph[temp2].push_back(temp1);
	}
	if (n != 1) {
		dfs1(1);

		visit.assign(n + 1, false);
		chain.push_back(std::pair<int, int>(1, 1));
		dfs2(1);
	}

	for (int i = 1; i <= n; i++) {
		insert(renumber[i], vec[i]);
	}

	// 체인 확인용 코드
	/*
	for (int i = 0; i < chain.size(); i++) {
		std::cout << chain[i].first << " " << chain[i].second << "\n";
	}*/

	for (int i = 0; i < m; i++) {
		int temp;
		std::cin >> temp;

		if (temp == 2) {
			int point1, point2, dummy;
			std::cin >> point1 >> point2 >> dummy;

			// 같은 체인인 경우
			if (chain_num[point1] == chain_num[point2]) {
				if (renumber[point1] > renumber[point2]) std::swap(point1, point2);
				int left = renumber[point1];
				int right = renumber[point2];
				long long result = sum_tree(left, right, 0, MAX - 1, 1).max;
				std::cout << result << "\n";
			}
			// 다른 체인인 경우
			else {
				Node left_node;
				Node right_node;
				bool is_right = true;

				while (chain_num[point1] != chain_num[point2]) {
					if (renumber[point1] > renumber[point2]) {
						std::swap(point1, point2);
						is_right = !is_right;
					}
					Node temp = sum_tree(chain[chain_num[point2]].first, renumber[point2], 0, MAX - 1, 1);

					if (is_right) {
						Node new_right;
						new_right.sum = right_node.sum + temp.sum;
						new_right.left = std::max(temp.left, temp.sum + right_node.left);
						new_right.right = std::max(right_node.right, right_node.sum + temp.right);
						new_right.max = std::max({ temp.max, right_node.max, temp.right + right_node.left });
						right_node = new_right;
					}
					else {
						std::swap(temp.left, temp.right);
						Node new_left;
						new_left.sum = left_node.sum + temp.sum;
						new_left.left = std::max(left_node.left, left_node.sum + temp.left);
						new_left.right = std::max(temp.right, temp.sum + left_node.right);
						new_left.max = std::max({ temp.max, left_node.max, left_node.right + temp.left });
						left_node = new_left;
					}
					point2 = parent[original[chain[chain_num[point2]].first]];
				}
				if (renumber[point1] > renumber[point2]) {
					std::swap(point1, point2);
					is_right = !is_right;
				}

				Node temp = sum_tree(renumber[point1], renumber[point2], 0, MAX - 1, 1);
				if (!is_right) {
					//노드 뒤집기
					std::swap(temp.left, temp.right);

					Node new_left;
					new_left.sum = left_node.sum + temp.sum;
					new_left.left = std::max(left_node.left, left_node.sum + temp.left);
					new_left.right = std::max(temp.right, temp.sum + left_node.right);
					new_left.max = std::max({ temp.max, left_node.max, left_node.right + temp.left });
					left_node = new_left;
				}
				else {
					Node new_right;
					new_right.sum = right_node.sum + temp.sum;
					new_right.left = std::max(temp.left, temp.sum + right_node.left);
					new_right.right = std::max(right_node.right, right_node.sum + temp.right);
					new_right.max = std::max({ temp.max, right_node.max, temp.right + right_node.left });
					right_node = new_right;
				}

				std::cout << std::max({ left_node.max, right_node.max, left_node.right + right_node.left }) << "\n";
			}
		}

		if (temp == 1) {
			int point1, point2, val;
			std::cin >> point1 >> point2 >> val;
			if (renumber[point1] > renumber[point2]) std::swap(point1, point2);

			// 같은 체인인 경우
			if (chain_num[point1] == chain_num[point2]) {
				int left = renumber[point1];
				int right = renumber[point2];
				insert_range(left, right, 0, MAX - 1, 1, val);
			}
			// 다른 체인인 경우
			else {
				while (chain_num[point1] != chain_num[point2]) {
					if (renumber[point1] > renumber[point2]) std::swap(point1, point2);
					insert_range(chain[chain_num[point2]].first, renumber[point2], 0, MAX - 1, 1, val);
					point2 = parent[original[chain[chain_num[point2]].first]];
				}
				if (renumber[point1] > renumber[point2]) std::swap(point1, point2);
				insert_range(renumber[point1], renumber[point2], 0, MAX - 1, 1, val);
			}
		}

		// 확인용 코드
		/*
		for (int j = 1; j <= n; j++) {
			std::cout << sum_tree(1, original[j], 0, MAX - 1, 1) << " ";
		}
		std::cout << "\n";
		*/
	}
}

// 서브트리 크기 구하기`
int dfs1(int n) {
	int count = 0;
	visit[n] = true;

	for (int i = 0; i < graph[n].size(); i++) {
		int target = graph[n][i];
		if (visit[target]) {
			parent[n] = target;
			continue;
		}

		count += dfs1(target);

		//그래프 첫 간선에 가장 무거운 간선을 저장
		if (size[graph[n][0]] < size[target]) std::swap(graph[n][0], graph[n][i]);
	}

	//첫 간선이 부모 간선인 경우 예외 처리 (첫 간선이 부모 간선이고 다른 간선이 리프 노드인 경우 이런 현상이 발생함)
	if (graph[n][0] == parent[n] && graph[n].size() > 1) std::swap(graph[n][0], graph[n][1]);

	size[n] = count;
	return count + 1;
}

// 체인 정하고 리넘버링
void dfs2(int n) {
	visit[n] = true;
	original[count] = n;
	renumber[n] = count;
	chain_num[n] = chain.size() - 1;

	for (int i = 0; i < graph[n].size(); i++) {
		int target = graph[n][i];
		if (visit[target]) continue;
		count++;
		if (i == 0) {
			chain.back().second++;
		}

		if (i != 0) {
			chain.push_back(std::pair<int, int>(count, count));
		}

		dfs2(target);
	}
}

void insert(int index, int num) {
	int point = index + MAX;

	segtree[point].left = num;
	segtree[point].right = num;
	segtree[point].max = num;
	segtree[point].sum = num;
	while (point > 1) {
		point /= 2;
		segtree[point].sum = segtree[point * 2].sum + segtree[point * 2 + 1].sum;
		segtree[point].left = std::max(segtree[point * 2].left, segtree[point * 2].sum + segtree[point * 2 + 1].left);
		segtree[point].right = std::max(segtree[point * 2 + 1].right, segtree[point * 2 + 1].sum + segtree[point * 2].right);
		segtree[point].max = std::max({ segtree[point * 2].max, segtree[point * 2 + 1].max, segtree[point * 2].right + segtree[point * 2 + 1].left });
	}
}

void insert_range(int start, int end, int left, int right, int point, long long num) {
	insert_lazy(left, right, point);

	if (left > end || right < start) return;
	if (start <= left && end >= right) {
		segtree[point].sum = (long long)(right - left + 1) * num;
		segtree[point].max = std::max(num, (long long)(right - left + 1) * num);
		segtree[point].left = std::max(num, (long long)(right - left + 1) * num);
		segtree[point].right = std::max(num, (long long)(right - left + 1) * num);
		if (left != right) {
			lazy[point * 2] = num;
			lazy[point * 2 + 1] = num;
		}
		return;
	}

	int mid = (left + right) / 2;
	insert_range(start, end, left, mid, point * 2, num);
	insert_range(start, end, mid + 1, right, point * 2 + 1, num);
	segtree[point].sum = segtree[point * 2].sum + segtree[point * 2 + 1].sum;
	segtree[point].left = std::max(segtree[point * 2].left, segtree[point * 2].sum + segtree[point * 2 + 1].left);
	segtree[point].right = std::max(segtree[point * 2 + 1].right, segtree[point * 2 + 1].sum + segtree[point * 2].right);
	segtree[point].max = std::max({ segtree[point * 2].max, segtree[point * 2 + 1].max, segtree[point * 2].right + segtree[point * 2 + 1].left });
}

void insert_lazy(int left, int right, int point) {
	if (lazy[point] != MIN) {
		segtree[point].sum = (long long)(right - left + 1) * lazy[point];
		segtree[point].max = std::max(lazy[point], (long long)(right - left + 1) * lazy[point]);
		segtree[point].left = std::max(lazy[point], (long long)(right - left + 1) * lazy[point]);
		segtree[point].right = std::max(lazy[point], (long long)(right - left + 1) * lazy[point]);
		if (left != right) {
			lazy[point * 2] = lazy[point];
			lazy[point * 2 + 1] = lazy[point];
		}
		lazy[point] = MIN;
	}
}

Node sum_tree(int start, int end, int left, int right, int point) {
	insert_lazy(left, right, point);
	if (left > end || right < start) {
		Node temp;
		return temp;
	}
	if (start <= left && end >= right) return segtree[point];

	int mid = (left + right) / 2;
	Node left_node = sum_tree(start, end, left, mid, point * 2);
	Node right_node = sum_tree(start, end, mid + 1, right, point * 2 + 1);
	Node temp;

	temp.sum = left_node.sum + right_node.sum;
	temp.left = std::max(left_node.left, left_node.sum + right_node.left);
	temp.right = std::max(right_node.right, right_node.sum + left_node.right);
	temp.max = std::max({ left_node.max, right_node.max, left_node.right + right_node.left });
	return temp;
}