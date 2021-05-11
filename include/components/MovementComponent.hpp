#ifndef __MOVEMENT_COMPONENT_HPP_GB8B3H2N530E__
#define __MOVEMENT_COMPONENT_HPP_GB8B3H2N530E__

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

enum movement_states
{
    IDLE = 0,
    MOVING,
    MOVING_LEFT,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_DOWN
};

/** Class Description
 *
 * @brief MovementComponent
 * Class is dependent on the Sprite
 *
 */
class MovementComponent
{
private:
    sf::Sprite &sprite; // Directly affect the sprite of the Entity

    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

    // Inilization Functions

public:
    MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    // Accessors
    /**
     * @brief Returns the velocity of the entity
     *
     * @return const sf::Vector2f&
     */
    const sf::Vector2f &getVelocity() const;
    const float &getMaxVelocity() const;

    // Functions
    /**
     * @brief Get the current movement state
     *
     * @param state
     * @return true
     * @return false
     */
    bool getState(const short unsigned state) const;

    /**
     * @brief Move Entity
     *
     * @param dir_x
     * @param dir_y
     * @param deltaTime
     */
    void move(const float dir_x, const float dir_y, const float &deltaTime);

    /**
     * @brief Updates component
     *
     * @param deltaTime
     */
    void update(const float &deltaTime);
};

#endif // __MOVEMENT_COMPONENT_HPP_GB8B3H2N530E__
