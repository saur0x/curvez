#include "bernstein.hpp"

#include <iostream>
#include <cstdint>
#include <cassert>

using namespace bernstein;


int main()
{
	constexpr std::size_t N = 29;
	PascalTriangle<std::uint64_t> triangle(N);

	for (std::uint64_t n = 0; n <= N; ++n) {
		for (std::uint64_t r = 0; r <= n; ++r) {
			assert(ncr(n, r) == ncr(n, n - r));
			assert(triangle.get(n, r) == triangle.get(n, n - r));
			assert(ncr(n, r) == triangle.get(n, r));
		}
	}

	return 0;
}