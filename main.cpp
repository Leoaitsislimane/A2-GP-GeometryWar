// main.cpp

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <SFML/Audio.hpp>

#include "MenuClass.h"


constexpr float speed = 800.f;

float countDownDuration = 60.0f; // Durée du décompte en secondes


float reloadTime = 0.5f;
float currentReloadTime = reloadTime;

int shootTimer = 0;
int enemySpawnTimer = 0;
int powerUpSpawnTimer = 0;

bool gameOver = false;
int bestScore = 70;

void EnemySpawn(float spawnInterval, float moveSpeed, float deltaTime, sf::RectangleShape& enemy, std::vector<sf::RectangleShape>& enemies, sf::RenderWindow& window);
void displayGameOver(sf::RenderWindow& window, sf::Sprite& gameOverSprite, sf::Texture& gameOverTexture, const std::string& texturePath, int lowerBound, int upperBound, int score);

//a mettre dans un struct ou une classe pour avoir des variables globales et le passer en paramètre de la future fonction update
int main()
{
	// Initialisation
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Geometry Wars");
	ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
	window.setVerticalSyncEnabled(true);
	srand(time(NULL));//on initialise le random

	sf::Image icon;
	if (!icon.loadFromFile("logo.png")) {
		std::cout << "could not load picture" << std::endl;
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::Music music;
	if (!music.openFromFile("cyborg-ninja.mp3"))
	{
		std::cout << "Error loading music\n" << std::endl;
	}
	else {
		music.setLoop(true);
		music.play();
	}

	MenuClass gameMenu;

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

	sf::Text chrono;
	chrono.setFont(myFont);
	chrono.setCharacterSize(34);
	chrono.setFillColor(sf::Color::White);
	chrono.setPosition(1600, 10);

	while (window.isOpen())
	{
		float time = frameClock.getElapsedTime().asSeconds();

		sf::Time elapsedGameTime = gameClock.getElapsedTime();
		float gameTime = elapsedGameTime.asSeconds();

		std::cout << gameTime << std::endl;
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
			pos.x = pos.x - deltaTime * speed; // pos.x -= deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			pos.x = pos.x + deltaTime * speed;


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

		if (gameTime < 10) {

			EnemySpawn(1.5f, 2.f, deltaTime, enemy, enemies, window);

		}

		else if (gameTime < 20) {

			EnemySpawn(1.f, 4.f, deltaTime, enemy, enemies, window);
		}

		else if (gameTime < 30) {

			EnemySpawn(0.5f, 6.f, deltaTime, enemy, enemies, window);
		}

		else if (gameTime < 45) {

			EnemySpawn(0.3f, 8.f, deltaTime, enemy, enemies, window);
		}

		else if (gameTime < 60) {

			EnemySpawn(0.1f, 10.f, deltaTime, enemy, enemies, window);
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

		countDownDuration -= deltaTime;

		if (gameTime >29 && !gameOver)
		{
			gameOver = true;

			if (score > bestScore)
			{
				bestScore = score;
			}
		}

		// Affichage

		// Remise au noir de toute la fenêtre
		window.clear();

		chrono.setString("Time left : " + std::to_string((static_cast<int>(countDownDuration))));

		if (gameMenu.state == MenuState::Open) {
			gameMenu.drawMenu(window);

		}
		else if (gameOver)
		{
			music.stop();

			//game over window
			sf::Text gameOverText;
			sf::Text displayScore;
			sf::Texture gameOverTexture;
			sf::Sprite gameOverSprite;

			gameOverText.setFont(myFont);
			displayScore.setFont(myFont);

			gameOverText.setCharacterSize(130);
			displayScore.setCharacterSize(64);

			gameOverText.setString("Game Over");
			displayScore.setString("Your score "+ std::to_string(score) + "\nBest Score : " + std::to_string(bestScore));

			gameOverText.setPosition(550, 150);
			displayScore.setPosition(680, 700);

			gameOverText.setFillColor(sf::Color::Red);
			displayScore.setFillColor(sf::Color::Red);

			window.draw(gameOverText);
			window.draw(displayScore);

			displayGameOver(window, gameOverSprite, gameOverTexture, "disapointed_travis.png", 0, 20, score);
			displayGameOver(window, gameOverSprite, gameOverTexture, "stare_travis.png", 21, 40, score);
			displayGameOver(window, gameOverSprite, gameOverTexture, "christmas_travis.jpg", 41, 50, score);
			displayGameOver(window, gameOverSprite, gameOverTexture, "wholesome_travis.jpg", 51, 70, score);
			displayGameOver(window, gameOverSprite, gameOverTexture, "crazy_travis.jpg", 71, 100, score);

		}
		else {

			window.draw(chrono);
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
		// Spawn enemy
		enemySpawnTimer++;
	}
	else {
		// Spawn enemies à des positions aléatoires les bords gauches et droits de l'écran
		enemy.setPosition(rand() % int(window.getSize().x - enemy.getSize().x), 0.f);
		enemies.push_back(sf::RectangleShape(enemy));
		enemySpawnTimer = 0;
	}

	// deplacer les ennemis vers le bas
	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i].move(0.f, moveSpeed);

		// supp les ennemis qui sortent de l'écran
		if (enemies[i].getPosition().y > window.getSize().y) {
			enemies.erase(enemies.begin() + i);
		}
	}
}

void displayGameOver(sf::RenderWindow& window, sf::Sprite& gameOverSprite, sf::Texture& gameOverTexture, const std::string& texturePath, int lowerBound, int upperBound, int score) {
	if (lowerBound <= score && score <= upperBound) {
		if (!gameOverTexture.loadFromFile(texturePath))
		{
			std::cout << "Error loading texture\n" << std::endl;
		}
		else {
			gameOverSprite.setTexture(gameOverTexture);
			gameOverSprite.setPosition(770, 320);
			window.draw(gameOverSprite);
		}
	}
}
