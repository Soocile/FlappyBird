


#include"Game.hpp"
#include<vector>


Game::Game() {


    
    

    //***SOUNDS***

    m_wingBuffer.loadFromFile("assets/Audio/wing.wav");
    m_pointBuffer.loadFromFile("assets/Audio/point.wav");
    m_hitBuffer.loadFromFile("assets/Audio/hit.wav");
    m_dieBuffer.loadFromFile("assets/Audio/die.wav");
    m_swooshBuffer.loadFromFile("assets/Audio/swoosh.wav");

    m_wingSound.setBuffer(m_wingBuffer);
    m_pointSound.setBuffer(m_pointBuffer);
    m_hitSound.setBuffer(m_hitBuffer);
    m_dieSound.setBuffer(m_dieBuffer);
    m_swooshSound.setBuffer(m_swooshBuffer);



	m_window.create(sf::VideoMode(1920, 1080), "Flappy Bird");

	m_window.setFramerateLimit(120);


	if (!m_backgroundTexture.loadFromFile("assets/Sprites/background-day.png")) {

		std::cerr << "background.png could not be loaded" << std::endl;
	}


	m_background.setTexture(m_backgroundTexture);

    //scale the background with the window size


    float scale_x = (float)m_window.getSize().x / m_background.getLocalBounds().width;
    float scale_y = (float)m_window.getSize().y / m_background.getLocalBounds().height;

    m_background.setScale(scale_x, scale_y);

    if (!m_pipe_texture.loadFromFile("assets/Sprites/pipe-green.png")) {

        std::cerr << "pipe.png could not be loaded" << std::endl;
    }


    if (!m_redBirdDownTexture.loadFromFile("assets/Sprites/redbird-downflap.png")) {

        std::cerr << "redbird-downflap.png could not be loaded" << std::endl;
    }
    if (!m_redBirdMidTexture.loadFromFile("assets/Sprites/redbird-midflap.png")) {

        std::cerr << "redbird-midflap.png could not be loaded" << std::endl;
    }
    if (!m_redBirdUpTexture.loadFromFile("assets/Sprites/redbird-upflap.png")) {

        std::cerr << "redbird-upflap.png could not be loaded" << std::endl;
    }


    m_bird.setTexture(m_redBirdMidTexture);

    m_bird.setScale(1.5f, 1.5f);

    m_bird.setPosition(300.0f, 250.0f);

    m_birdAnimationState = 0;

    m_pipes.push_back(Pipe(m_window.getSize().x, m_pipe_texture));


    m_gamestate = START_SCREEN;

    //load the Game Over picture

    if (!m_gameOverTexture.loadFromFile("assets/Sprites/gameover.png")) {

        std::cerr<<"gameover.png could not be loaded"<<std::endl;
    }

    m_gameOverSprite.setTexture(m_gameOverTexture);
    m_gameOverSprite.setOrigin(m_gameOverSprite.getGlobalBounds().width / 2, m_gameOverSprite.getGlobalBounds().height / 2);

    m_gameOverSprite.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2 - 150);


   

    if (!m_font.loadFromFile("assets/Fonts/arial.ttf")) {
        std::cerr << "flappy-font.ttf could not be loaded" << std::endl;
    }
    //New Game text

    m_newGameText.setFont(m_font);
    m_newGameText.setString("New Game");
    m_newGameText.setCharacterSize(60);
    m_newGameText.setFillColor(sf::Color::White);
    m_newGameText.setOutlineColor(sf::Color::Black);
    m_newGameText.setOutlineThickness(2.0f);
    m_newGameText.setOrigin(m_newGameText.getGlobalBounds().width / 2, m_newGameText.getGlobalBounds().height / 2);
    m_newGameText.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2 + 50);

    

    //quit text

    m_quitText.setFont(m_font);
    m_quitText.setString("Quit");
    m_quitText.setCharacterSize(60);
    m_quitText.setFillColor(sf::Color::White);
    m_quitText.setOutlineColor(sf::Color::Black);
    m_quitText.setOutlineThickness(2.0f);
    m_quitText.setOrigin(m_quitText.getGlobalBounds().width / 2, m_quitText.getGlobalBounds().height / 2);
    m_quitText.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2 + 150);


    if (!m_messageTexture.loadFromFile("assets/Sprites/message.png")) {
        
        std::cerr << "message.png could not be loaded" << std::endl;
    }

    m_messageSprite.setTexture(m_messageTexture);
    m_messageSprite.setOrigin(m_messageSprite.getGlobalBounds().width / 2,
        m_messageSprite.getGlobalBounds().height / 2);
    m_messageSprite.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);



    scoreText.setFont(m_font);
    scoreText.setCharacterSize(32);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: " + std::to_string(m_score));
    scoreText.setPosition(20.f, 20.f);
}

void Game::run() {


    while (m_window.isOpen()) {

        processEvents();
        update();
        render();
    }
}

void Game::Restart_Game() {

    m_bird.setPosition(300.0f, 250.0f);

    m_birdvelocityY = 0.0f;
    m_bird.setTexture(m_redBirdMidTexture);
    m_birdAnimationState = 0;
    m_pipes.clear();
    m_pipes.push_back(Pipe(m_window.getSize().x, m_pipe_texture));

    m_gamestate = RUNNING;
}


