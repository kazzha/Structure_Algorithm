#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>

// �ִ� �۾� �켱 �����ٸ� ���� - main���� sort�� �ϴ°� �߿�
template <typename T>
auto compute_waiting_times(std::vector<T>& service_times)
{
	std::vector<T> W(service_times.size());
	W[0] = 0;

	for (auto i = 1; i < service_times.size(); i++)
	{
		W[i] = W[i - 1] + service_times[i -1];
	}
	return W;
}

template <typename T>
void print_vector(std::vector<T>& V)
{
	for (auto& i : V)
	{ std::cout.width(2);
	std::cout << i << " ";
	}
	std::cout << std::endl;
}

template <typename T>
void compute_and_print_waiting_times(std::vector<T>& service_times)
{
	auto waiting_times = compute_waiting_times<int>(service_times);

	std::cout << "- ó�� �ð�: ";
	print_vector<T>(waiting_times);

	auto ave_waiting_times = std::accumulate(waiting_times.begin(), waiting_times.end(), 0.0) /
		waiting_times.size();
	std::cout << "- ��� ��� �ð�: " << ave_waiting_times;

	std::cout << std::endl;
}

// ���� ���� �賶 ����

class Object
{
public:
	int id;
	int weight;
	double value;
	double value_per_unit_weight;

	Object(int i, int w, double v) : id(i), weight(w), value(v), value_per_unit_weight(v / w) {}

	//std::sort() ���� ���
	inline bool operator < (const Object& obj) const
	{
		return this->value_per_unit_weight > obj.value_per_unit_weight;
	}

	// �ܼ� ��� ����. std::cout << obj << std::endl; �ڵ� ��� ����

	friend std::ostream& operator << (std::ostream& os, const Object& obj);
};

std::ostream& operator << (std::ostream& os, const Object& obj)
{
	os << "[" << obj.id << "] ����: " << obj.value << " \t����: "
		<< obj.weight << " kg\t���� ���� �� ����: " << obj.value_per_unit_weight;
	return os;
}

// ���� ���� �賶 ���� �˰��� ���� �Լ�
auto fill_knapsack(std::vector<Object>& objects, int knapsack_capacity)
{
	std::vector<Object> knapsack_contents;
	knapsack_contents.reserve(objects.size());

	// ������ ������������ ����(���� ���� �� ���� ����)-�������� ���� ����
	std::sort(objects.begin(), objects.end());

	// ���� ��ġ �ִ� ������ ���� �賶�� �߰�
	auto current_object = objects.begin();
	int current_total_weight = 0;
	while (current_total_weight < knapsack_capacity && current_object != objects.end())
	{
		knapsack_contents.push_back(*current_object);
		current_total_weight += current_object->weight;
		current_object++;
	}

	// ������ �߰��� ���ǿ� ���� �賶 �ִ� ��� ���԰� �ʰ��� ���
	int weight_of_last_obj_to_remove = current_total_weight - knapsack_capacity;
	Object& last_object = knapsack_contents.back();
	if (weight_of_last_obj_to_remove > 0)
	{
		last_object.weight -= weight_of_last_obj_to_remove;
		last_object.value -= last_object.value_per_unit_weight * weight_of_last_obj_to_remove;
	}
	return knapsack_contents;
}

// �۾� �����ٸ� ����
struct Work
{
	int ID;
	int startTime;
	int endTime;

	inline bool operator < (const Work& wor) const
	{
		return this->endTime < wor.endTime;
	}
	friend std::ostream& operator << (std::ostream& os, const Work& wor);
};

std::ostream& operator << (std::ostream& os, const Work& work)
{
	os << "[" << work.ID << "] " << work.startTime << " -> " << work.endTime;
	return os;
}

std::vector<Work> WorkSort(std::list<Work>& work)
{
	std::vector<Work> greedyWork;
	std::vector<Work> workVector(work.begin(), work.end());
	std::sort(workVector.begin(), workVector.end());
	while (!workVector.empty())
	{
		int fastEnd = workVector.begin()->endTime;
		greedyWork.push_back(*workVector.begin());
		workVector.erase(remove_if(workVector.begin(),workVector.end(),[fastEnd](const Work& w) {return w.startTime < fastEnd; }), workVector.end());
	}
	return greedyWork;
}
