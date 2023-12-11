#include "BinarySearchTree.h"
#include "heap.h"
#include "greedy algorithm.h"
#include <list>

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

	list<Work> test{ {1, 5, 9}, { 2,6, 20 }, { 3,16,19 }, { 4,7,10 }, { 5,9,19 }, { 6,10,19 }, {10, 4, 7} };

	vector<Work> solution = WorkSort(test);
	for (auto& w : solution)
	{
		cout << w << endl;
	}
}