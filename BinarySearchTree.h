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
			std::cout << value << "��(��) ã�ҽ��ϴ�." << std::endl;
			return current;
		}

		if (value < current->mData)
		{
			std::cout << current->mData << "���� �������� �̵�->";
			return find_impl(current->mLeft, value);
		}

		std::cout << current->mRight << "���� ���������� �̵�->";
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
			if (!start->mLeft) // �ڽĳ�尡 ���ų� ���� ��尡 ����
			{
				auto tmp = start->mRight;
				delete start;
				return tmp;
			}

			if (!start->mRight) // ������ ��尡 ���� ���
			{
				auto tmp = start->mLeft;
				delete start;
				return tmp;
			}

			// �ڽ� ��尡 �� �� �ִ� ��� - �ļӳ���� ���� ��Ʈ ��忡 ����
			auto succNode = successor(start);
			start->mData = succNode->mData;

			// ������ ���� Ʈ������ �ļ� ��带 ����
			start->mRight = delete_impl(start->mRight, succNode->mData);
		}

		return start;
	}


};