#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(float startX, float startY);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds();

private:
    sf::RectangleShape enemy;
    float speed;
};

#endif // ENEMY_H
