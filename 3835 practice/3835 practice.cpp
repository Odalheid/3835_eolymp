#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int get(const int &n, int *&subtree) {
	if (subtree[n] == n) return n;
	return subtree[n] = get(subtree[n], subtree);  
}

void merge(const int &a, const int &b, int *&subtree, int *&vertex_rank) {
	int ra = get(a, subtree), rb = get(b, subtree);
	if (vertex_rank[ra] < vertex_rank[rb]) subtree[ra] = rb;
	else if (vertex_rank[rb] < vertex_rank[ra]) subtree[rb] = ra;
	else {
		subtree[ra] = rb;
		vertex_rank[rb]++;
	}
}

int main()
{
	int vertices, edges; // vertices <= edges : Граф является связным.
	scanf("%i%i", &vertices, &edges);
	vector <pair<int, pair<int, int>>> v(edges);
	for (int i = 0; i < edges; ++i) {
		scanf("%i", &v[i].second.first); // vertex out
		scanf("%i", &v[i].second.second); // vertex in
		scanf("%i", &v[i].first); // weight
	}
	sort(v.begin(), v.end());
	int *subtree = new int[vertices];
	int *vertex_rank = new int[vertices];
	for (int i = 0; i < vertices; i++) {
		subtree[i] = i;
		vertex_rank[i] = 1;
	}
	int spanning_tree_weight = 0;
	for (int i = 0; i < edges; ++i) {
		if (get(v[i].second.first - 1, subtree) != get(v[i].second.second - 1, subtree)) {
			spanning_tree_weight += v[i].first;
			merge(v[i].second.first - 1, v[i].second.second - 1, subtree, vertex_rank);
		}
	}
	printf("%i", spanning_tree_weight);
	delete[] subtree;
	delete[] vertex_rank;
	return 0;
}