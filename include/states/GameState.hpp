#ifndef __GAME_STATE_HPP_11CYHHJ36S08__
#define __GAME_STATE_HPP_11CYHHJ36S08__

#include "PauseMenu.hpp"
#include "State.hpp"

/** Class Description
 *
 * @brief GameState
 *
 */
class GameState : public State
{
private:
    sf::Font font;
    PauseMenu *pmenu;

    Player *player;

    // Initiliazation Functions
    void initKeybinds();
    void initFonts();
    void intiTextures();
    void initPauseMenu();
    void initPlayers();

public:
    GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~GameState();

    // Functions
    void updateInput(const float &deltaTime);
    void updatePlayerInput(const float &deltaTime);
    void updatePauseMenuButtons();
    void update(const float &deltaTime);
    void render(sf::RenderTarget *target = nullptr);
};

#endif // __GAME_STATE_HPP_11CYHHJ36S08__
