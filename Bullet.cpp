#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position) : speed(10.f) {
    bullet.setRadius(5.f);
    bullet.setFillColor(sf::Color::Red);
    bullet.setPosition(position);
}

void Bullet::update(float deltaTime) {
    bullet.move(0.f, -speed * deltaTime);

    // Mettre à jour la logique du projectile
    // ...
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(bullet);
}

sf::FloatRect Bullet::getGlobalBounds() {
    return bullet.getGlobalBounds();
}
