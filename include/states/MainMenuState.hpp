#ifndef __MAIN_MENU_STATE_HPP_X04C1KGRPM7Q__
#define __MAIN_MENU_STATE_HPP_X04C1KGRPM7Q__

#include "EditorState.hpp"
#include "GameState.hpp"
#include "Gui.hpp"
#include "SettingsState.hpp"

/** Class Description
 *
 * @brief MainMenuState
 *
 */
class MainMenuState : public State
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
    MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~MainMenuState();

    // Functions
    void updateInput(const float &deltaTime);
    void updateButtons();
    void update(const float &deltaTime);
    void renderButtons(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);
};

#endif // __MAIN_MENU_STATE_HPP_X04C1KGRPM7Q__
