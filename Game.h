#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "MenuClass.h"

class Game {
public:
    Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void EnemySpawn(float spawnInterval, float moveSpeed, float deltaTime, Enemy& enemy, std::vector<sf::RectangleShape>& enemies, sf::RenderWindow& window, float gameTime);
    void checkCollisions();

    sf::RenderWindow window;
    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    float countDownDuration;
    int shootTimer;
    int enemySpawnTimer;
    bool gameOver;
    int bestScore;
    MenuClass gameMenu;

    sf::Clock frameClock;
    sf::Clock gameClock;
};

#endif // GAME_H
