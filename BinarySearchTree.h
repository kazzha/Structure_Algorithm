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
	Node* mRoot;

public:
	BST(Node* root = nullptr) : mRoot(root) {}
	~BST() {}

	int GetRoot()
	{
		return mRoot->mData;
	}

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

	Node* successor(Node* start)
	{
		auto current = start->mRight;
		while (current && current->mLeft)
			current = current->mLeft;

		return current;
	}

	void deleteValue(int value)
	{
		mRoot = delete_impl(mRoot, value);
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
	Node* delete_impl(Node* start, int value)
	{
		if (!start)
			return nullptr;

		if (value < start->mData)
			start->mLeft = delete_impl(start->mLeft, value);
		else if (value > start->mData)
			start->mRight = delete_impl(start->mRight, value);
		else
		{
			if (!start->mLeft) // 자식노드가 없거나 왼쪽 노드가 없음
			{
				auto tmp = start->mRight;
				delete start;
				return tmp;
			}

			if (!start->mRight) // 오른쪽 노드가 없는 경우
			{
				auto tmp = start->mLeft;
				delete start;
				return tmp;
			}

			// 자식 노드가 둘 다 있는 경우 - 후속노드의 수를 루트 노드에 삽입
			auto succNode = successor(start);
			start->mData = succNode->mData;

			// 오른쪽 서브 트리에서 후속 노드를 삭제
			start->mRight = delete_impl(start->mRight, succNode->mData);
		}

		return start;
	}


};