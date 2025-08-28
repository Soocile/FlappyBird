

#include"Pipe.hpp"

#include<random>

#include<ctime>


 static constexpr float GAP = 200.0f;
 static constexpr float GAP_HALF = GAP / 2.f;

 static constexpr float GAP_MIN_Y = 250.f;
 static constexpr float GAP_MAX_Y = 550.f;

 //float gapY = rand() % static_cast<int>(GAP_MAX_Y - GAP_MIN_Y) + GAP_MIN_Y;

static std::mt19937& rng() {
    static std::mt19937 gen{ static_cast<unsigned>(std::time(nullptr)) };
    return gen;
}



Pipe::Pipe(float x, const sf::Texture& texture)
{

    m_scored = false;

    m_topPipe.setTexture(texture);
    m_bottomPipe.setTexture(texture);

    // Borular� ekran boyunca uzatmak i�in doku dikd�rtgenini ayarla
    m_topPipe.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, 2000)); // �ok uzun bir boru olu�tur
    m_bottomPipe.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, 2000)); // �ok uzun bir boru olu�tur

    std::uniform_real_distribution<float> dist(GAP_MIN_Y, GAP_MAX_Y);
    float gapCenterY = dist(rng());

    m_topPipe.setScale(1.f, -1.f);

    // �st boruyu bo�lu�un �st�ne, ekran�n en �st�ne yasla
    m_topPipe.setPosition(x, gapCenterY - GAP_HALF);

    // Alt boruyu bo�lu�un alt�na, ekran�n en alt�na yasla
    m_bottomPipe.setPosition(x, gapCenterY + GAP_HALF);
}



void Pipe::move(float speed) {

	m_topPipe.move(-speed, 0.0f);
	m_bottomPipe.move(-speed, 0.0f);

}

void Pipe::render(sf::RenderWindow& window) {

	window.draw(m_topPipe);
	window.draw(m_bottomPipe);
}

bool Pipe::isOffScreen() {

	return m_bottomPipe.getGlobalBounds().left < -m_bottomPipe.getGlobalBounds().width;
}

float Pipe::getRightx() {

	return m_bottomPipe.getGlobalBounds().left + m_bottomPipe.getGlobalBounds().width;
}

sf::FloatRect Pipe::get_top_bounds() const {

    return m_topPipe.getGlobalBounds();
}

sf::FloatRect Pipe::get_bottom_bounds() const {

    return m_bottomPipe.getGlobalBounds();
}

float Pipe::getX() const {
    return m_topPipe.getPosition().x;
}

float Pipe::getGapY() const {
    return m_topPipe.getPosition().y + m_topPipe.getGlobalBounds().height + GAP / 2;
}
