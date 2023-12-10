#pragma once
#include <iostream>
#include <queue>
#include <vector>

class median
{
	std::priority_queue<int> maxHeap;
	std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

public:
	void insert(int data)
	{
		if (maxHeap.size() == 0)
		{
			maxHeap.push(data);
			return;
		}
		if (maxHeap.size() == maxHeap.size())
		{
			if (data <= get())
				maxHeap.push(data);
			else
				minHeap.push(data);
				
			return;
		}

		if (maxHeap.size() < minHeap.size())
		{
			if (data > get())
			{
				maxHeap.push(minHeap.top());
				minHeap.pop();
				minHeap.push(data);
			}
			else
				maxHeap.push(data);

			return;
		}

		if (data < get())
		{
			minHeap.push(maxHeap.top());
			maxHeap.pop();
			maxHeap.push(data);
		}
		else
			minHeap.push(data);
	}

	double get()
	{
		if (maxHeap.size() == minHeap.size())
			return (maxHeap.top() + minHeap.top()) / 2.0;
		
		if (maxHeap.size() < minHeap.size())
			return static_cast<double>(minHeap.top());
		
		return static_cast<double>(maxHeap.top());
	}
};