#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <vector>
#include <cstdlib>

using namespace sf;
using namespace std;



//-------------------Classes-------------------------//
class HealthBar : public RectangleShape{
public:
	float Health;
	float maxHealth;
	float height, width;

	HealthBar(float _height, float _width, float _maxHealth);
	void decreaseHealth(float amount);

};


class UI_Texes_Utility {
private:
public:
	//Fonts
	Font font;

	//Text
	Text scoreLabel;
	Text scoreValue;
	Text HPLabel;
	Text gameOverT;


	// textures
	Texture background;
	Texture player_tex;
	Texture shield_tex;
	Texture playerBullet_tex;
	Texture enemy_tex;
	Texture enemyBullet_tex;

	//others
	RectangleShape back;

	//functions
	UI_Texes_Utility();

};