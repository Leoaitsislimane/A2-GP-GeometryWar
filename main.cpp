// main.cpp

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <SFML/Audio.hpp>
//#include "Menu.h"
#include "MenuClass.h"


constexpr float cubeSpeed = 800.f;

float reloadTime = 0.4f;
float currentReloadTime = reloadTime;

int shootTimer = 0;
int enemySpawnTimer = 0;

void EnemySpawn(float spawnInterval, float moveSpeed, float deltaTime, sf::RectangleShape& enemy, std::vector<sf::RectangleShape>& enemies, sf::RenderWindow& window);
//a mettre dans un struct ou une classe pour avoir des variables globales et le passer en paramètre de la future fonction update
int main()
{
	sf::Music music;

	MenuClass gameMenu;
	// Initialisation

	srand(time(NULL));//on initialise le random

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Geometry Wars");
	window.setVerticalSyncEnabled(true);

	// Début de la boucle de jeu
	sf::CircleShape player(30, 3);//rayon et nombre de points (3 points pour un triangle)
	player.setOrigin(30, 30);
	player.setRadius(30.f);
	player.setFillColor(sf::Color::Green);
	player.setPosition(980, 920);//au centre de l'ecran
	sf::Vector2f playerPos;//Notre position de tir

	sf::RectangleShape enemy;
	enemy.setSize(sf::Vector2f(40.0f, 40.0f));
	enemy.setOutlineColor(sf::Color::Magenta);
	enemy.setOutlineThickness(5.0f);
	enemy.setFillColor(sf::Color::Transparent);
	std::vector<sf::RectangleShape> enemies;
	enemies.push_back(sf::RectangleShape(enemy));//on ajoute un ennemi à notre tableau de taille dynamique d'ennemis

	sf::CircleShape bullet;
	bullet.setOrigin(5, 5);
	bullet.setRadius(5.0f);
	bullet.setFillColor(sf::Color::Red);
	std::vector<sf::CircleShape> bullets;
	bullets.push_back(sf::CircleShape(bullet));//on ajoute une balle à notre tableau de taille dynamique de projectiles



	sf::Clock frameClock;
	sf::Clock gameClock;


	sf::Font myFont;
	myFont.loadFromFile("spacetime.ttf");

	int score = 0;
	sf::Text scoreboard;
	scoreboard.setFont(myFont);
	scoreboard.setFillColor(sf::Color::Yellow);
	scoreboard.setCharacterSize(54);
	scoreboard.setString(std::to_string(score));

	while (window.isOpen())
	{
		if (!music.openFromFile("cyborg-ninja.mp3"))
		{
			std::cout << "Error loading music\n" << std::endl;
		}
		else {
			music.setLoop(true);
			music.play();
		}
		

		float time = frameClock.getElapsedTime().asSeconds();

		sf::Time elapsedGameTime = gameClock.getElapsedTime();
		float gameTime = elapsedGameTime.asSeconds();
		// Gérer les événéments survenus depuis le dernier tour de boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// On gère l'événément
			switch (event.type)
			{
			case sf::Event::Closed:
				// L'utilisateur a cliqué sur la croix => on ferme la fenêtre
				window.close();
				break;


			}
			//envoyer event à notre menu
			if (gameMenu.state == MenuState::Open) {
				gameMenu.processInputMenu(event, window);
			}
		}



		float deltaTime = frameClock.restart().asSeconds();
		//std::cout << 1.f / deltaTime << " FPS" << std::endl; 


		// Logique
		sf::Vector2f pos = player.getPosition();//vector2f = vecteur position avec 2 float
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			pos.x = pos.x - deltaTime * cubeSpeed; // pos.x -= deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			pos.x = pos.x + deltaTime * cubeSpeed;


#pragma region SHOOTING

		player.setPosition(pos);

		playerPos = sf::Vector2f(player.getPosition().x + (player.getRadius() * deltaTime), player.getPosition().y + (player.getRadius() * deltaTime));

		if (shootTimer < reloadTime * 60) {

			shootTimer++;
		}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			shootTimer = 0;
			bullet.setPosition(playerPos);
			bullets.push_back(sf::CircleShape(bullet));
		}
		//std::cout << shootTimer << "secondes" << std::endl;

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].move(0.f, -10.f);//offset x, offset y => on déplace la balle vers le bas 

			if (bullets[i].getPosition().y <= 0)//si la balle est hors de l'ecran
			{
				bullets.erase(bullets.begin() + i);//on supprime la balle si elle sort de l'écran. On place l'iterateur au debut
			}
		}
#pragma endregion



