#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	// Circle shape
	sf::CircleShape circle;
	float circleSpeed;

	// Rectangle shape
	sf::RectangleShape rectangle;
	float rectangleSpeed;

	// DVD shape
	sf::CircleShape DVD;

	// Text
	sf::Text text;
	sf::Text trackingTextSpeed;
	sf::Font font;
	float textXSpeed;
	float textYSpeed;
	bool textXNegative;
	bool textYNegative;

	// Int variable to track position of right side of the screen
	int side;
	int bottom;
};