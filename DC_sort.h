#pragma once
#include <iostream>
#include <vector>

// 병합 정렬(Merge Sort) 
// - 컴퓨터의 메인 메모리보다 큰 용량의 데이터에서도 동작하는 외부 정렬 알고리즘으로
// 많은 원소로 구성된 전체 집합을 작은 크기의 부분집합으로 나눠 각각 정렬하고 순서를 유지하며 합치는 방식

template <typename T>
std::vector<T> merge(std::vector<T>& arr1, std::vector<T>& arr2) // 병합 파트
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
std::vector<T> merge_sort(std::vector<T> arr) // 분할 파트
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
	// 세 개의 반복자 생성(피벗, 백터의 시작과 마지막 원소)
	auto pivot_val = *begin; // 여기서는 첫 번째 원소를 피벗으로 설정
	auto left_iter = begin + 1;
	typename std::vector<T>::iterator right_iter = end;

	while (true)
	{
		// 벡터의 첫 번째 원소부터 시작해 피벗보다 큰 원소를 찾음
		while (*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
			left_iter++;

		// 벡터의 마지막 원소부터 시작해 역순으로 피벗보다 작은 원소를 찾음
		while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
			right_iter--;

		// 만약 left와 right가 같다면 교환할 원소가 없음
		// 그렇지 않으면 left와 right가 가리키는 원소를 서로 교환
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
	// 만약 벡터에 하나 이상의 원소가 있다면
	if (std::distance(begin, last) >= 1)
	{
		// 분할 작업을 수행
		auto partition_iter = partition<T>(begin, last);

		// 분할 작업에 의해 생성된 벡터를 재귀적으로 정렬
		quick_sort<T>(begin, partition_iter - 1);
		quick_sort<T>(partition_iter, last);
	}
}

template <typename T>
auto find_median(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last)
{
	// 정렬
	quick_sort<T>(begin, last);

	// 가운데(median) 원소 반복자를 반환
	return begin + (std::distance(begin, last) / 2);
}

template <typename T>
auto partition_using_given_pivot(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator end, typename std::vector<T>::iterator pivot)
{
	// 피벗 위치는 함수 인자로 주어지므로 벡터의 시작과 마지막 원소를 가리키는 반복자 정의
	auto left_iter = begin;
	auto right_iter = end -1;

	while (true)
	{
		// 벡터의 첫 번째 원소부터 시작해 피벗보다 큰 원소를 찾음
		while (*left_iter < *pivot && left_iter != right_iter)
			left_iter++;

		// 벡터의 마지막 원소부터 시작해 역순으로 피벗보다 작은 원소를 찾음
		while (*right_iter >= *pivot && left_iter != right_iter)
			right_iter--;

		// 만약 left와 right가 같다면 교환할 원소가 없음
		// 그렇지 않으면 left와 right가 가리키는 원소를 서로 교환
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
		// 다섯 개 원소로 구분하여 만들 부분 벡터 Vi의 개수 계산
		auto num_Vi = (size + 4) / 5;
		size_t j = 0;
		
		// 각각의 Vi에서 중앙값을 찾아 벡터 M에 저장
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
		// Vi의 중앙값으로 구성된 벡터 M에서 다시 중앙값 q를 찾음
		auto median_of_medians = (M.size() == 1) ? M.begin() :
			linear_time_select<T>(M.begin(), M.end() - 1, M.size() / 2);

		// 분할 연산을 적용하고 피벗 q의 위치 k를 찾음
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

