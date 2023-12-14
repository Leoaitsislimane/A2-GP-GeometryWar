#include "Menu.h"
#include <iostream>

void moveUpMenu(Menu& menu);
void moveDownMenu(Menu& menu);

void drawMenu(Menu& menu, sf::RenderWindow& window){
	window.draw(menu.title);

	for (const auto& selection : menu.menuSelect) {
		window.draw(selection);
	}
}



void moveDownMenu(Menu& menu) {

	if (menu.selectedItemIndex < 1) {
		menu.menuSelect[menu.selectedItemIndex].setFillColor(sf::Color::White);
		menu.selectedItemIndex++;
		menu.menuSelect[menu.selectedItemIndex - 1].setCharacterSize(40);
		menu.menuSelect[menu.selectedItemIndex].setFillColor(sf::Color::Yellow);
		menu.menuSelect[menu.selectedItemIndex].setCharacterSize(50);
	}

}

void processInputMenu(Menu& menu, sf::Event event, sf::RenderWindow& window) {

	switch (event.type) {
	case sf::Event::KeyReleased:
		switch (event.key.code) {
		case sf::Keyboard::Z:
			moveUpMenu(menu);
			break;

		case sf::Keyboard::S:
			moveDownMenu(menu);
			break;

		case sf::Keyboard::Return://bouton entrée
			if (menu.selectedItemIndex == 0) {
				menu.state = MenuState::Launch; // Lancer le jeu
			}
			else if (menu.selectedItemIndex == 1) {
				menu.state = MenuState::Exit; // Aller aux options
				window.close();
			}

			break;
		}

		break;
	}

}

void initialiseMenu(Menu& menu) {

	menu.font.loadFromFile("spacetime.ttf");
	menu.title.setFont(menu.font);
	menu.title.setString("Flop Invaders");
	menu.title.setCharacterSize(80);
	menu.title.setFillColor(sf::Color::Cyan);
	menu.title.setPosition(310, 100);

	menu.menuSelect[0].setString("Play");
	menu.menuSelect[1].setString("Quit");


	for (int i = 0; i < 2; ++i) {
		menu.menuSelect[i].setFont(menu.font);
		menu.menuSelect[i].setCharacterSize(40);
		menu.menuSelect[i].setFillColor(sf::Color::White);
		menu.menuSelect[i].setPosition(560, 280 + i * 70);
	}

	menu.selectedItemIndex = 0;
	menu.state = MenuState::Open;
	menu.menuSelect[0].setFillColor(sf::Color::Yellow);
	menu.menuSelect[0].setCharacterSize(50);


}
void moveUpMenu(Menu& menu) {

	if (menu.selectedItemIndex > 0) {// si on est pas au début du menu
		menu.menuSelect[menu.selectedItemIndex].setFillColor(sf::Color::White);
		menu.selectedItemIndex--;// on décrémente l'index pour le remonter dans le menu
		menu.menuSelect[menu.selectedItemIndex].setCharacterSize(50);
		menu.menuSelect[menu.selectedItemIndex].setFillColor(sf::Color::Yellow);
		menu.menuSelect[menu.selectedItemIndex + 1].setCharacterSize(40);


	}

}
