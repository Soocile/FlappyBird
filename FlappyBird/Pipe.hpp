

#pragma once

#include<SFML/Graphics.hpp>


class Pipe {

public:

	Pipe(float x, const sf::Texture& texture);

	void move(float speed);

	void render(sf::RenderWindow& window);

	bool isOffScreen();

	float getRightx();

	float getX() const;

	 float getGapY() const;

	 bool m_scored;

	sf::FloatRect get_top_bounds() const;
	sf::FloatRect get_bottom_bounds() const;

private:
	sf::Sprite m_topPipe;

	sf::Sprite m_bottomPipe;

};