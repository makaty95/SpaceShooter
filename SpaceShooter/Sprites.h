#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include<vector>
#include<cstdlib>
//------------------//
#include "UI.h"
//------------------//

////////////////////////////////////////Enemy////////////////////////////////////////

class Enemy : public Sprite{
private:

public:

	float bulletStrength = 10.f;
	HealthBar* health_bar;
	int shootingTimer = 0;
	Vector2f movingSpeed = { 5.f, 5.f };


	Enemy(Texture* _texture, Vector2u windowSize);
	void decreaseHP(float amount);
	~Enemy() {}

};

////////////////////////////////////////Player//////////////////////////////////////////////////////////////////


class Shield : public Sprite {
private:
	
public:
	bool isShieledActive;

};

class Player : public Sprite {
private:
	int score;

public:

	Shield player_shield;
	Vector2f playerCenter;
	HealthBar* health_bar;

	Vector2f currentVelocity = { 0.f, 0.f };
	Vector2f direction = { 0.f, 0.f };
	float maxVelocity = 6.f;
	float acceleration = 0.5f;
	float drag = 0.1f;
	static float bulletStrength; //make it static

	Player(Texture* _texture, Texture* _shield_tex);
	void addToScore(int _x);
	void decreaseHP(float amount);
	int getScore();


};

