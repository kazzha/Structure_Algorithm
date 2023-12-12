#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <string>


class SimpleDisjointSet
{
private:
	struct Node
	{
		unsigned id;
		unsigned rank;
		unsigned parent;

		Node(unsigned _id) : id(_id), rank(0), parent(_id) {}

		bool operator != (const Node& n) const
		{
			return this->id != n.id;
		}
	};
	
	// ������Ʈ-�� ������Ʈ
	std::vector<Node> nodes;

public:
	SimpleDisjointSet(unsigned N)
	{
		nodes.reserve(N);
	}
	 
	void make_set(const unsigned& x)
	{
		nodes.emplace_back(x);
	}

	unsigned find(unsigned x)
	{
		auto node_it = find_if(nodes.begin(), nodes.end(),
			[x](auto n) { return n.id == x; });
		unsigned node_id = (*node_it).id;

		while (node_id != nodes[node_id].parent)
		{
			node_id = nodes[node_id].parent;
		}

		return node_id;
	}

	void union_sets(unsigned x, unsigned y)
	{
		auto root_x = find(x);
		auto root_y = find(y);

		// ���� X�� Y�� ���� Ʈ���� �ִٸ� �״�� ����
		if (root_x == root_y)
			return;

		// ���� ��ũ�� Ʈ���� ū ��ũ�� Ʈ�� ������ ����
		if (nodes[root_x].rank > nodes[root_y].rank)
			std::swap(root_x, root_y);

		nodes[root_x].parent = nodes[root_y].parent;
		nodes[root_y].rank++;
	}
};

// �׷��� �ڷ� ����
template <typename T>
struct Edge
{
	unsigned src;
	unsigned dst;
	T weight;

	// Edge ��ü �񱳴� ����ġ�� �̿�
	inline bool operator < (const Edge<T>& e) const
	{
		return this->weight < e.weight;
	}
	inline bool operator > (const Edge<T>& e) const
	{
		return this->weight > e.weight;
	}
};

template <typename T>
class Graph
{
public:
	// N���� �������� ������ �׷���
	Graph(unsigned N) : V(N) {}

	// �׷����� ���� ���� ��ȯ
	auto vertices() const { return V; }
	// ��ü ���� ����Ʈ ��ȯ
	auto& edges() const { return edge_list; }
	// ���� v���� ������ ��� ���� ��ȯ
	auto edges(unsigned v) const
	{
		std::vector<Edge<T>> edges_from_v;
		for (auto& e : edge_list)
		{
			if (e.src == v)
				edges_from_v.emplace_back(e);
		}
		return edges_from_v;
	}

	void add_edge(Edge<T>&& e)
	{
		// ���� �� �� ���� ID�� ��ȿ���� �˻�
		if (e.src >= 1 && e.src <= V && e.dst <= V)
			edge_list.emplace_back(e);
		else
			std::cerr << "����: ��ȿ ������ ��� ����!" << std::endl;
	}

	// ǥ�� ��� ��Ʈ�� ����
	template <typename U>
	friend std::ostream& operator << (std::ostream& os, const Graph<U>& G);

private:
	unsigned V; // ���� ����
	std::vector<Edge<T>> edge_list;
};

template <typename U>
std::ostream& operator << (std::ostream& os, const Graph<U>& G)
{
	for (unsigned i = 1; i < G.vertices(); i++)
	{
		os << i << ":\t";
		auto edges = G.edges(i);
		for (auto& e : edges)
			os << "{" << e.dst << ": " << e.weight << "}, ";

		os << std::endl;
	}
	
	return os;
}

template <typename T>
Graph<T> minimum_spanning_tree(const Graph<T>& G)
{
	// ���� ����ġ�� �̿��� �ּ� �� ����
	std::priority_queue<Edge<T>, std::vector<Edge<T>>, std::greater<Edge<T>>> edge_min_heap;

	// ��� ������ �ּ� ���� �߰�
	for (auto& e : G.edges())
	{
		edge_min_heap.push(e);
	}

	// ���� ������ �ش��ϴ� ũ���� ������Ʈ-�� �ڷ� ���� ���� �� �ʱ�ȭ
	auto N = G.vertices();
	SimpleDisjointSet dset(N);
	for (unsigned i = 0; i < N; i++)
		dset.make_set(i);

	// ������Ʈ-�� �ڷ� ������ �̿��Ͽ� �ּ� ���� Ʈ�� ���ϱ�
	Graph<T> MST(N);
	while (!edge_min_heap.empty())
	{
		// �ּ� ������ �ּ� ����ġ ������ ����
		auto e = edge_min_heap.top();
		edge_min_heap.pop();

		// ������ ������ ����Ŭ�� �������� ������ �ش� ������ MST�� �߰�
		if (dset.find(e.src) != dset.find(e.dst))
		{
			MST.add_edge(Edge<T>{e.src, e.dst, e.weight});
			dset.union_sets(e.src, e.dst);
		}
	}
	return MST;
}

// greedy graph coloring
std::unordered_map<unsigned, std::string> color_map = {
	{1, "Red"},
	{2, "Blue"},
	{3, "Green"},
	{4, "Yellow"},
	{5, "Black"},
	{6, "White"}
};

template<typename T>
auto greedy_coloring(const Graph<T>& G)
{
	auto size = G.vertices();
	std::vector<unsigned> assigned_colors(size);

	// 1�� �������� ���ʴ�� �˻�
	for (unsigned i = 1; i < size; i++)
	{
		auto outgoing_edges = G.edges(i);

		// i��° ������ ������ �ִ� �������� ���� ����
		std::set<unsigned> neighbours;
		for (auto& e : outgoing_edges)
		{
			neighbours.insert(assigned_colors[e.dst]);
		}

		// ������ ������ ĥ������ ���� ���� �߿��� ���� ���� ������ ������ ����
		auto smallest = 1;
		for (; smallest <= color_map.size(); smallest++)
		{
			if (neighbours.find(smallest) == neighbours.end())
				break;
		}
		assigned_colors[i] = smallest;
	}
	return assigned_colors;
}

template<typename T>
void print_colors(std::vector<T>& colors)
{
	for (auto i = 1; i < colors.size(); i++)
	{
		std::cout << i << ": " << color_map[colors[i]] << std::endl;
	}
}
