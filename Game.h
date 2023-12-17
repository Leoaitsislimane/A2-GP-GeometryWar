// Game.h
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MenuClass.h"

class Game {
    float cubeSpeed = 800.f;

    float reloadTime = 0.4f;
    float currentReloadTime = reloadTime;

    int shootTimer = 0.5;
    int enemySpawnTimer = 0;

    int score = 0;
public:
    Game();
    void run();

public:
    void processInput();
    void update(float deltaTime);
    void render();

    void playerMovement(float deltaTime);
    void shooting(float deltaTime);
    void updateBullets(float deltaTime);
    void updateEnemies(float deltaTime);
    void handleCollisions();
    void EnemySpawn(float spawnInterval, float moveSpeed, float deltaTime, sf::RectangleShape& enemy, std::vector<sf::RectangleShape>& enemies, sf::RenderWindow& window);


    sf::RenderWindow window;
    sf::Music music;

    sf::CircleShape player;
    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies;

    sf::CircleShape bullet;
    std::vector<sf::CircleShape> bullets;

    sf::Clock frameClock;
    sf::Clock gameClock;

    sf::Font myFont;
    sf::Text scoreboard;

    // Other game-related variables and functions...
};
