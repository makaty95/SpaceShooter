#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include<vector>
#include<cstdlib>
//-------------------------//
#include "Sprites.h"
//-------------------------//

using namespace sf;
using namespace std;


enum class bulletSource { PLAYER, ENEMY };



//---------utility classes--------------------------------------------//




class Bullet {
private:
	Texture* texture;
public:
	float strength;
	float speed;
	Sprite shape;
	bulletSource source;
	Bullet(Texture* _texture, float _speed);
	~Bullet() {}

};

class GameManager {
private:
	const Vector2f bulletSpeed = { 30.f, 0.f };
	float shootTimer;
	float enemySpwanTimer;

public:
	float deltaTime;
	float multiplier = 62.0;
	vector<Bullet> bullets;
	vector<Enemy> enemies;
	bool isGameOver;
	UI_Texes_Utility UIs;
	Player* player;
	GameManager();


	//---------utility functions--------------------------------------------//
	void movePlayer();
	void Shoot();
	bool outsideScreen(Sprite& shape, RenderWindow& window);
	void checkPlayerBounds(RenderWindow& window);
	void spawnEnemies(RenderWindow& window);
	void enemyBehaviour(RenderWindow& window);
	void checkBullets();
	void Update();
	void gameOver();
	void validateBullets(RenderWindow& window);



};

