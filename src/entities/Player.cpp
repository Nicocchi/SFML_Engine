#include "Player.hpp"

// Initialization Functions
void Player::initVariables() { this->attacking = false; }
void Player::initComponents() {}

// Constructors / Destructors
Player::Player(float x, float y, sf::Texture &texture_sheet)
{
    this->initVariables();

    this->setPosition(x, y);

    this->createHitboxComponent(this->sprite, 86.f, 71.f, 86.f, 111.f);
    this->createMovementComponent(300.f, 13.f, 5.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 13, 0, 192, 192);
    this->animationComponent->addAnimation("WALK", 6.f, 0, 1, 11, 1, 192, 192);
    this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192 * 2, 192);
}

Player::~Player() {}

// Functions
void Player::updateAttack()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        this->attacking = true;
    }
}

void Player::updateAnimation(const float &deltaTime)
{
    if (this->attacking)
    {
        // Set origin depending on direction
        if (this->sprite.getScale().x > 0.f) // Facing left
        {
            this->sprite.setOrigin(96.f, 0.f);
        }
        else // Facing right
        {
            this->sprite.setOrigin(258.f + 96.f, 0.f);
        }

        // Animate and check for animation end
        if (this->animationComponent->play("ATTACK", deltaTime, true))
        {
            this->attacking = false;

            // Reset origin
            if (this->sprite.getScale().x > 0.f) // Facing left
            {
                this->sprite.setOrigin(0.f, 0.f);
            }
            else // Facing right
            {
                this->sprite.setOrigin(258.f, 0.f);
            }
        }
    }

    // Movement
    if (this->movementComponent->getState(IDLE))
    {
        this->animationComponent->play("IDLE", deltaTime);
    }
    else if (this->movementComponent->getState(MOVING_LEFT))
    {
        if (this->sprite.getScale().x < 0.f)
        {
            this->sprite.setOrigin(0.f, 0.f);
            this->sprite.setScale(1.f, 1.f);
        }

        this->animationComponent->play("WALK", deltaTime, this->movementComponent->getVelocity().x,
                                       this->movementComponent->getMaxVelocity());
    }
    else if (this->movementComponent->getState(MOVING_RIGHT))
    {
        if (this->sprite.getScale().x > 0.f)
        {
            this->sprite.setOrigin(258.f, 0.f);
            this->sprite.setScale(-1.f, 1.f);
        }

        this->animationComponent->play("WALK", deltaTime, this->movementComponent->getVelocity().x,
                                       this->movementComponent->getMaxVelocity());
    }
    else if (this->movementComponent->getState(MOVING_UP))
    {
        this->animationComponent->play("WALK", deltaTime, this->movementComponent->getVelocity().y,
                                       this->movementComponent->getMaxVelocity());
    }
    else if (this->movementComponent->getState(MOVING_DOWN))
    {
        this->animationComponent->play("WALK", deltaTime, this->movementComponent->getVelocity().y,
                                       this->movementComponent->getMaxVelocity());
    }
}

void Player::update(const float &deltaTime)
{
    // Movement
    this->movementComponent->update(deltaTime);

    // Attacking
    this->updateAttack();

    // Animation
    this->updateAnimation(deltaTime);

    // Hitbox
    this->hitboxComponent->update();
}
