

#include"BirdAnimation.hpp"

BirdAnimation::BirdAnimation(const std::string& file_name) {



}

void BirdAnimation::load_frames(const std::string& file_name) {

	std::vector<std::string> suffixes = { "bird-downflap","bird-midflap","bird-upflap" };

	for (const auto& suffix : suffixes) {

		sf::Texture tex;

		tex.loadFromFile("assets/Sprites/" + file_name + suffix + ".png");

		frames.push_back(tex);
	}

	sprite.setTexture(frames[1]);
	sprite.setScale(1.5f, 1.5f);
	sprite.setPosition(300.0f, 250.0f);
}

void BirdAnimation::update(float gravity) {

	velocityY += gravity;
	sprite.move(0, velocityY);

	if (velocityY < 0) //while jumping(while bird goes up )
	{
		if (animationClock.getElapsedTime().asMilliseconds() > frameDurationMs) {

			//	animationState = (animationState == 0) ? 1 : 0; ternary operator could be used as well

			if (animationState == 0)
			{
				animationState = 1;
			}
			else {
				animationState = 0;
			}
		

			sprite.setTexture(frames[animationState]);
			animationClock.restart();
		}
		else {//while bird goes down

			sprite.setTexture(frames[2]); //down

		}
	}


}


void BirdAnimation::render(sf::RenderWindow& window) {

	window.draw(sprite);
}
