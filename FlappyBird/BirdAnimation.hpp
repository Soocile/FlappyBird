
#pragma once

#include <SFML/Graphics.hpp>

#include<vector>
#include<iostream>


#ifndef BirdAnimation_HPP

#define BirdAnimation_HPP


class BirdAnimation {
public:

	BirdAnimation(const std::string& file_name);

	void render(sf::RenderWindow& window);

 
	void update(float gravity);


	 inline sf::FloatRect get_local_bounds() const {

		return sprite.getLocalBounds();
	}


	 inline sf::FloatRect get_global_bounds() const {

		return sprite.getGlobalBounds();
	}

	 inline float get_pos_x() const {

		 return sprite.getPosition().x;
	 }

	 inline float get_pos_y() const {

		 return sprite.getPosition().y;
	 }

	 void load_frames(const std::string& file_name);


	  inline void set_position(float x, float y) {

		  sprite.setPosition(x, y);
	 }

	  inline void move_object(float jumpvelocity) {

		  velocityY = -jumpvelocity;
		
	  }

private:

	float velocityY = 0.0f;

	std::vector<sf::Texture> frames; 
	sf::Sprite sprite;
	int animationState = 0;
	sf::Clock animationClock;
	const int frameDurationMs = 150;

	
	
};




#endif //BirdAnimation_HPP




