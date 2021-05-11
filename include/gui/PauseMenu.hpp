#ifndef __PAUSEMENU_HPP_3CE6ED374124_
#define __PAUSEMENU_HPP_3CE6ED374124_

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>

#include "Gui.hpp"

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

class PauseMenu
{
private:
    sf::Font &font;
    sf::Text menuText;

    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, gui::Button *> buttons;

    // Functions

public:
    PauseMenu(sf::RenderWindow &window, sf::Font &font);
    virtual ~PauseMenu();

    // Accessor
    std::map<std::string, gui::Button *> &getButtons();

    // Functions
    const bool isButtonPressed(const std::string key);
    void addButton(const std::string key, float y, const std::string text);
    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget &target);
};

#endif // __PAUSEMENU_HPP_3CE6ED374124_
