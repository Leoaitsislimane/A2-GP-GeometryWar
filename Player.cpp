#include "Player.h"

Player::Player() : speed(800.f) {
    player.setRadius(30.f);
    player.setPointCount(3); // Triangle
    player.setOrigin(30.f, 30.f);
    player.setFillColor(sf::Color::Green);
    player.setPosition(980.f, 920.f);
}

void Player::update(float deltaTime) {
    
    // Logique
    sf::Vector2f pos = player.getPosition();//vector2f = vecteur position avec 2 float
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        pos.x = pos.x - deltaTime * speed; // pos.x -= deltaTime * speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        pos.x = pos.x + deltaTime * speed;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(player);
}

void Player::handleInput() {
    

}
