#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>


constexpr float cubeSpeed = 500.f;

constexpr float reloadTime = 2.0f;
float currentReloadTime = reloadTime;


enum class MenuState {
	Open,
	Launch,
	Exit
};

# pragma region MAIN_MENU

class MainMenu {
public:
	MainMenu(sf::RenderWindow& window) : window(window) {
		font.loadFromFile("spacetime.ttf");
		title.setFont(font);
		title.setString("Nom du Jeu");
		title.setCharacterSize(40);
		title.setFillColor(sf::Color::White);
		title.setPosition(200, 100);

		menuOptions[0].setString("Jouer");
		menuOptions[1].setString("Quitter");


		for (int i = 0; i < 2; ++i) {
			menuOptions[i].setFont(font);
			menuOptions[i].setCharacterSize(30);
			menuOptions[i].setFillColor(sf::Color::White);
			menuOptions[i].setPosition(300, 250 + i * 50);
		}

		selectedItemIndex = 0;
		state = MenuState::Open;
	}

	void draw() {
		
		window.draw(title);

		for (const auto& option : menuOptions) {
			window.draw(option);
		}

	}

	void moveUp() {
		if (selectedItemIndex > 0) {
			menuOptions[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex--;
			menuOptions[selectedItemIndex].setFillColor(sf::Color::Yellow);
		}
	}

	void moveDown() {
		if (selectedItemIndex < 1) {
			menuOptions[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex++;
			menuOptions[selectedItemIndex].setFillColor(sf::Color::Yellow);
		}
	}

	void processInput(sf::Event event) {
		
	
			switch (event.type) {
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Up:
					moveUp();
					break;

				case sf::Keyboard::Down:
					moveDown();
					break;

				case sf::Keyboard::Return:
					if (selectedItemIndex == 0) {
						state = MenuState::Launch; // Lancer le jeu
					}
					else if (selectedItemIndex == 1) {
						state = MenuState::Exit; // Aller aux options
						window.close();
					}
				
					break;
				}

				break;
			}
	}

		

public:
	sf::RenderWindow& window;
	sf::Font font;
	sf::Text title;
	sf::Text menuOptions[2];
	int selectedItemIndex;
	MenuState state;
};
#pragma endregion


int main()
{
	// Initialisation

	srand(time(NULL));//on initialise le random

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars");
	window.setVerticalSyncEnabled(true);
	MainMenu mainMenu(window);

	// Début de la boucle de jeu
	sf::CircleShape player(30, 3);//rayon et nombre de points (3 points pour un triangle)
	player.setRadius(30.f);
	player.setFillColor(sf::Color::Green);
	player.setPosition(640, 360);//au centre de l'ecran
	sf::Vector2f playerPos;//Notre position de tir

	int shootTimer = 0;

	sf::RectangleShape enemy;
	enemy.setSize(sf::Vector2f(40.0f, 40.0f));
	enemy.setOutlineColor(sf::Color::Magenta);
	enemy.setOutlineThickness(5.0f);
	enemy.setFillColor(sf::Color::Transparent);
	std::vector<sf::RectangleShape> enemies;
	enemies.push_back(sf::RectangleShape(enemy));//on ajoute un ennemi à notre tableau de taille dynamique d'ennemis
	int enemySpawnTimer = 0;

	sf::CircleShape bullet;
	bullet.setRadius(5.0f);
	bullet.setFillColor(sf::Color::Red);
	std::vector<sf::CircleShape> bullets;
	bullets.push_back(sf::CircleShape(bullet));//on ajoute une balle à notre tableau de taille dynamique de projectiles



	sf::Clock frameClock;


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
		float time = frameClock.getElapsedTime().asSeconds();
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
			if (mainMenu.state == MenuState::Open) {
				mainMenu.processInput(event);
			}
		}



		float deltaTime = frameClock.restart().asSeconds();
		//std::cout << 1.f / deltaTime << " FPS" << std::endl; 

		
			// Dessiner le jeu
			
			


		// Logique
		sf::Vector2f pos = player.getPosition();//vector2f = vecteur position avec 2 float
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			pos.x = pos.x - deltaTime * cubeSpeed; // pos.x -= deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			pos.x = pos.x + deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			pos.y = pos.y - deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			pos.y = pos.y + deltaTime * cubeSpeed;

		player.setPosition(pos);

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


#pragma region ENEMIES

		if (enemySpawnTimer < 30) {

			enemySpawnTimer++;
		}
		else {
			enemy.setPosition(rand() % int(window.getSize().x - enemy.getSize().x), 0.f);// spawn aléatoire entre le bord gauche et le bord droit de l'écran
			enemies.push_back(sf::RectangleShape(enemy));

			enemySpawnTimer = 0;
		}

		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].move(0.f, 5.f);//offset x, offset y => on déplace la balle vers le haut 

			if (enemies[i].getPosition().y > window.getSize().y) {
				enemies.erase(enemies.begin() + i);
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
		if (mainMenu.state == MenuState::Open) {
			mainMenu.draw();

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
