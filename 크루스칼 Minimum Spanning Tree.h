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
	
	// 디스조인트-셋 포레스트
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

		// 만약 X와 Y가 같은 트리에 있다면 그대로 종료
		if (root_x == root_y)
			return;

		// 작은 랭크의 트리를 큰 랭크의 트리 쪽으로 병합
		if (nodes[root_x].rank > nodes[root_y].rank)
			std::swap(root_x, root_y);

		nodes[root_x].parent = nodes[root_y].parent;
		nodes[root_y].rank++;
	}
};

// 그래프 자료 구현
template <typename T>
struct Edge
{
	unsigned src;
	unsigned dst;
	T weight;

	// Edge 객체 비교는 가중치를 이용
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
	// N개의 정점으로 구성된 그래프
	Graph(unsigned N) : V(N) {}

	// 그래프의 정점 개수 반환
	auto vertices() const { return V; }
	// 전체 에지 리스트 반환
	auto& edges() const { return edge_list; }
	// 정점 v에서 나가는 모든 에지 반환
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
		// 에지 양 끝 정점 ID가 유효한지 검사
		if (e.src >= 1 && e.src <= V && e.dst <= V)
			edge_list.emplace_back(e);
		else
			std::cerr << "에러: 유효 범위를 벗어난 정점!" << std::endl;
	}

	// 표준 출력 스트림 지원
	template <typename U>
	friend std::ostream& operator << (std::ostream& os, const Graph<U>& G);

private:
	unsigned V; // 정점 개수
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
	// 에지 가중치를 이용한 최소 힙 구성
	std::priority_queue<Edge<T>, std::vector<Edge<T>>, std::greater<Edge<T>>> edge_min_heap;

	// 모든 에지를 최소 힙에 추가
	for (auto& e : G.edges())
	{
		edge_min_heap.push(e);
	}

	// 정점 개수에 해당하는 크기의 디스조인트-셋 자료 구조 생성 및 초기화
	auto N = G.vertices();
	SimpleDisjointSet dset(N);
	for (unsigned i = 0; i < N; i++)
		dset.make_set(i);

	// 디스조인트-셋 자료 구조를 이용하여 최소 신장 트리 구하기
	Graph<T> MST(N);
	while (!edge_min_heap.empty())
	{
		// 최소 힙에서 최소 가중치 에지를 추출
		auto e = edge_min_heap.top();
		edge_min_heap.pop();

		// 선택한 에지가 사이클을 생성하지 않으면 해당 에지를 MST에 추가
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

	// 1번 정점부터 차례대로 검사
	for (unsigned i = 1; i < size; i++)
	{
		auto outgoing_edges = G.edges(i);

		// i번째 정점과 인접해 있는 정점들의 현재 색상
		std::set<unsigned> neighbours;
		for (auto& e : outgoing_edges)
		{
			neighbours.insert(assigned_colors[e.dst]);
		}

		// 인접한 정점에 칠해지지 않은 색상 중에서 가장 적은 숫자의 색상을 선택
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
