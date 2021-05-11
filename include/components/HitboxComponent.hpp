#ifndef __HITBOX_COMPONENT_HPP_3WGD4ZJTRIO7__
#define __HITBOX_COMPONENT_HPP_3WGD4ZJTRIO7__

#include <cstdlib>
#include <ctime>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

/** Class Description
 *
 * @brief HitboxComponent
 *
 */
class HitboxComponent
{
private:
    sf::Sprite &sprite;
    sf::RectangleShape hitbox;
    float offsetX;
    float offsetY;

public:
    HitboxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height);
    virtual ~HitboxComponent();

    // Functions
    bool checkIntersect(const sf::FloatRect &frect);
    void update();
    void render(sf::RenderTarget &target);
};

#endif // __HITBOX_COMPONENT_HPP_3WGD4ZJTRIO7__
