#include "Sprites.h"
#include "UI.h"

/////////////////////////////////////////Enemy////////////////////////////////////////////////////////////////////

Enemy::Enemy(Texture* _texture, Vector2u windowSize) {
	this->setTexture(*_texture);
	this->setScale({ 0.12, 0.12 });
	this->setPosition(windowSize.x, rand() % windowSize.y - this->getGlobalBounds().height);

	//health
	health_bar = new HealthBar(5.f, 100.f, 100.f);
	health_bar->setFillColor(Color::Green);
}

void Enemy::decreaseHP(float amount) {
	this->health_bar->decreaseHealth(amount);
}


/////////////////////////////////////////Player////////////////////////////////////////////////////////////////////
float Player::bulletStrength = 40.f;
//Constructors//
Player::Player(Texture* _texture, Texture* _shield_tex) {
	player_shield.setTexture(*_shield_tex);
	player_shield.isShieledActive = 0;
	player_shield.setOrigin({ player_shield.getGlobalBounds().width / 2, player_shield.getGlobalBounds().height / 2 });
	player_shield.setScale({ 0.3, 0.3 });

	score = 0;
	this->setTexture(*_texture);
	this->setScale({ 0.2, 0.2 });

	//health
	health_bar = new HealthBar(15.f, 200.f, 200.f);
	health_bar->setFillColor(Color::Red);
}

// functions
void Player::addToScore(int _x) {
	score += _x;
}

void Player::decreaseHP(float amount) {
	this->health_bar->decreaseHealth(amount);
}

int Player::getScore() { return score; }