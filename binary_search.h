#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// ���� �˻�
bool binary_search(int N, std::vector<int>& S)
{
	auto first = S.begin();
	auto last = S.end();

	while (true)
	{
		// ���� �˻� ������ �߰� ���Ҹ� mid_element�� ����
		auto range_length = std::distance(first, last);
		auto mid_element_index = std::floor(range_length / 2);
		auto mid_element = *(first + mid_element_index);

		// mid_element�� N ���� ��
		if (mid_element == N)
		{
			std::cout << N;
			return true;
		}
		else if (mid_element > N)
			std::advance(last, -mid_element_index);
		if (mid_element < N)
			std::advance(first, mid_element_index);

		// ���� �˻� ������ �ϳ��� ���Ҹ� ���� �ִٸ� false ��ȯ
		if (range_length == 1)
			return false;
	}
}
