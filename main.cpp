#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

constexpr float cubeSpeed = 500.f;

int main()
{
	// Initialisation

	srand(time(NULL));//on initialise le random

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars");
	window.setVerticalSyncEnabled(true);

	// Début de la boucle de jeu
	sf::CircleShape player (30, 3);//rayon et nombre de points (3 points pour un triangle)
	player.setRadius(30.f);
	player.setFillColor(sf::Color::Green);
	player.setPosition(640, 360);//au centre de l'ecran
	sf::Vector2f playerPos;//Notre position de tir

	int shootTimer = 0;
	
	sf::RectangleShape enemy;
	enemy.setSize(sf::Vector2f(50.0f, 50.0f));
	enemy.setFillColor(sf::Color::Magenta);
	std::vector<sf::RectangleShape> enemies;
	enemies.push_back(sf::RectangleShape(enemy));//on ajoute un ennemi à notre tableau de taille dynamique d'ennemis
	int enemySpawnTimer = 0;

	sf::CircleShape bullet;
	bullet.setRadius(5.0f);
	bullet.setFillColor(sf::Color::Red);
	std::vector<sf::CircleShape> bullets;
	bullets.push_back(sf::CircleShape(bullet));//on ajoute une balle à notre tableau de taille dynamique de projectiles



	sf::Clock frameClock;

	while (window.isOpen())
	{
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

				default:
					break;
			}
		}

		float deltaTime = frameClock.restart().asSeconds();
		//std::cout << 1.f / deltaTime << " FPS" << std::endl;

		// Logique
		sf::Vector2f pos = player.getPosition();//vector2f = vecteur position avec 2 float
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			pos.x = pos.x - deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			pos.x = pos.x + deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			pos.y = pos.y - deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			pos.y = pos.y + deltaTime * cubeSpeed;

#pragma region BULLETS

		player.setPosition(pos);

		playerPos = sf::Vector2f(player.getPosition().x + (player.getRadius() * deltaTime), player.getPosition().y + (player.getRadius() * deltaTime));

		if (shootTimer < 5) {

			shootTimer++;
		}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >= 5)
		{
			shootTimer = 0;
			bullet.setPosition(playerPos);
			bullets.push_back(sf::CircleShape(bullet));
		}
		std::cout << shootTimer << "secondes" << std::endl;

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].move(0.f, -10.f);//offset x, offset y => on déplace la balle vers le bas 
			
			if (bullets[i].getPosition().y <= 0)//si la balle est hors de l'ecran
			{
				bullets.erase(bullets.begin() + i);//on supprime la balle si elle sort de l'écran. On place l'iterateur au debut
			}
		}
#pragma endregion


#pragma region BULLETS

		if (enemySpawnTimer < 20) {

			enemySpawnTimer++;
		}
		else {
			enemy.setPosition(rand() % int (window.getSize().x - enemy.getSize().x), 0.f);// spawn aléatoire entre le bord gauche et le bord droit de l'écran
			enemies.push_back(sf::RectangleShape(enemy));

			enemySpawnTimer = 0;
		}

		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].move(0.f, 5.f);//offset x, offset y => on déplace la balle vers le haut 

		}
#pragma endregion
			

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		window.draw(player);

		for (size_t i = 0; i < enemies.size(); i++) {
			window.draw(enemies[i]);// on dessine chaque ennemi
		}

		for (size_t i = 0; i < bullets.size(); i++)
			window.draw(bullets[i]);// on dessine chaque balle

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
