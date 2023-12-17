// Game.cpp
#include "Game.h"

Game::Game() : window(sf::VideoMode(1920, 1080), "Geometry Wars") {

	

	window.setVerticalSyncEnabled(true);

	// Load font
	myFont.loadFromFile("spacetime.ttf");

	// Initialize player as a triangle using sf::ConvexShape
	player.setPointCount(3);  // Set the number of points for a triangle
	player.setRadius(30.f);   // Radius is not used for triangles, but it's required to set a size
	player.setFillColor(sf::Color::Green);
	player.setOrigin(30, 30);
	player.setPosition(980, 920);

	// Initialize enemy
	enemy.setSize(sf::Vector2f(40.0f, 40.0f));
	enemy.setOutlineColor(sf::Color::Magenta);
	enemy.setOutlineThickness(5.0f);
	enemy.setFillColor(sf::Color::Transparent);

	// Initialize bullet
	bullet.setRadius(5.0f);
	bullet.setFillColor(sf::Color::Red);
	bullet.setOrigin(5, 5);

	// Initialize scoreboard
	scoreboard.setFont(myFont);
	scoreboard.setFillColor(sf::Color::Yellow);
	scoreboard.setCharacterSize(54);
	scoreboard.setString(std::to_string(score));

	// Initialize other game-related variables...
}

void Game::run() {
	while (window.isOpen()) {
		processInput();
		update(frameClock.restart().asSeconds());
		render();
	}
}

void Game::processInput() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			// Handle events
		case sf::Event::Closed:
			window.close();
			break;
		}
	}

	// Handle player input, shooting, etc.
}

void Game::update(float deltaTime) {
	float time = frameClock.getElapsedTime().asSeconds();

	playerMovement(deltaTime);
	shooting(deltaTime);
	updateBullets(deltaTime);
	updateEnemies(deltaTime);
	handleCollisions();
}

void Game::render() {
	window.clear();

	MenuClass gameMenu;
	gameMenu.drawMenu(window);

	// Draw player
	window.draw(player);

	// Draw enemies
	for (const auto& enemy : enemies) {
		window.draw(enemy);
	}

	// Draw bullets
	for (const auto& bullet : bullets) {
		window.draw(bullet);
	}

	// Draw scoreboard
	window.draw(scoreboard);

	// Display the window
	window.display();

}

void Game::playerMovement(float deltaTime) {
	// Handle player movement logic
	sf::Vector2f pos = player.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		pos.x -= deltaTime * cubeSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		pos.x += deltaTime * cubeSpeed;
	}

	

	player.setPosition(pos);
}

void Game::shooting(float deltaTime) {
	// Handle shooting logic
	sf::Vector2f playerPos = player.getPosition();

	if (shootTimer < reloadTime * 60) {
		shootTimer++;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		shootTimer = 0;
		bullet.setPosition(playerPos);
		bullets.push_back(sf::CircleShape(bullet));
	}
}

void Game::updateBullets(float deltaTime) {
	// Update bullet logic
	for (size_t i = 0; i < bullets.size(); i++) {
		bullets[i].move(0.f, -10.f);

		if (bullets[i].getPosition().y <= 0) {
			bullets.erase(bullets.begin() + i);
		}
	}
}

void Game::EnemySpawn(float spawnInterval, float moveSpeed, float deltaTime, sf::RectangleShape& enemy, std::vector<sf::RectangleShape>& enemies, sf::RenderWindow& window) {
	if (enemySpawnTimer * deltaTime < spawnInterval) {
		enemySpawnTimer++;
	}
	else {
		enemy.setPosition(rand() % int(window.getSize().x - enemy.getSize().x), 0.f);
		enemies.push_back(sf::RectangleShape(enemy));
		enemySpawnTimer = 0;
	}

	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i].move(0.f, moveSpeed);

		if (enemies[i].getPosition().y > window.getSize().y) {
			window.close();
		}
	}
}

void Game::updateEnemies(float deltaTime) {
	// Update enemy logic
	// Add your enemy update logic here
}

void Game::handleCollisions() {

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
}