#pragma region ENEMIES

		/*if (gameTime < 10) {

			EnemySpawn(1.5f, 1.f, deltaTime, enemy, enemies, window);
		}

		if (gameTime < 20) {

			EnemySpawn(1.5f, 2.f, deltaTime, enemy, enemies, window);
		}

		if (gameTime < 30) {

			EnemySpawn(1.5f, 4.f, deltaTime, enemy, enemies, window);
		}

		if (gameTime < 40) {

			EnemySpawn(1.5f, 6.f, deltaTime, enemy, enemies, window);
		}

		if (gameTime < 50) {

			EnemySpawn(1.5f, 8.f, deltaTime, enemy, enemies, window);
		}*/

		if (gameTime < 10) {
			// Code for the first time interval (0 to 10 seconds)
			if (enemySpawnTimer * deltaTime < 1.5) {
				// Spawn an enemy every 3 seconds
				enemySpawnTimer++;
				std::cout << gameTime << std::endl;
			}
			else {
				// Spawn enemies at random positions between the left and right edges of the window
				enemy.setPosition(rand() % int(window.getSize().x - enemy.getSize().x), 0.f);
				enemies.push_back(sf::RectangleShape(enemy));
				enemySpawnTimer = 0;
			}

			// Move existing enemies downward
			for (size_t i = 0; i < enemies.size(); i++) {
				enemies[i].move(0.f, 2.f);

				// Remove enemies that have moved beyond the bottom of the window
				if (enemies[i].getPosition().y > window.getSize().y) {
					enemies.erase(enemies.begin() + i);
				}
			}
		}
		else if (gameTime < 20) {
			// Code for the second time interval (10 to 20 seconds)
			if (enemySpawnTimer * deltaTime < 1) {
				// Spawn an enemy every 2 second
				enemySpawnTimer++;
			}
			else {
				// Spawn enemies at random positions between the left and right edges of the window
				enemy.setPosition(rand() % int(window.getSize().x - enemy.getSize().x), 0.f);
				enemies.push_back(sf::RectangleShape(enemy));
				enemySpawnTimer = 0;
			}

			// Move existing enemies downward
			for (size_t i = 0; i < enemies.size(); i++) {
				enemies[i].move(0.f, 4.f);
			}
		}
		else if (gameTime < 30) {
			// Code for the third time interval (20 to 30 seconds)
			if (enemySpawnTimer * deltaTime < 0.5) {
				// Spawn an enemy every 1 second
				enemySpawnTimer++;
			}
			else {
				// Spawn enemies at random positions between the left and right edges of the window
				enemy.setPosition(rand() % int(window.getSize().x - enemy.getSize().x), 0.f);
				enemies.push_back(sf::RectangleShape(enemy));
				enemySpawnTimer = 0;
			}

			// Move existing enemies downward
			for (size_t i = 0; i < enemies.size(); i++) {
				enemies[i].move(0.f, 6.f);
			}
		}

		else if (gameTime < 40) {
			// Code for the third time interval (20 to 30 seconds)
			if (enemySpawnTimer * deltaTime < 0.5) {
				// Spawn an enemy every 1 second
				enemySpawnTimer++;
			}
			else {
				// Spawn enemies at random positions between the left and right edges of the window
				enemy.setPosition(rand() % int(window.getSize().x - enemy.getSize().x), 0.f);
				enemies.push_back(sf::RectangleShape(enemy));
				enemySpawnTimer = 0;
			}

			// Move existing enemies downward
			for (size_t i = 0; i < enemies.size(); i++) {
				enemies[i].move(0.f, 8.f);
			}
		}

		else if (gameTime < 50) {
			// Code for the third time interval (20 to 30 seconds)
			if (enemySpawnTimer * deltaTime < 0.2) {
				// Spawn an enemy every 1 second
				enemySpawnTimer++;
			}
			else {
				// Spawn enemies at random positions between the left and right edges of the window
				enemy.setPosition(rand() % int(window.getSize().x - enemy.getSize().x), 0.f);
				enemies.push_back(sf::RectangleShape(enemy));
				enemySpawnTimer = 0;
			}

			// Move existing enemies downward
			for (size_t i = 0; i < enemies.size(); i++) {
				enemies[i].move(0.f, 10.f);
			}
		}



#pragma endregion

#pragma region COLLISION
		for (size_t i = 0; i < bullets.size(); i++) {
			for (size_t j = 0; j < enemies.size(); j++) {
				if (bullets[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
					score++;
					scoreboard.setString(std::to_string(score));
					bullets.erase(bullets.begin() + i);
					enemies.erase(enemies.begin() + j);
					break;
				}
			}
		}
#pragma endregion



		// Affichage

		// Remise au noir de toute la fenêtre
		window.clear();
		if (gameMenu.state == MenuState::Open) {
			gameMenu.drawMenu(window);

		}
		else {

			// Dessiner le joueur
			window.draw(player);

			// Dessiner les ennemis
			for (const auto& enemy : enemies) {
				window.draw(enemy);
			}

			// Dessiner les projectiles
			for (const auto& bullet : bullets) {
				window.draw(bullet);
			}

			// Dessiner le score
			window.draw(scoreboard);
		}

		window.display();

		// On présente la fenêtre sur l'écran

	}
}

void EnemySpawn(float spawnInterval, float moveSpeed, float deltaTime, sf::RectangleShape& enemy, std::vector<sf::RectangleShape>& enemies, sf::RenderWindow& window) {
	if (enemySpawnTimer * deltaTime < spawnInterval) {
		// Spawn an enemy
		enemySpawnTimer++;
	}
	else {
		// Spawn enemies at random positions between the left and right edges of the window
		enemy.setPosition(rand() % int(window.getSize().x - enemy.getSize().x), 0.f);
		enemies.push_back(sf::RectangleShape(enemy));
		enemySpawnTimer = 0;
	}

	// Move existing enemies downward
	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i].move(0.f, moveSpeed);

		// Remove enemies that have moved beyond the bottom of the window
		if (enemies[i].getPosition().y > window.getSize().y) {
			// Vous pouvez également fermer la fenêtre si nécessaire
			window.close();
		}
	}
}