#ifndef BERNSTEIN_H
#define BERNSTEIN_H


#include <glm/vec2.hpp>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <math.h>

namespace bernstein {


/// `ncr` function works till n = 30 and r = 15 for `std::uint64_t`.
/// Alternate implementation:
/// for i in range(min(r, n - r)): ncr *= (n - i) / (i + 1)
/// BUG: Numerator can overflow for large n and small T size.
template <typename T = std::uint32_t>
static inline T ncr(T n, T r)
{
	T k = r <= n - r ? r : n - r;
	T numerator = 1, denominator = 1;

	while (k--) {
		numerator *= n - k;
		denominator *= k + 1;
	}

	return numerator / denominator;
}


template <typename T = std::uint32_t>
struct PascalTriangle
{
	std::size_t N;
	std::vector<T> triangle;

	PascalTriangle(std::size_t n = 20)
		: triangle((n + 1) * (n + 2) / 2), N(n)
	{
		for (std::size_t y = 0; y <= n; ++y) {
			set(y, 0, 1);
			set(y, y, 1);
		}

		for (std::size_t y = 2; y <= n; ++y) {
			for (std::size_t x = 1; x < y; ++x) {
				// n C r = n-1 C r-1 + n-1 C r
				set(y, x, get(y - 1, x - 1) + get(y - 1, x));
			}
		}
	}

	std::size_t index(std::size_t n, std::size_t r)
	{
		return n * (n + 1) / 2 + r;
	}

	void set(std::size_t n, std::size_t r, T ncr)
	{
		triangle[index(n, r)] = ncr;
	}

	T get(std::size_t n, std::size_t r)
	{
		return triangle[index(n, r)];
	}

	void show()
	{
		for (std::size_t y = 0; y <= N; ++y) {
			for (std::size_t x = 0; x <= y; ++x) {
				std::cout << get(y, x) << " ";
			}

			std::cout << std::endl;
		}
	}
};


using vec2 = glm::vec2;

vec2 npoint(std::vector<vec2>& vertices, float t)
{
	std::size_t size = vertices.size();
	std::size_t n = size - 1;

	glm::vec2 curve(0, 0);
	static PascalTriangle<std::uint32_t> triangle(50);

	float u = 1 - t;

	for (std::size_t r = 0; r < size; ++r) {
		// curve += vertex * (rth term of binomial expansion)
		curve += vertices[r] * (float) triangle.get(n, r) * powf(u, n - r) * powf(t, r);
	}

	return curve;
}

vec2 linear(vec2 a, vec2 b, float t)
{
	std::vector<vec2> vertices = { a, b };
	return npoint(vertices, t);
}

vec2 quadratic(vec2 a, vec2 b, vec2 c, float t)
{
	std::vector<vec2> vertices = { a, b, c };
	return npoint(vertices, t);
}

vec2 cubic(vec2 a, vec2 b, vec2 c, vec2 d, float t)
{
	std::vector<vec2> vertices = { a, b, c, d };
	return npoint(vertices, t);
}


}

#endif // BERNSTEIN_H