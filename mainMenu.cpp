#include <SFML/Graphics.hpp>

enum class MenuState {
    MainMenu,
    Options,
    Exit
};

class MainMenu {
public:
    MainMenu(sf::RenderWindow& window) : window(window) {
        font.loadFromFile("arial.ttf");
        title.setFont(font);
        title.setString("Nom du Jeu");
        title.setCharacterSize(40);
        title.setFillColor(sf::Color::White);
        title.setPosition(200, 100);

        menuOptions[0].setString("Jouer");
        menuOptions[1].setString("Options");
        menuOptions[2].setString("Quitter");

        for (int i = 0; i < 3; ++i) {
            menuOptions[i].setFont(font);
            menuOptions[i].setCharacterSize(30);
            menuOptions[i].setFillColor(sf::Color::White);
            menuOptions[i].setPosition(300, 250 + i * 50);
        }

        selectedItemIndex = 0;
        menuState = MenuState::MainMenu;
    }

    void draw() {
        window.clear();

        window.draw(title);

        for (const auto& option : menuOptions) {
            window.draw(option);
        }

        window.display();
    }

    void moveUp() {
        if (selectedItemIndex > 0) {
            menuOptions[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex--;
            menuOptions[selectedItemIndex].setFillColor(sf::Color::Yellow);
        }
    }

    void moveDown() {
        if (selectedItemIndex < 2) {
            menuOptions[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex++;
            menuOptions[selectedItemIndex].setFillColor(sf::Color::Yellow);
        }
    }

    MenuState processInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    moveUp();
                    break;

                case sf::Keyboard::Down:
                    moveDown();
                    break;

                case sf::Keyboard::Return:
                    if (selectedItemIndex == 0) {
                        return MenuState::MainMenu; // Lancer le jeu
                    }
                    else if (selectedItemIndex == 1) {
                        return MenuState::Options; // Aller aux options
                    }
                    else {
                        return MenuState::Exit; // Quitter le jeu
                    }

                default:
                    break;
                }
                break;

            case sf::Event::Closed:
                return MenuState::Exit;

            default:
                break;
            }
        }

        return MenuState::MainMenu;
    }

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text title;
    sf::Text menuOptions[3];
    int selectedItemIndex;
    MenuState menuState;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Menu Example");
    window.setFramerateLimit(60);

    MainMenu mainMenu(window);

    while (true) {
        mainMenu.draw();
        MenuState result = mainMenu.processInput();

        if (result == MenuState::Exit) {
            break;
        }
        else if (result == MenuState::Options) {
            // Code pour le menu des options (à implémenter)
        }
        else {
            // Code pour lancer le jeu (à implémenter)
        }
    }

    return 0;
}
