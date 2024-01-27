#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include<vector>
#include<cstdlib>
//-----------------------------//
#include "Utility.h"
//-----------------------------//
using namespace sf;
using namespace std;

/*
* shiled in game duration
* shield as a game aids
* 
* 
*/

int main() {
	srand(0);
	RenderWindow window(VideoMode(1280, 720), "Mainwindow");
	window.setFramerateLimit(60);


	
	/*Player::bulletStrength = 20.f;
	Enemy::bulletStrength = 20.f;*/

	Clock gameClock;
	GameManager Game;
	
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		if (Game.player->health_bar->Health > 0) {
			Game.movePlayer();
			Game.Shoot();
			Game.spawnEnemies(window);
			Game.enemyBehaviour(window);
			Game.checkBullets();
			Game.Update();
		}
		else {
			Game.gameOver();
		}

		Game.deltaTime = gameClock.restart().asSeconds();
		Game.checkPlayerBounds(window);
		Game.validateBullets(window);

		window.clear();
		window.draw(Game.UIs.back);
		window.draw(*Game.player);
		window.draw(*Game.player->health_bar);
		window.draw(Game.UIs.scoreLabel);
		window.draw(Game.UIs.scoreValue);
		window.draw(Game.UIs.HPLabel);
		if (Game.isGameOver) {
			window.draw(Game.UIs.gameOverT);
		}

		if (Game.player->player_shield.isShieledActive) {
			window.draw(Game.player->player_shield);
		}

		// draw bullets
		for (auto& b : Game.bullets) {
			window.draw(b.shape);
		}

		for (auto& enemy : Game.enemies) {
			window.draw(enemy);
			window.draw(*enemy.health_bar);
		}
		window.display();
	}


}

