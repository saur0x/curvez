#ifndef DECASTELJAU_H
#define DECASTELJAU_H


#include <glm/vec2.hpp>
#include <vector>

namespace decasteljau {

using vec2 = glm::vec2;


vec2 lerp(vec2 a, vec2 b, float t)
{
	return b * t + a * (1 - t);
}


vec2 npoint(std::vector<vec2>& vertices, float t)
{
	std::size_t size = vertices.size();

	if (size == 1)
		return vertices[0];

	std::vector<vec2> intermediate_vertices(size - 1);

	for (std::size_t i = 0; i < size - 1; ++i)
		intermediate_vertices[i] = lerp(vertices[i], vertices[i + 1], t);

	return npoint(intermediate_vertices, t);
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

#endif // DECASTELJAU_H