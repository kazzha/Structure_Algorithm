#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stack>

// 너비 우선 탐색(BFS, Breadth-First Search) - 에지 가중치 사용 X

namespace Search
{
	template <typename T>
	struct Edge
	{
		unsigned src;
		unsigned dst;
		T weight;
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
	auto creat_reference_graph()
	{
		Graph<T> G(9);

		std::map<unsigned, std::vector<std::pair<unsigned, T>>> edge_map;
		edge_map[1] = { {2,0},{5,0} };
		edge_map[2] = { {1,0},{5,0},{4,0} };
		edge_map[3] = { {4,0},{7,0} };
		edge_map[4] = { {2,0},{3,0},{5,0},{6,0},{8,0} };
		edge_map[5] = { {1,0},{2,0},{4,0},{8,0} };
		edge_map[6] = { {4,0},{7,0}, {8,0} };
		edge_map[7] = { {3,0},{6,0} };
		edge_map[8] = { {4,0},{5,0},{6,0} };

		for (auto& i : edge_map)
			for (auto& j : i.second)
				G.add_edge(Edge<T>{ i.first, j.first, j.second});

		return G;
	}

	template <typename T>
	auto breadth_first_search(const Graph<T>& G, unsigned start)
	{
		std::queue<unsigned> queue;
		std::set<unsigned> visited; // 방문한 정점
		std::vector<unsigned> visit_order; // 방문 순서
		queue.push(start);

		while (!queue.empty())
		{
			auto current_vertex = queue.front();
			queue.pop();

			// 현재 정점을 이전에 방문하지 않았다면
			if (visited.find(current_vertex) == visited.end())
			{
				visited.insert(current_vertex);
				visit_order.push_back(current_vertex);

				for (auto& e : G.edges(current_vertex))
				{
					// 인접한 정점 중에서 방문하지 않은 정점이 있다면 큐에 추가
					if (visited.find(e.dst) == visited.end())
					{
						queue.push(e.dst);
					}
				}
			}
		}
		return visit_order;
	}

	template <typename T>
	auto depth_first_search(const Graph<T>& G, unsigned start)
	{
		std::stack<unsigned> stack;
		std::set<unsigned> visited; // 방문한 정점
		std::vector<unsigned> visit_order; // 방문 순서
		stack.push(start);

		while (!stack.empty())
		{
			auto current_vertex = stack.top();
			stack.pop();

			// 현재 정점을 이전에 방문하지 않았다면
			if (visited.find(current_vertex) == visited.end())
			{
				visited.insert(current_vertex);
				visit_order.push_back(current_vertex);

				for (auto& e : G.edges(current_vertex))
				{
					// 인접한 정점 중에서 방문하지 않은 정점이 있다면 스택에 추가
					if (visited.find(e.dst) == visited.end())
					{
						stack.push(e.dst);
					}
				}
			}
		}
		return visit_order;
	}
}
