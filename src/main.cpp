#include "FastNoise.h"
#include "camera.hpp"
#include "chunk.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <array>
#include <fstream>
#include "glad.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = 4;
	settings.minorVersion = 2;
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1200, 700, 32), "KimeCraft 2.0",
							sf::Style::Titlebar | sf::Style::Close, settings);
	Chunk chunk;
	std::ofstream fout("debug.log");

	FastNoise perlin;
	perlin.SetFrequency(0.003);
	perlin.SetSeed(rand() % 10000);
	perlin.SetNoiseType(FastNoise::Perlin);
	for (int x = 0; x < 100; x++)
		for (int z = 0; z < 100; z++)
		{
			int y = ceil(perlin.GetNoise(x, z) * 100);
			chunk.blocks.push_back(Block(glm::vec3(x, y, z)));
		}
	chunk.generate_mesh();
	chunk.bind_mesh();
	window.setMouseCursorVisible(0);
	window.setFramerateLimit(60);
	Camera player;
	while (window.isOpen())
	{
		//sf::Mouse::setPosition(sf::Vector2i(100.0f, 100.0f));
		player.handle_input();
		player.upload_uniform();
		chunk.render();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.display();
	}
	return 0;
}