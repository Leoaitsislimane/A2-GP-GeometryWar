#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void handleInput();

private:
    sf::CircleShape player;
    float speed;
};

#endif // PLAYER_H
