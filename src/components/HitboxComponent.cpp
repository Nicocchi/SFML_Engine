#include "HitboxComponent.hpp"

HitboxComponent::HitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height)
    : sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
    this->hitbox.setPosition(this->sprite.getPosition().x + offsetX, this->sprite.getPosition().y + offsetY);
    this->hitbox.setSize(sf::Vector2f(width, height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(1.0f);
    this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
    // TODO: Needs implementation
}

bool HitboxComponent::checkIntersect(const sf::FloatRect &frect)
{
    return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update()
{
    this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX,
                             this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget &target) { target.draw(this->hitbox); }