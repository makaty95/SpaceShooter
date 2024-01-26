#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include<vector>
#include<cstdlib>
//---------------------//
#include "Utility.h"
//---------------------//
using namespace std;
using namespace sf;

//---------------------Utility Variables-------------------//


//------------Classes Constructors Difinitions----------------//

Bullet::Bullet(Texture* _texture, float _speed) {
	strength = (float)10 + rand() % 15;
	this->texture = _texture;
	this->shape.setTexture(*texture);
	this->speed = _speed;
	shape.setScale({ 0.03, 0.03 });
}

GameManager::GameManager() {
	shootTimer = 0;
	enemySpwanTimer = 0;
	isGameOver = 0;

	//player

	player = new Player(&UIs.player_tex, &UIs.shield_tex);
}

//------------Utility Functions Difinitions----------------//

void GameManager::gameOver() {
	isGameOver = 1;
	UIs.gameOverT.setFillColor(Color::Yellow);
	UIs.gameOverT.setCharacterSize(100);
	UIs.gameOverT.setFont(UIs.font);
	UIs.gameOverT.setString("Game Over");
	UIs.gameOverT.setPosition({ 600.f, 400.f });

}
void GameManager::Update() {
	UIs.scoreValue.setString(to_string(player->getScore()));
	player->shield.setPosition(player->playerCenter);
}

void GameManager::checkBullets() {
	int n = bullets.size();
	for (int i = 0; i < n; i++) {
		if (bullets[i].source == bulletSource::ENEMY and player->shape.getGlobalBounds().intersects(bullets[i].shape.getGlobalBounds())) {

			player->decreaseHP(bullets[i].strength);
			bullets.erase(bullets.begin() + i);
			break;
		}
	}

	n = bullets.size();
	bool flag = 0;
	for (int i = 0; i < n; i++) {
		flag = 0;
		for (int j = 0; j < enemies.size(); j++) {
			if (bullets[i].source == bulletSource::PLAYER and bullets[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds())) {

				player->addToScore(5);
				enemies[j].decreaseHP(bullets[i].strength);
				bullets.erase(bullets.begin() + i);
				if (enemies[j].health_bar->Health <= 0) {
					enemies.erase(enemies.begin() + j);
				}

				flag = 1;
				break;
			}
		}
		if (flag) {
			break;
		}
	}

	//enemy health_bar
	for (auto& e : enemies) {
		e.health_bar->shape.setPosition({ e.shape.getPosition().x, e.shape.getPosition().y - 3.f });
	}

}

void GameManager::enemyBehaviour(RenderWindow& window) {
	for (auto& enemy : enemies) {
		enemy.shape.move({ -enemy.movingSpeed.x * deltaTime * multiplier, 0.f });

	}
	int n = enemies.size();
	for (int i = 0; i < n; i++) {
		if (outsideScreen(enemies[i].shape, window)) {
			enemies.erase(enemies.begin() + i);
			cout << "enemy removed" << endl;
			break;
		}
	}

	//shooting
	for (auto& enemy : enemies) {
		if (abs(player->shape.getPosition().y - enemy.shape.getPosition().y) <= 200) {

			if (enemy.shootingTimer >= 70) {
				Bullet bullet(&UIs.enemyBullet_tex, bulletSpeed.x / 2);
				bullet.strength = enemy.bulletStrength;
				bullet.source = bulletSource::ENEMY;
				Vector2f enemy_center = { enemy.shape.getPosition().x + enemy.shape.getGlobalBounds().width / 2,
					enemy.shape.getPosition().y + enemy.shape.getGlobalBounds().height / 2 };

				bullet.shape.setPosition(enemy_center);
				bullets.push_back(bullet);
				enemy.shootingTimer = 0;

			}
			else enemy.shootingTimer++;
		}
	}

}
void GameManager::spawnEnemies(RenderWindow& window) {
	if (enemySpwanTimer >= 50 + rand() % 50) {
		enemySpwanTimer = 0;
		Enemy enemy(&UIs.enemy_tex, window.getSize());
		enemies.push_back(enemy);
	}
	else {
		enemySpwanTimer += (deltaTime * multiplier);
	}
}

void GameManager::checkPlayerBounds(RenderWindow& window) {
	auto x = player->shape.getPosition().x;
	auto y = player->shape.getPosition().y;
	if (y < 0) {
		player->shape.setPosition(x, 0);
	}
	if (y + player->shape.getGlobalBounds().height > window.getSize().y) {
		player->shape.setPosition(x, window.getSize().y - player->shape.getGlobalBounds().height);
	}
}