void Game::processEvents() {

    sf::Event event;

    while (m_window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {

            m_window.close();
        }

        if (event.type == sf::Event::KeyPressed) {

            if (event.key.code == sf::Keyboard::Space) {

                if (m_gamestate == START_SCREEN) {
                    m_gamestate = RUNNING;
                }
                else if (m_gamestate == RUNNING) {

                    m_birdvelocityY = -4.0f;
                    m_birdAnimationState = 1; //start animation by raising the wings
                    m_wingSound.play();
                    m_animationclock.restart();

                }

            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

            if (m_gamestate == GAME_OVER) {

                if (m_newGameText.getGlobalBounds().contains(mousePos)) {
                    
                    Restart_Game();
                }
                else if (m_quitText.getGlobalBounds().contains(mousePos)){

                    m_window.close();
                }
            }
        }

        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(m_window);
        sf::Vector2f mouseWorldPos = m_window.mapPixelToCoords(mousePixelPos);

        
        if (m_gamestate == GAME_OVER) {
            m_score = 0;
            // New Game hover
            if (m_newGameText.getGlobalBounds().contains(mouseWorldPos)) {
                m_newGameText.setFillColor(sf::Color::Yellow); // shimmering effect
            }
            else {
                m_newGameText.setFillColor(sf::Color::White); // normal color
            }

            // Quit hover
            if (m_quitText.getGlobalBounds().contains(mouseWorldPos)) {
                m_quitText.setFillColor(sf::Color::Red);
            }
            else {
                m_quitText.setFillColor(sf::Color::White);
            }
        }
    }

}


void Game::update() {

    if (m_gamestate != RUNNING) {
        return;
    }
    else {


        m_birdvelocityY += 0.1f;
        m_bird.move(0.0f, m_birdvelocityY);

        if (m_birdvelocityY < 0) {//if bird goes up

            if (m_animationclock.getElapsedTime().asMilliseconds() > ANIMATION_FRAME_DURATION_MS) {

                if (m_birdAnimationState == 1) {
                    m_bird.setTexture(m_redBirdUpTexture);
                    m_birdAnimationState = 2;
                }
                else if (m_birdAnimationState == 2) {
                    m_bird.setTexture(m_redBirdMidTexture);
                    m_birdAnimationState = 1;

                }
                m_animationclock.restart();
            }
            else { //if bird goes down

                m_bird.setTexture(m_redBirdDownTexture);

            }


        }


        //pipe update
        for (size_t i = 0; i < m_pipes.size(); ++i) {
            m_pipes[i].move(5.0f);


            if (!m_pipes[i].m_scored &&
                m_pipes[i].getX() + m_pipe_texture.getSize().x < m_bird.getPosition().x)
            {
                m_pipes[i].m_scored = true;
                m_score++;
                m_pointSound.play();
            }

            //create a new pipe
            if (m_pipes.back().getRightx() < m_window.getSize().x - 350.0f) {

                m_pipes.push_back(Pipe(m_window.getSize().x, m_pipe_texture));


            }

            //delete the old pipe
            if (m_pipes[0].isOffScreen()) {

                m_pipes.erase(m_pipes.begin());
            }




        }


        scoreText.setString("Score: " + std::to_string(m_score));

    }
}
void Game::render() {



    m_window.clear(sf::Color::Black);
    m_window.draw(m_background);

    for (size_t i = 0; i < m_pipes.size(); ++i) {

        m_pipes[i].render(m_window);
    }



    if (m_gamestate == RUNNING) {

        m_gamestate = check_collision();
        m_window.draw(m_bird);
        m_window.draw(scoreText);

    }

    else if (m_gamestate == GAME_OVER) {

        m_window.draw(m_bird);
        m_window.draw(m_gameOverSprite); // Game Over görselini çiz
        m_window.draw(m_newGameText);
        m_window.draw(scoreText);
        m_window.draw(m_quitText);

    }
    else if (m_gamestate == START_SCREEN) {

        m_window.draw(m_background);
        m_window.draw(m_messageSprite);
        m_window.draw(m_bird);//leave the bird stable

        m_window.display();
        return; // do not draw anything else
    }
    m_window.display();
}

GameState get_game_state_running() {
    return RUNNING;
}

GameState get_game_state_over() {
    return GAME_OVER;
}

GameState get_game_state_start_screen() {

    return START_SCREEN;

}
GameState Game::check_collision() {

    sf::FloatRect birdBounds = m_bird.getGlobalBounds();

    if (birdBounds.top + birdBounds.height >= m_window.getSize().y){

        if (m_dieSound.getStatus() != sf::Sound::Playing)
        {
            m_dieSound.play();
            return get_game_state_over();
        }
        return get_game_state_running();
    }

    for (size_t i = 0; i < m_pipes.size(); i++) {

        if (m_pipes[i].get_top_bounds().intersects(birdBounds) ||
            m_pipes[i].get_bottom_bounds().intersects(birdBounds)) {

            if (m_hitSound.getStatus() != sf::Sound::Playing && m_dieSound.getStatus() != sf::Sound::Playing) {

                m_hitSound.play();
                m_dieSound.play();
            }
            return get_game_state_over();
        }

    }

    return get_game_state_running();
}

