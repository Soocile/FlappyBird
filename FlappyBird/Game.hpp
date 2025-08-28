
#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<vector>
#include"Pipe.hpp"


#ifndef Game_HPP

#define Game_HPP



enum GameState {

	RUNNING,
	GAME_OVER,
	START_SCREEN

};

GameState get_game_state_running();

GameState get_game_state_over();

GameState get_game_state_start_screen();


class Game {
public:

	Game();

	void run();

	
	

private:

	void processEvents();

	void update();

	void render();

	void Restart_Game();

	GameState check_collision();


	sf::RenderWindow m_window;


	sf::Texture m_gameOverTexture;
	sf::Sprite m_gameOverSprite;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_background;

	sf::Texture m_redBirdDownTexture;
	sf::Texture m_redBirdMidTexture;
	sf::Texture m_redBirdUpTexture;
	sf::Texture m_pipe_texture;

	//new
	sf::Texture m_messageTexture;
	sf::Sprite m_messageSprite;

	sf::Sprite m_bird;
	
	std::vector<Pipe> m_pipes;

	sf::Clock m_animationclock;

	int m_birdAnimationState;

	float m_birdvelocityY = 0.0f;

	const int ANIMATION_FRAME_DURATION_MS = 125;


	sf::SoundBuffer m_wingBuffer, m_pointBuffer, m_hitBuffer, m_dieBuffer, m_swooshBuffer;
	sf::Sound m_wingSound, m_pointSound, m_hitSound, m_dieSound, m_swooshSound;

	GameState m_gamestate;

	sf::Font m_font;

	sf::Text m_newGameText;

	sf::Text m_quitText;


	sf::Text scoreText;

	int m_score = 0;
};





#endif //Game_HPP