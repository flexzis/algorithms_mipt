#include <iostream>
#include <string>
#include <vector>

using Bitmask = std::vector<bool>;
using std::string;

void Floyd(Bitmask& d, int N)
{
	for (auto k = 0; k < N; ++k)
		for (auto u = 0; u < N; ++u)
			if (d[u * N + k])
				for (auto v = 0; v < N; ++v)
					d[u * N + v] = d[u * N + v] | d[k * N + v];
}

int main()
{
	int N;
	std::cin >> N;
	Bitmask graph(N * N);
	for (auto i = 0; i < N; ++i)
	{
		string s;
		std::cin >> s;
		for (auto j = 0; j < N; ++j)
			graph[i * N + j] = s[j] - '0';
	}
	Floyd(graph, N);
	for (auto i = 0; i < N; ++i)
	{
		for (auto j = 0; j < N; ++j)
			std::cout << graph[i * N + j];
		std::cout << "\n";
	}
}