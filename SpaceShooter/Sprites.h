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

class Enemy {
private:
	Texture* texture;

public:

	float bulletStrength = 10.f; // make it static
	HealthBar* health_bar;
	int shootingTimer = 0;
	Vector2f movingSpeed = { 5.f, 5.f };
	Sprite shape;

	Enemy(Texture* _texture, Vector2u windowSize);
	void decreaseHP(float amount);
	~Enemy() {}

};

////////////////////////////////////////Player////////////////////////////////////////
struct Force {
public:

	Vector2f magnitude = { 0.f, 0.f };
	Vector2f direction = { 0.f , 0.f };

};

class Player {
private:
	Texture* texture;
	Texture* shield_tex;
	int score;


public:

	Force appForce;
	Vector2f playerCenter;
	Sprite shield;
	bool isShieledActive;
	HealthBar* health_bar;
	Sprite shape;

	Vector2f currentVelocity = { 0.f, 0.f };
	Vector2f direction = { 0.f, 0.f };
	float maxVelocity = 6.f;
	float acceleration = 0.5f;
	float drag = 0.1f;
	float bulletStrength = 40.f; //make it static

	Player(Texture* _texture, Texture* _shield_tex);
	void addToScore(int _x);
	void decreaseHP(float amount);
	int getScore();
	~Player() {}

};

