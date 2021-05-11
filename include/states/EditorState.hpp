#ifndef __EDITOR_STATE_HPP_ZDWMSKYXVMHY__
#define __EDITOR_STATE_HPP_ZDWMSKYXVMHY__

#include "Gui.hpp"
#include "State.hpp"

/** Class Description
 *
 * @brief EditorState
 *
 */
class EditorState : public State
{
private:
    // Variables
    sf::Font font;

    std::map<std::string, gui::Button *> buttons;

    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    EditorState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~EditorState();

    // Functions
    void updateInput(const float &deltaTime);
    void updateButtons();
    void update(const float &deltaTime);
    void renderButtons(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);
};

#endif // __EDITOR_STATE_HPP_ZDWMSKYXVMHY__
