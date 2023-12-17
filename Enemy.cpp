#include "Enemy.h"

Enemy::Enemy(float startX, float startY) : speed(2.f) {
    enemy.setSize(sf::Vector2f(40.f, 40.f));
    enemy.setOutlineColor(sf::Color::Magenta);
    enemy.setOutlineThickness(5.f);
    enemy.setFillColor(sf::Color::Transparent);
    enemy.setPosition(startX, startY);
}

void Enemy::update(float deltaTime) {
    enemy.move(0.f, speed * deltaTime);

    // Mettre à jour la logique de l'ennemi
    // ...
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(enemy);
}

sf::FloatRect Enemy::getGlobalBounds() {
    return enemy.getGlobalBounds();
}
