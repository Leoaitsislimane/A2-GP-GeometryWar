//MenuClass.h

#pragma once
#include <SFML/Graphics.hpp>

enum class MenuState {
	Open,
	Launch,
	Exit
};

class MenuClass
{
public:
	MenuState state;

	void drawMenu(sf::RenderWindow& window);
	void processInputMenu(sf::Event event, sf::RenderWindow& window);
	MenuClass();

private:
	sf::Font font;
	sf::Text title;
	sf::Text menuSelect[2];
	int selectedItemIndex;

	void moveUpMenu();
	void moveDownMenu();
};
