#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using pair_vector = std::vector<std::pair<int, int>>;

enum class city :int
{
	MOSCOW,
	LONDON,
	SEOUL,
	SEATTLE,
	DUBAI,
	SYDNEY
};

std::ostream& operator << (std::ostream& os, const city c)
{
	switch (c)
	{
	case city::LONDON:
		os << "런던";
		return os;

	case city::MOSCOW:
		os << "모스크바";
		return os;

	case city::SEOUL:
		os << "서울";
		return os;

	case city::SEATTLE:
		os << "시애틀";
		return os;

	case city::DUBAI:
		os << "두바이";
		return os;

	case city::SYDNEY:
		os << "시드니";
		return os;

	default:
		break;
	}
}


class graph
{
	std::vector<pair_vector> data;

public:
	graph(int n)
	{
		data = std::vector<pair_vector>(n, pair_vector());
	}

	void addEdge(const city c1, const city c2, int dis)
	{
		std::cout << "에지 추가: " << c1 << "-" << c2 << "=" << dis << std::endl;

		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		data[n1].push_back({ n2, dis });
		data[n2].push_back({ n1, dis });
	}

	void removeEdge(const city c1, const city c2)
	{
		std::cout << "에지 삭제: " << c1 << "-" << c2 << std::endl;

		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		std::remove_if(data[n1].begin(), data[n1].end(), [n2](const auto& pair){
			return pair.first == n2;
		});
		std::remove_if(data[n2].begin(), data[n2].end(), [n1](const auto& pair) {
			return pair.first == n1;
			});
	}
};

