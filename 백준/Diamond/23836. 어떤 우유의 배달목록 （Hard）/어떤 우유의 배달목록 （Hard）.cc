#include <iostream>
#include <vector>
#define MAX 131072

std::vector<long long> segtree(MAX * 2, 0);
std::vector<long long> lazy(MAX * 2, 0);
std::vector<std::vector<int>> graph;
std::vector<bool> visit; // 노드 접근
std::vector<int> parent; // 노드 접근
std::vector<int> size; // 노드 접근
std::vector<int> renumber; // 노드 접근
std::vector<int> original; //리넘버링 접근
std::vector<std::pair<int, int>> chain;
std::vector<int> chain_num; // 노드 접근

void insert_range(int start, int end, int left, int right, int point, int num);
void insert_lazy(int left, int right, int point);
long long sum_tree(int start, int end, int left, int right, int point);
int dfs1(int n);
void dfs2(int n);
int count = 1;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL), std::cout.tie(NULL);
	int n, m;

	std::cin >> n;
	graph.resize(n + 1);
	parent.resize(n + 1);
	visit.resize(n + 1);
	size.resize(n + 1);
	renumber.resize(n + 1);
	original.resize(n + 1);
	chain_num.resize(n + 1);
	for (int i = 0; i < n - 1; i++) {
		int temp1, temp2;
		std::cin >> temp1 >> temp2;

		graph[temp1].push_back(temp2);
		graph[temp2].push_back(temp1);
	}
	if (n != 1) {
		size[1] = dfs1(1);

		visit.assign(n + 1, false);
		chain.push_back(std::pair<int, int>(1, 1));
		dfs2(1);
	}

	// 체인 확인용 코드
	/*
	for (int i = 0; i < chain.size(); i++) {
		std::cout << chain[i].first << " " << chain[i].second << "\n";
	}*/
	
	std::cin >> m;

	for (int i = 0; i < m; i++) {
		int temp;
		std::cin >> temp;
		if (temp == 1) {
			bool inverse = false;
			int point1, point2;
			std::cin >> point1 >> point2;

			// 같은 체인인 경우
			if (chain_num[point1] == chain_num[point2]) {
				if (renumber[point1] > renumber[point2]) {
					std::swap(point1, point2);
					inverse = !inverse;
				}
				int left = renumber[point1];
				int right = renumber[point2];
				if (!inverse) {
					//left -> right
					insert_range(left + 1, right, 0, MAX - 1, 1, 1);
					insert_range(right + 1, right + 1, 0, MAX - 1, 1, -(right - left));
				}
				else {
					//right -> left
					insert_range(left + 1, right, 0, MAX - 1, 1, -1);
					insert_range(left, left, 0, MAX - 1, 1, right - left);
				}
			}
			// 다른 체인인 경우
			else {
				int temp_point1 = point1;
				int temp_point2 = point2;

				// 지나는 노드 개수 조사
				int node_count = 0;
				while (chain_num[point1] != chain_num[point2]) {
					if (renumber[point1] > renumber[point2]) std::swap(point1, point2);
					node_count += renumber[point2] - chain[chain_num[point2]].first + 1;
					point2 = parent[original[chain[chain_num[point2]].first]];
				}

				if (renumber[point1] > renumber[point2]) std::swap(point1, point2);
				node_count += renumber[point2] - renumber[point1] + 1;
				int start = 0;
				int end = node_count - 1;

				point1 = temp_point1;
				point2 = temp_point2;

				while (chain_num[point1] != chain_num[point2]) {
					if (renumber[point1] > renumber[point2]) {
						// start -> parent
						insert_range(renumber[point1] + 1, renumber[point1] + 1, 0, MAX - 1, 1, -start);
						start += renumber[point1] - chain[chain_num[point1]].first + 1;
						if (chain[chain_num[point1]].first != renumber[point1]) insert_range(chain[chain_num[point1]].first + 1, renumber[point1], 0, MAX - 1, 1, -1);
						insert_range(chain[chain_num[point1]].first, chain[chain_num[point1]].first, 0, MAX - 1, 1, start - 1);
						point1 = parent[original[chain[chain_num[point1]].first]];
					}
					else {
						// end -> parent
						insert_range(renumber[point2] + 1, renumber[point2] + 1, 0, MAX - 1, 1, -end);
						if (chain[chain_num[point2]].first != renumber[point2]) insert_range(chain[chain_num[point2]].first + 1, renumber[point2], 0, MAX - 1, 1, 1);
						end -= renumber[point2] - chain[chain_num[point2]].first + 1;
						insert_range(chain[chain_num[point2]].first, chain[chain_num[point2]].first, 0, MAX - 1, 1, end + 1);
						point2 = parent[original[chain[chain_num[point2]].first]];
					}
				}

				if (renumber[point1] > renumber[point2]) {
					inverse = !inverse;
					std::swap(point1, point2);
				}
				if (!inverse) {
					// left -> right
					insert_range(renumber[point1], renumber[point1], 0, MAX - 1, 1, start);
					if(renumber[point1] != renumber[point2]) insert_range(renumber[point1] + 1, renumber[point2], 0, MAX - 1, 1, 1);
					start += renumber[point2] - renumber[point1] + 1;
					insert_range(renumber[point2] + 1, renumber[point2] + 1, 0, MAX - 1, 1, -(start - 1));
				}
				else {
					// right -> left
					insert_range(renumber[point2] + 1, renumber[point2] + 1, 0, MAX - 1, 1, -start);
					start += renumber[point2] - renumber[point1] + 1;
					if (renumber[point1] != renumber[point2]) insert_range(renumber[point1] + 1, renumber[point2], 0, MAX - 1, 1, -1);
					insert_range(renumber[point1], renumber[point1], 0, MAX - 1, 1, start - 1);
				}

			}
		}
		if (temp == 2) {
			int index;
			std::cin >> index;
			std::cout << sum_tree(1, renumber[index], 0, MAX - 1, 1) << "\n";
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

void insert_range(int start, int end, int left, int right, int point, int num) {
	insert_lazy(left, right, point);

	if (left > end || right < start) return;
	if (start <= left && end >= right) {
		segtree[point] += (right - left + 1) * num;
		if (left != right) {
			lazy[point * 2] += num;
			lazy[point * 2 + 1] += num;
		}
		return;
	}

	int mid = (left + right) / 2;
	insert_range(start, end, left, mid, point * 2, num);
	insert_range(start, end, mid + 1, right, point * 2 + 1, num);
	segtree[point] = segtree[point * 2] + segtree[point * 2 + 1];
}

void insert_lazy(int left, int right, int point) {
	segtree[point] += lazy[point] * (right - left + 1);
	if (left != right) {
		lazy[point * 2] += lazy[point];
		lazy[point * 2 + 1] += lazy[point];
	}
	lazy[point] = 0;
}

long long sum_tree(int start, int end, int left, int right, int point) {
	insert_lazy(left, right, point);
	if (left > end || right < start) return 0;
	if (left >= start && right <= end) return segtree[point];

	int mid = (left + right) / 2;
	return sum_tree(start, end, left, mid, point * 2) + sum_tree(start, end, mid + 1, right, point * 2 + 1);
}