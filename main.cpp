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

	// ����� �� �ִ� ���� ���� ���
	cout << "[����� �� �ִ� ���� ����]" << endl;
	for (auto& o : objects)
		cout << o << endl;
	cout << endl;

	// ���� ���� �賶 ���� �˰��� ����, �賶�� �ִ� ��� ���Դ� 7�� ����
	int knapsack_capacity = 7;
	auto solution = fill_knapsack(objects, knapsack_capacity);

	// �賶�� ���� ���� ���� ���
	cout << "[�賶�� ���� ���ǵ� ( �ִ� �뷮 = " << knapsack_capacity << ")]" << endl;
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