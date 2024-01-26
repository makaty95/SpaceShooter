#include "Sprites.h"
#include "UI.h"

/////////////////////////////////////////Enemy////////////////////////////////////////////////////////////////////

Enemy::Enemy(Texture* _texture, Vector2u windowSize) {
	this->texture = _texture;
	this->shape.setTexture(*texture);
	shape.setScale({ 0.12, 0.12 });
	shape.setPosition(windowSize.x, rand() % windowSize.y - this->shape.getGlobalBounds().height);

	//health
	health_bar = new HealthBar(5.f, 100.f, 100.f);
	health_bar->shape.setFillColor(Color::Green);
}

void Enemy::decreaseHP(float amount) {
	this->health_bar->decreaseHealth(amount);
}


/////////////////////////////////////////Player////////////////////////////////////////////////////////////////////

//Constructors//
Player::Player(Texture* _texture, Texture* _shield_tex) {
	shield_tex = _shield_tex;
	isShieledActive = 0;
	shield.setTexture(*shield_tex);
	shield.setOrigin({ shield.getGlobalBounds().width / 2, shield.getGlobalBounds().height / 2 });
	shield.setScale({ 0.3, 0.3 });

	score = 0;
	this->texture = _texture;
	this->shape.setTexture(*texture);
	shape.setScale({ 0.2, 0.2 });

	//health
	health_bar = new HealthBar(15.f, 200.f, 200.f);
	health_bar->shape.setFillColor(Color::Red);
}

// functions
void Player::addToScore(int _x) {
	score += _x;
}

void Player::decreaseHP(float amount) {
	this->health_bar->decreaseHealth(amount);
}

int Player::getScore() { return score; }