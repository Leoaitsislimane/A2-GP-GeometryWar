#pragma once
#include <SFML/Graphics.hpp>

enum class MenuState {
	Open,
	Launch,
	Exit
};

struct Menu
{
	sf::Font font;
	sf::Text title;
	sf::Text menuSelect[2];
	int selectedItemIndex;
	MenuState state;
};

void drawMenu(Menu& menu, sf::RenderWindow& window);
void processInputMenu(Menu& menu, sf::Event event, sf::RenderWindow& window);
void initialiseMenu(Menu& menu);
