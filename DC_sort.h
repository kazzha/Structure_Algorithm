#pragma once
#include <iostream>
#include <vector>

// ���� ����(Merge Sort) 
// - ��ǻ���� ���� �޸𸮺��� ū �뷮�� �����Ϳ����� �����ϴ� �ܺ� ���� �˰�������
// ���� ���ҷ� ������ ��ü ������ ���� ũ���� �κ��������� ���� ���� �����ϰ� ������ �����ϸ� ��ġ�� ���

template <typename T>
std::vector<T> merge(std::vector<T>& arr1, std::vector<T>& arr2) // ���� ��Ʈ
{
	std::vector<T> merged;

	auto iter1 = arr1.begin();
	auto iter2 = arr2.begin();

	while (iter1 != arr1.end() && iter2 != arr2.end())
	{
		if (*iter1 < *iter2)
		{
			merged.emplace_back(*iter1);
			iter1++;
		}
		else
		{
			merged.emplace_back(*iter2);
			iter2++;
		}
	}
		if (iter1 != arr1.end())
		{
			for (; iter1 != arr1.end(); iter1++)
				merged.emplace_back(*iter1);
		}
		else
		{
			for (; iter2 != arr2.end(); iter2++)
				merged.emplace_back(*iter2);
		}
	return merged;
}

template <typename T>
std::vector<T> merge_sort(std::vector<T> arr) // ���� ��Ʈ
{
	if (arr.size() > 1)
	{
		auto mid = size_t(arr.size() / 2);
		auto left_half = merge_sort<T>(std::vector<T>(arr.begin(), arr.begin() + mid));
		auto right_half = merge_sort<T>(std::vector<T>(arr.begin() + mid, arr.end()));

		return merge<T>(left_half, right_half);
	}

	return arr;
}

template <typename T>
auto partition(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
{
	// �� ���� �ݺ��� ����(�ǹ�, ������ ���۰� ������ ����)
	auto pivot_val = *begin; // ���⼭�� ù ��° ���Ҹ� �ǹ����� ����
	auto left_iter = begin + 1;
	typename std::vector<T>::iterator right_iter = end;

	while (true)
	{
		// ������ ù ��° ���Һ��� ������ �ǹ����� ū ���Ҹ� ã��
		while (*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
			left_iter++;

		// ������ ������ ���Һ��� ������ �������� �ǹ����� ���� ���Ҹ� ã��
		while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
			right_iter--;

		// ���� left�� right�� ���ٸ� ��ȯ�� ���Ұ� ����
		// �׷��� ������ left�� right�� ����Ű�� ���Ҹ� ���� ��ȯ
		if (left_iter == right_iter)
			break;
		else
			std::iter_swap(left_iter, right_iter);
	}
	if (pivot_val > *right_iter)
		std::iter_swap(begin, right_iter);

	return right_iter;
}

template <typename T>
void quick_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last)
{
	// ���� ���Ϳ� �ϳ� �̻��� ���Ұ� �ִٸ�
	if (std::distance(begin, last) >= 1)
	{
		// ���� �۾��� ����
		auto partition_iter = partition<T>(begin, last);

		// ���� �۾��� ���� ������ ���͸� ��������� ����
		quick_sort<T>(begin, partition_iter - 1);
		quick_sort<T>(partition_iter, last);
	}
}

template <typename T>
auto find_median(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last)
{
	// ����
	quick_sort<T>(begin, last);

	// ���(median) ���� �ݺ��ڸ� ��ȯ
	return begin + (std::distance(begin, last) / 2);
}

template <typename T>
auto partition_using_given_pivot(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator end, typename std::vector<T>::iterator pivot)
{
	// �ǹ� ��ġ�� �Լ� ���ڷ� �־����Ƿ� ������ ���۰� ������ ���Ҹ� ����Ű�� �ݺ��� ����
	auto left_iter = begin;
	auto right_iter = end -1;

	while (true)
	{
		// ������ ù ��° ���Һ��� ������ �ǹ����� ū ���Ҹ� ã��
		while (*left_iter < *pivot && left_iter != right_iter)
			left_iter++;

		// ������ ������ ���Һ��� ������ �������� �ǹ����� ���� ���Ҹ� ã��
		while (*right_iter >= *pivot && left_iter != right_iter)
			right_iter--;

		// ���� left�� right�� ���ٸ� ��ȯ�� ���Ұ� ����
		// �׷��� ������ left�� right�� ����Ű�� ���Ҹ� ���� ��ȯ
		if (left_iter == right_iter)
			break;
		else
			std::iter_swap(left_iter, right_iter);
	}
	if (*pivot > *right_iter)
		std::iter_swap(pivot, right_iter);

	return right_iter;
}

template <typename T>
typename std::vector<T>::iterator linear_time_select(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last, size_t i)
{
	auto size = std::distance(begin, last);

	if (size > 0 && i <= size)
	{
		// �ټ� �� ���ҷ� �����Ͽ� ���� �κ� ���� Vi�� ���� ���
		auto num_Vi = (size + 4) / 5;
		size_t j = 0;
		
		// ������ Vi���� �߾Ӱ��� ã�� ���� M�� ����
		std::vector<T> M;
		for (; j < size / 5; j++)
		{
			auto b = begin + (j * 5);
			auto l = begin + (j * 5)+ 5 ;

			M.push_back(*find_median<T>(b, l));
		}

		if (j * 5 < size)
		{
			auto b = begin + (j * 5);
			auto l = begin + (j * 5) + (size % 5);

			M.push_back(*find_median<T>(b, l));
		}
		// Vi�� �߾Ӱ����� ������ ���� M���� �ٽ� �߾Ӱ� q�� ã��
		auto median_of_medians = (M.size() == 1) ? M.begin() :
			linear_time_select<T>(M.begin(), M.end() - 1, M.size() / 2);

		// ���� ������ �����ϰ� �ǹ� q�� ��ġ k�� ã��
		auto partition_iter = partition_using_given_pivot<T>(begin, last, median_of_medians);
		auto k = std::distance(begin, partition_iter) + 1;

		if (i == k)
			return partition_iter;
		else if (i < k)
			return linear_time_select<T>(begin, partition_iter - 1, i);
		else if (i > k)
			return linear_time_select<T>(partition_iter + 1, last, i - k);
	}
	else
	{
		return begin;
	}
}

