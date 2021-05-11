#ifndef __PLAYER_HPP_44WWODD0QR1W__
#define __PLAYER_HPP_44WWODD0QR1W__

#include "Entity.hpp"

/** Class Description
 *
 * @brief Player
 *
 */
class Player : public Entity
{
private:
    // Variables
    bool attacking;

    // Initialization Functions
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture &texture_sheet);
    virtual ~Player();

    // Functions
    void updateAttack();
    void updateAnimation(const float &deltaTime);
    virtual void update(const float &deltaTime);
};

#endif // __PLAYER_HPP_44WWODD0QR1W__
