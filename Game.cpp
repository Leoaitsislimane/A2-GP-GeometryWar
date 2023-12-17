#include "Game.h"

int score = 0;

Game::Game() : window(sf::VideoMode(1920, 1080), "Geometry Wars"), player(), countDownDuration(60.0f), shootTimer(0), enemySpawnTimer(0), gameOver(false), bestScore(39), gameMenu() {
    window.setVerticalSyncEnabled(true);
    srand(time(NULL));
    // Autres initialisations au besoin
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        //// Envoyer l'événement au menu
        //if (gameMenu.state == MenuState::Open) {
        //    gameMenu.processInputMenu(event, window);
        //}
    }

    player.handleInput();
}

void Game::update() {
    float deltaTime = frameClock.restart().asSeconds();
    float gameTime = gameClock.getElapsedTime().asSeconds();

    /*if (gameTime < 10) {
        EnemySpawn(1.5f, 2.f, deltaTime, enemy, enemies, window, gameTime);
    }
    else if (gameTime < 20) {
        EnemySpawn(1.f, 4.f, deltaTime, enemy, enemies, window, gameTime);
    }
    else if (gameTime < 30) {
        EnemySpawn(0.5f, 6.f, deltaTime, enemy, enemies, window, gameTime);
    }
    else if (gameTime < 40) {
        EnemySpawn(0.5f, 8.f, deltaTime, enemy, enemies, window, gameTime);
    }
    else if (gameTime < 50) {
        EnemySpawn(0.2f, 10.f, deltaTime, enemy, enemies, window, gameTime);
    }*/

    player.update(deltaTime);

    // Mettre à jour la logique du jeu
    // ...

}

void Game::render() {
    window.clear();

    // Dessiner le menu si nécessaire
    if (gameMenu.state == MenuState::Open) {
        gameMenu.drawMenu(window);
    }
    else {
        // Dessiner les autres éléments du jeu
        player.draw(window);

        for (auto& bullet : bullets)
            bullet.draw(window);

        for (auto& enemy : enemies)
            enemy.draw(window);

        // ...
    }

    window.display();
}

void Game::EnemySpawn(float spawnInterval, float moveSpeed, float deltaTime, Enemy& enemy, std::vector<sf::RectangleShape>& enemies, sf::RenderWindow& window, float gameTime) {
    if (enemySpawnTimer * deltaTime < spawnInterval) {
        // Spawn enemy
        enemySpawnTimer++;
    }
    else {
        // Spawn enemies à des positions aléatoires les bords gauches et droits de l'écran
       /* enemy.setPosition(rand() % int(window.getSize().x - enemy.getSize().x), 0.f);
        enemies.push_back(sf::RectangleShape(enemy));
        enemySpawnTimer = 0;*/
    }

    // deplacer les ennemis vers le bas
    for (size_t i = 0; i < enemies.size(); i++) {
        enemies[i].move(0.f, moveSpeed);

        // supp les ennemis qui sortent de l'écran
        if (enemies[i].getPosition().y > window.getSize().y) {
            enemies.erase(enemies.begin() + i);
        }
    }

//void Game::checkCollisions() {
//    float deltaTime = frameClock.restart().asSeconds();
//
//    for (size_t i = 0; i < bullets.size(); i++) {
//        for (size_t j = 0; j < enemies.size(); j++) {
//            if (bullets[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
//                // Mettre à jour la logique de collision
//                // ...
//                bullets.erase(bullets.begin() + i);
//                enemies.erase(enemies.begin() + j);
//                break;
//            }
//        }
//    }

    countDownDuration -= deltaTime;

    if (gameTime > 59 && !gameOver) {
        gameOver = true;

        if (score > bestScore) {
            bestScore = score;
        }
    }
}
