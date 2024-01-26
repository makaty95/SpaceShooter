#include "UI.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <vector>
#include <cstdlib>

using namespace std;
using namespace sf;


// constructors
HealthBar::HealthBar(float _height, float _width, float _maxHealth) : maxHealth(_maxHealth), Health(_maxHealth), height(_height), width(_width) {
	shape.setSize({ _width, _height });
	shape.setPosition({ 10.f, 40.f });
}

UI_Texes_Utility::UI_Texes_Utility() {

	if (!font.loadFromFile("stuff/mainFont.ttf")) {
		cout << "error loading font" << endl;
	}
	else {
		cout << "font loaded" << endl;
	}

	back.setSize(Vector2f(1280, 720));

	// UI text
	scoreLabel.setCharacterSize(20);
	scoreLabel.setFont(font);
	scoreLabel.setString("SCORE:");
	scoreLabel.setPosition({ 220.f, 10.f });

	scoreValue.setCharacterSize(20);
	scoreValue.setFont(font);
	scoreValue.setString("0");
	scoreValue.setPosition({ 300.f, 10.f });

	HPLabel.setCharacterSize(20);
	HPLabel.setFont(font);
	HPLabel.setString("HEALTH");
	HPLabel.setPosition({ 10.f, 10.f });

	// background
	background.loadFromFile("stuff/bg_space.png");
	back.setTexture(&background);
	back.setPosition(Vector2f(0, 0));


	//importing UI Textures
	shield_tex.loadFromFile("stuff/shield.png");
	if (player_tex.loadFromFile("stuff/jet.png")) cout << "player texture loaded\n";
	if (bullet_tex.loadFromFile("stuff/bullet.png"))cout << "bullet texture loaded\n";
	if (enemy_tex.loadFromFile("stuff/enemy.png"))cout << "enemy texture loaded\n";
	if (enemyBullet_tex.loadFromFile("stuff/ebullet.png"))cout << "enemy texture loaded\n";

}

void HealthBar::decreaseHealth(float amount) {
	
	width -= min(amount, width);
	Health -= min(amount, Health);
	shape.setSize({ width, height });

}


