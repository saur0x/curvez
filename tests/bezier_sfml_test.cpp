#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_FORCE_NO_CTOR_INIT

#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/color_space.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cstdint>
#include <cstdio>
#include <vector>

#include "bezier.hpp"


constexpr std::size_t WIDTH = 500, HEIGHT = 500;
constexpr float PI = 3.141592653589793f;


sf::Vector2f glm_to_sf2(glm::vec2 vec)
{
	return sf::Vector2f(vec.x, vec.y);
}

glm::vec2 sf_to_glm2(sf::Vector2f vec)
{
	return glm::vec2(vec.x, vec.y);
}


int main(int argc, char **argv)
{	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 600), "My Window", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	// window.setFramerateLimit(60);

	std::vector<glm::vec2> vertices = {
		glm::vec2(100, 100),
		glm::vec2(350, 100),
		glm::vec2(400, 350),
		glm::vec2(100, 350),
		glm::vec2(300, 400),
		glm::vec2(350, 550),
	};

	sf::VertexArray lines(sf::LineStrip, vertices.size());
	for (std::size_t i = 0; i < vertices.size(); ++i) {
		lines[i] = sf::Vertex(glm_to_sf2(vertices[i]), sf::Color::White);
	}

	sf::VertexArray curve;
	curve.setPrimitiveType(sf::LineStrip);

	for (float t = 0.0f; t <= 1.001f; t += 0.001f) {
		glm::vec2 point = bezier::npoint(vertices, t);

		glm::vec3 rgb = glm::rgbColor(glm::vec3(t * 360, 1, 1));
		rgb *= 255.0f;

		curve.append(sf::Vertex(glm_to_sf2(point), sf::Color(rgb.r, rgb.g, rgb.b)));
	}

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			window.clear(sf::Color::Black);

			window.draw(lines);
			window.draw(curve);

			window.display();
		}
	}

	return 0;
}