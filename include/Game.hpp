#ifndef __GAME_HPP_5HH6ZUZLW82U__
#define __GAME_HPP_5HH6ZUZLW82U__

#include "MainMenuState.hpp"

/** Class Description
 *
 * @brief Game
 * 
 */
class Game
{
private:
    // Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;
    bool fullscreen;

    // DeltaTime keeps track of how long it takes our game to do one update call and one render call (aka: one frame)
    sf::Clock dtClock;
    float dt; // Delta time.

    std::stack<State *> states;

    std::map<std::string, int> supportedKeys;

    // Initalization Functions
    void initVariables();
    void initWindow();
    void initKeys();
    void initStates();

public:
    // Constructors / Destructors
    Game();
    virtual ~Game();

    // Functions

    // Regular
    void endApplication();

    // Update
    void updateDt();
    void updateSFMLEvents();
    void update();

    // Render
    void render();

    // Core
    void run();
};

#endif // __GAME_HPP_5HH6ZUZLW82U__
