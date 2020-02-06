#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects

	// Circle that bounces back and forth
	circle.setRadius(25);
	circle.setFillColor(sf::Color::Blue);
	circle.setPosition(0, 300);
	circleSpeed = 200.0f;

	// Rectangle that user controls
	rectangle.setSize(sf::Vector2f(25, 25));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(100, 100);
	rectangleSpeed = 100.0f;

	// Loading font for text
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font.";
	}

	// Text that bounces off each wall of the screen
	text.setString("DVD");
	text.setCharacterSize(25);
	text.setPosition(0, 0);
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setOutlineThickness(2.5);
	text.setOutlineColor(sf::Color::Black);
	textXSpeed = 100.0f;
	textYSpeed = 100.0f;
	textXNegative = false;
	textYNegative = false;

	// Text for showing speed of bouncing text
	trackingTextSpeed.setCharacterSize(16);
	trackingTextSpeed.setFont(font);
	trackingTextSpeed.setPosition(400, 0);
	trackingTextSpeed.setFillColor(sf::Color::Yellow);

	// Oval to follow "DVD" text
	DVD.setRadius(5);
	DVD.setScale(1, 0.33);
	DVD.setFillColor(sf::Color::Transparent);
	DVD.setOutlineColor(sf::Color::Black);
	DVD.setOutlineThickness(20);
	DVD.setPosition(0, 0);


}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	// W moves rectangle up
	if (input->isKeyDown(sf::Keyboard::W))
	{
		rectangle.move(0, dt * -rectangleSpeed);
	}

	// S moves rectangle down
	if (input->isKeyDown(sf::Keyboard::S))
	{
		rectangle.move(0, dt * rectangleSpeed);
	}

	// A moves rectangle left
	if (input->isKeyDown(sf::Keyboard::A))
	{
		rectangle.move(dt * -rectangleSpeed, 0);
	}

	// D moves rectangle right
	if (input->isKeyDown(sf::Keyboard::D))
	{
		rectangle.move(dt * rectangleSpeed, 0);
	}

	// Increases speed of bouncing text when Add key is pressed
	if (input->isKeyDown(sf::Keyboard::Add))
	{
		input->setKeyUp(sf::Keyboard::Add);

		if (textXNegative == false && textYNegative == false)
		{
			textXSpeed += 50;
			textYSpeed += 50;
		}

		if (textXNegative == true && textYNegative == true)
		{
			textXSpeed -= 50;
			textYSpeed -= 50;
		}

		if (textXNegative == true && textYNegative == false)
		{
			textXSpeed -= 50;
			textYSpeed += 50;
		}

		if (textXNegative == false && textYNegative == true)
		{
			textXSpeed += 50;
			textYSpeed -= 50;
		}
	}

	// Decreases speed of bouncing text when Subtract key is pressed
	if (input->isKeyDown(sf::Keyboard::Subtract))
	{
		input->setKeyUp(sf::Keyboard::Subtract);

		if (textXNegative == false && textYNegative == false)
		{
			textXSpeed -= 50;
			textYSpeed -= 50;
		}

		if (textXNegative == true && textYNegative == true)
		{
			textXSpeed += 50;
			textYSpeed += 50;
		}

		if (textXNegative == true && textYNegative == false)
		{
			textXSpeed += 50;
			textYSpeed -= 50;
		}

		if (textXNegative == false && textYNegative == true)
		{
			textXSpeed -= 50;
			textYSpeed += 50;
		}

	}
}

// Update game objects
void Level::update(float dt)
{
	// Gets x and y sizes of window
	side = window->getSize().x;
	bottom = window->getSize().y;

	// Text to be displayed with current speed
	trackingTextSpeed.setString("Current speed in X axis: " + std::to_string(textXSpeed) + "\nCurrent speed in Y axis: " + std::to_string(textYSpeed));

	// Inverts the circle's direction when it reaches the side
	if (circle.getPosition().x > side - 50 || circle.getPosition().x < 0)
	{
		circleSpeed = -circleSpeed;
	}

	// Moves the circle right if circle speed is positive, left if negative
	circle.move(dt * circleSpeed, 0);

	// If statements to make sure user controlled rectangle doesn't leave screen
	if (rectangle.getPosition().x > side - 25)
	{
		rectangle.setPosition(side - 25, rectangle.getPosition().y);
	}
	if (rectangle.getPosition().x < 0)
	{
		rectangle.setPosition(0, rectangle.getPosition().y);
	}
	if (rectangle.getPosition().y > bottom - 25)
	{
		rectangle.setPosition(rectangle.getPosition().x, bottom - 25);
	}
	if (rectangle.getPosition().y < 0)
	{
		rectangle.setPosition(rectangle.getPosition().x, 0);
	}

	// For tracking when bouncing text has reached end of screen and inverting its direction/speed
	if (text.getPosition().x >= side - 53 || text.getPosition().x <= 0)
	{
		textXSpeed = -textXSpeed;
		textXNegative = !textXNegative;
	}
	if (text.getPosition().y >= bottom - 43|| text.getPosition().y <= 0)
	{
		textYSpeed = -textYSpeed;
		textYNegative = !textYNegative;
	}

	// Moves bouncing text
	text.move(dt * textXSpeed, dt * textYSpeed);

	// Locks oval position to follow the text
	DVD.setPosition(text.getPosition().x + 22, text.getPosition().y + 35);
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(circle);
	window->draw(rectangle);
	window->draw(text);
	window->draw(trackingTextSpeed);
	window->draw(DVD);

	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}