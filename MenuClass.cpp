#include "MenuClass.h"
#include <iostream>



void MenuClass::drawMenu(sf::RenderWindow& window) {
	window.draw(title);

	for (const auto& selection : menuSelect) {
		window.draw(selection);
	}
}


void MenuClass::moveDownMenu() {

	if (selectedItemIndex < 1) {
		menuSelect[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menuSelect[selectedItemIndex - 1].setCharacterSize(40);
		menuSelect[selectedItemIndex].setFillColor(sf::Color::Yellow);
		menuSelect[selectedItemIndex].setCharacterSize(50);
	}

}

void MenuClass::processInputMenu(sf::Event event, sf::RenderWindow& window) {

	switch (event.type) {
	case sf::Event::KeyReleased:
		switch (event.key.code) {
		case sf::Keyboard::Z:
			moveUpMenu();
			break;

		case sf::Keyboard::S:
			moveDownMenu();
			break;

		case sf::Keyboard::Return://bouton entrée
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

 MenuClass::MenuClass() {

	font.loadFromFile("spacetime.ttf");
	title.setFont(font);
	title.setString("Flop Invaders");
	title.setCharacterSize(80);
	title.setFillColor(sf::Color::Cyan);
	title.setPosition(310, 100);

	menuSelect[0].setString("Play");
	menuSelect[1].setString("Quit");


	for (int i = 0; i < 2; ++i) {
		menuSelect[i].setFont(font);
		menuSelect[i].setCharacterSize(40);
		menuSelect[i].setFillColor(sf::Color::White);
		menuSelect[i].setPosition(560, 280 + i * 70);
	}

	selectedItemIndex = 0;
	state = MenuState::Open;
	menuSelect[0].setFillColor(sf::Color::Yellow);
	menuSelect[0].setCharacterSize(50);


}
void MenuClass::moveUpMenu() {

	if (selectedItemIndex > 0) {// si on est pas au début du menu
		menuSelect[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;// on décrémente l'index pour le remonter dans le menu
		menuSelect[selectedItemIndex].setCharacterSize(50);
		menuSelect[selectedItemIndex].setFillColor(sf::Color::Yellow);
		menuSelect[selectedItemIndex + 1].setCharacterSize(40);


	}

}
