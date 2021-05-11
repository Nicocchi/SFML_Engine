#ifndef __STATE_HPP_24KU1GATURP2__
#define __STATE_HPP_24KU1GATURP2__

#include "Player.hpp"

/** Class Description
 *
 * @brief State
 *
 */
class State
{
private:
protected:
    std::stack<State *> *states; // Save universal state stack
    sf::RenderWindow *window;
    std::map<std::string, int> *supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;
    bool paused;
    float keytime;
    float keytimeMax;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Resources
    std::map<std::string, sf::Texture> textures;

    // Functions
    virtual void initKeybinds() = 0;

public:
    State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~State();

    // Accessors
    const bool &getQuit() const;
    /**
     * @brief Determines if the user can press the button based on keytime
     *
     * @return true
     * @return false
     */
    const bool getKeytime();

    // Functions
    /**
     * @brief Ends the state
     *
     */
    void endState();

    /**
     * @brief Pauses the state
     *
     */
    void pauseState();

    /**
     * @brief Unpauses the state
     *
     */
    void unpauseState();

    // virtual = 0 makes sure that when we inherit from this calss, we implement these functions in the child class
    /**
     * @brief Updates the mouse position
     *
     */
    virtual void updateMousePositions();

    /**
     * @brief Updates the keytime for button presses
     *
     * @param deltaTime Delta Time
     */
    virtual void updateKeytime(const float &deltaTime);

    /**
     * @brief Updates input
     *
     * @param deltaTime Delta Time
     */
    virtual void updateInput(const float &deltaTime) = 0;
    virtual void update(const float &deltaTime) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

#endif // __STATE_HPP_24KU1GATURP2__