void GameManager::movePlayer() {
	if (Keyboard::isKeyPressed(Keyboard::W)) {

		player->direction.y = -1.0;

		if (player->currentVelocity.y < player->maxVelocity)
			player->currentVelocity.y += (player->acceleration * deltaTime * multiplier);

	}else if (Keyboard::isKeyPressed(Keyboard::S)) {
		player->direction.y = 1;

		if (player->currentVelocity.y < player->maxVelocity)
			player->currentVelocity.y += (player->acceleration * deltaTime * multiplier);

	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {

		if (player->direction.x != 1.0) {
			player->currentVelocity.x = 0.f;
			//player->appForce.magnitude.x += (player->currentVelocity.x * player->direction.x);

		}
			

		player->direction.x = 1.0;
		if (player->currentVelocity.x < player->maxVelocity)
			player->currentVelocity.x += (player->acceleration * deltaTime * multiplier);

	}else if (Keyboard::isKeyPressed(Keyboard::A)) {

		if (player->direction.x != -1.0) {
			player->currentVelocity.x = 0.f;
			//player->appForce.magnitude.x += (player->currentVelocity.x * player->direction.x);

		}


		player->direction.x = -1.0;
		if (player->currentVelocity.x < player->maxVelocity)
			player->currentVelocity.x += (player->acceleration * deltaTime * multiplier);

	}

	//player->appForce.magnitude.x = max(0.f, player->appForce.magnitude.x - 0.1f);
	//player->appForce.magnitude.y = max(0.f, player->appForce.magnitude.y - 0.1f);

	

	if (player->currentVelocity.x > 0.f) {
		player->currentVelocity.x = max(0.f, player->currentVelocity.x - (player->drag * deltaTime * multiplier));
	}
	else if (player->currentVelocity.x < 0.f) {
		player->currentVelocity.x = min(player->maxVelocity, player->currentVelocity.x + (player->drag * deltaTime * multiplier));
	}

	if (player->currentVelocity.y > 0.f) {
		player->currentVelocity.y = max(0.f, player->currentVelocity.y - (player->drag * deltaTime * multiplier));
	}
	else if (player->currentVelocity.y < 0.f) {
		player->currentVelocity.y = min(player->maxVelocity, player->currentVelocity.y + (player->drag * deltaTime * multiplier));
	}

	player->shape.move({(player->currentVelocity.x) * player->direction.x * deltaTime * multiplier,
		(player->currentVelocity.y) * player->direction.y * deltaTime * multiplier });

	player->playerCenter = { player->shape.getPosition().x + player->shape.getGlobalBounds().width / 2, player->shape.getPosition().y + player->shape.getGlobalBounds().height / 2 };

}

void GameManager::Shoot() {

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (shootTimer >= 10) {
			Bullet bullet(&UIs.bullet_tex, bulletSpeed.x);
			bullet.source = bulletSource::PLAYER;
			bullet.strength = player->bulletStrength;
			bullet.shape.setPosition(player->playerCenter);
			bullets.push_back(bullet);
			shootTimer = 0;

		}
		else shootTimer += (deltaTime * multiplier);

	}
	else {
		shootTimer++;

	}

}


bool GameManager::outsideScreen(Sprite& shape, RenderWindow& window) {
	if (shape.getPosition().x > window.getSize().x) {
		return true;
	}
	if (shape.getPosition().x < -shape.getGlobalBounds().width) {
		return true;
	}

	if (shape.getPosition().y < 0) {
		return true;
	}

	if (shape.getPosition().y > window.getSize().y) {
		return true;
	}
	return false;
}

void GameManager::validateBullets(RenderWindow& window) {
	int n = bullets.size();
	for (int i = 0; i < n; i++) {
		if (outsideScreen(bullets[i].shape, window)) {
			bullets.erase(bullets.begin() + i);
			cout << "bullet removed\n";
			break;
		}

		// if shield is active and a bullet intersected with it
		if (player->isShieledActive and bullets[i].source == bulletSource::ENEMY and bullets[i].shape.getGlobalBounds().intersects(player->shield.getGlobalBounds())) {
			player->shield.setColor(Color::Green);
			bullets.erase(bullets.begin() + i);
			cout << "bullet removed\n";
			player->shield.setColor(Color::White);
			break;
		}
	}

	for (auto& b : bullets) {
		if (b.source == bulletSource::PLAYER) {
			b.shape.move({ b.speed * deltaTime * multiplier, 0.f });
		}
		else {
			b.shape.move({ -b.speed * deltaTime * multiplier, 0.f });
		}
	}
}