#include "BinarySearchTree.h"
#include "heap.h"
#include "greedy algorithm.h"
#include <list>
#include "크루스칼 Minimum Spanning Tree.h"

using namespace std;

int main()
{
	/*
	std::vector<Object> objects;
	objects.reserve(7);

	std::vector<int> weights{ 1,2,5,9,2,3,4 };
	std::vector<double> values{ 10,7,15,10,12,11,5 };
	for (auto i = 0; i < 7; i++)
	{
		objects.push_back(Object(i + 1, weights[i], values[i]));
	}

	// 사용할 수 있는 물건 정보 출력
	cout << "[사용할 수 있는 물건 정보]" << endl;
	for (auto& o : objects)
		cout << o << endl;
	cout << endl;

	// 분할 가능 배낭 문제 알고리즘 실행, 배낭의 최대 허용 무게는 7로 지정
	int knapsack_capacity = 7;
	auto solution = fill_knapsack(objects, knapsack_capacity);

	// 배낭에 넣을 물건 정보 출력
	cout << "[배낭에 넣을 물건들 ( 최대 용량 = " << knapsack_capacity << ")]" << endl;
	for (auto& o : solution)
		cout << o << endl;
	cout << endl;

	*/

	/*
	list<Work> test{ {1, 5, 9}, { 2,6, 20 }, { 3,16,19 }, { 4,7,10 }, { 5,9,19 }, { 6,10,19 }, {10, 4, 7} };

	vector<Work> solution = WorkSort(test);
	for (auto& w : solution)
	{
		cout << w << endl;
	}
	*/

	using T = unsigned;

	/*
	// 그래프 객체 생성
	Graph<T> G(9);

	map<unsigned, vector<pair<unsigned, T>>> edge_map;
	edge_map[1] = { {2,2},{5,3} };
	edge_map[2] = { {1,2},{5,5},{4,1} };
	edge_map[3] = { {4,2},{7,3} };
	edge_map[4] = { {2,1},{3,2},{5,2},{6,4},{8,5} };
	edge_map[5] = { {1,3},{2,5},{4,2 },{8,3} };
	edge_map[6] = { {4,4},{7,4}, {8,1} };
	edge_map[7] = { {3,3},{6,4} };
	edge_map[8] = { {4,5},{5,3},{6,1} };

	for (auto& i : edge_map)
		for (auto& j : i.second)
			G.add_edge(Edge<T>{i.first, j.first, j.second});

	cout << "[입력 그래프]" << endl;
	cout << G << endl;

	Graph<T> MST = minimum_spanning_tree(G);
	cout << "[최소 신장 트리]" << endl;
	cout << MST;
	
	*/
	Graph<T> G(9);

	map<unsigned, vector<pair<unsigned, T>>> edge_map;
	edge_map[1] = { {2,0},{5,0} };
	edge_map[2] = { {1,0},{5,0},{4,0} };
	edge_map[3] = { {4,0},{7,0} };
	edge_map[4] = { {2,0},{3,0},{5,0},{6,0},{8,0} };
	edge_map[5] = { {1,0},{2,0},{4,0},{8,0} };
	edge_map[6] = { {4,0},{7,0}, {8,0} };
	edge_map[7] = { {3,0},{6,0} };
	edge_map[8] = { {4,0},{5,0},{6,0} };

	for (auto& i : edge_map)
		for (auto& j : i.second)
			G.add_edge(Edge<T>{ i.first, j.first, j.second});

	cout << "[입력 그래프]" << endl;
	cout << G << endl;

	auto colors = greedy_coloring<T>(G);
	cout << "[그래프 컬러링]" << endl;
	print_colors(colors);

}