#pragma once
#include <iostream>
#include <queue>

struct Node
{
	std::string mData;
	Node* mLeft;
	Node* mRight;
};

class org_tree
{
	Node* mRoot;

public:
	static org_tree createLoot(const std::string& value, Node* pLeft=nullptr, Node* pRight = nullptr)
	{
		org_tree tree;
		tree.mRoot = new Node{value, pLeft, pRight};
		return tree;
	}

	static Node* find(Node* root, const std::string& value)
	{
		if (root == nullptr)
			return nullptr;

		if (root->mData == value)
			return root;
		
		auto leftFound = find(root->mLeft, value);

		if (leftFound != nullptr)
			return leftFound;

		return find(root->mRight, value);

	}

	bool addSubOrdinate(const std::string& manager, const std::string& subordinate)
	{
		auto managerNode = find(mRoot, manager);

		if (!managerNode)
		{
			std::cout << manager << "을(를) 찾을 수 없습니다." << std::endl;
			return false;
		}

		if (managerNode->mLeft && managerNode->mRight)
		{
			std::cout << manager << "아래에 " << subordinate << "을(를) 추가할 수 없습니다." << std::endl;
			return false;
		}

		if (!managerNode->mLeft)
			managerNode->mLeft = new Node{ subordinate, nullptr, nullptr };
		else
			managerNode->mRight = new Node{ subordinate, nullptr, nullptr };

		std::cout << manager << "아래에 " << subordinate << "을(를) 추가했습니다." << std::endl;

		return true;
	}

	static void preOrder(Node* start)
	{
		if (!start)
			return;

		std::cout << start->mData << ", ";
		preOrder(start->mLeft);
		preOrder(start->mRight);
	}

	static void inOrder(Node* start)
	{
		if (!start)
			return;
		
		inOrder(start->mLeft);
		std::cout << start->mData << ", ";
		inOrder(start->mRight);
	}

	static void postOrder(Node* start)
	{
		if (!start)
			return;

		postOrder(start->mLeft);
		postOrder(start->mRight);
		std::cout << start->mData << ", ";
	}

	static void levelOrder(Node* start)
	{
		if (!start)
			return;

		std::queue<Node*> level;
		level.push(start);

		while (!level.empty())
		{
			int size = level.size();
			for (int i = 0; i < size; i++)
			{
				auto temp = level.front();
				level.pop();

				std::cout << temp->mData << ", ";
				if (temp->mLeft)
					level.push(temp->mLeft);
				if (temp->mRight)
					level.push(temp->mRight);
			}
			std::cout << std::endl;
		}
	}
};

