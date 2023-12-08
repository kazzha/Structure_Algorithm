#pragma once
#include <iostream>

struct Node
{
	int mData;
	Node* mLeft;
	Node* mRight;
};

class BST
{
	Node* mRoot{};

public:
	BST(Node* mRoot = nullptr) {}
	~BST() {}

	Node* find(int value)
	{
		return find_impl(mRoot, value);
	}

	void insert(int value)
	{
		if (!mRoot)
			mRoot = new Node{ value, nullptr, nullptr };
		else
			insert_impl(mRoot, value);
	}

	void inOrder()
	{
		inOrder_impl(mRoot);
	}
private:
	Node* find_impl(Node* current, int value)
	{
		if (!current)
		{
			return nullptr;
		}

		if (current->mData == value)
		{
			std::cout << value << "을(를) 찾았습니다." << std::endl;
			return current;
		}

		if (value < current->mData)
		{
			std::cout << current->mData << "에서 왼쪽으로 이동->";
			return find_impl(current->mLeft, value);
		}

		std::cout << current->mRight << "에서 오른쪽으로 이동->";
		return find_impl(current->mRight, value);
	}

	void insert_impl(Node* current, int value)
	{
		if (value < current->mData)
		{
			if (!current->mLeft)
				current->mLeft = new Node{ value, nullptr, nullptr };
			else
				insert_impl(current->mLeft, value);
		}
		else
		{
			if (!current->mRight)
				current->mRight = new Node{ value, nullptr, nullptr };
			else
				insert_impl(current->mRight, value);
		}
	}
	
	void inOrder_impl(Node* start)
	{
		if (!start)
			return;

		inOrder_impl(start->mLeft);
		std::cout << start->mData << " ";
		inOrder_impl(start->mRight);
	}
};