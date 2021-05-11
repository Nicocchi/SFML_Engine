#ifndef __ENTITY_HPP_R6TTKF55IENG__
#define __ENTITY_HPP_R6TTKF55IENG__

#include "AnimationComponent.hpp"
#include "HitboxComponent.hpp"
#include "MovementComponent.hpp"

/** Class Description
 *
 * @brief Entity
 *
 */
class Entity
{
private:
    void initVariables();

protected:
    sf::Sprite sprite;

    HitboxComponent *hitboxComponent;
    MovementComponent *movementComponent;
    AnimationComponent *animationComponent;

public:
    Entity();
    virtual ~Entity();

    // Component Functions
    void setTexture(sf::Texture &texture);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture &texture_sheet);
    void createHitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height);

    // Functions
    virtual void setPosition(const float x, const float y);
    virtual void move(const float dir_x, const float dir_y, const float &deltaTime);

    virtual void update(const float &deltaTime);
    virtual void render(sf::RenderTarget &target);
};

#endif // __ENTITY_HPP_R6TTKF55IENG__
