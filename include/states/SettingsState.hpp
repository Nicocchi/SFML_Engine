#ifndef __SETTINGS_STATE_HPP_8605CBF9E064_
#define __SETTINGS_STATE_HPP_8605CBF9E064_

#include "Gui.hpp"
#include "State.hpp"

class SettingsState : public State
{
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button *> buttons;

    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~SettingsState();

    // Accessors

    // Functions
    void updateInput(const float &deltaTime);
    void updateButtons();
    void update(const float &deltaTime);
    void renderButtons(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);
};

#endif // __SETTINGS_STATE_HPP_8605CBF9E064_
