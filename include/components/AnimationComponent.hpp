#ifndef __ANIMATION_COMPONENT_HPP_C6X66FDSUEB9__
#define __ANIMATION_COMPONENT_HPP_C6X66FDSUEB9__

#include <iostream>
#include <map>
#include <string>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

/** Class Description
 *
 * @brief AnimationComponent
 *
 */
class AnimationComponent
{
private:
    class Animation
    {
    public:
        // Variables
        sf::Sprite &sprite;
        sf::Texture &textureSheet;
        float animationTimer;
        float timer;
        bool done;
        int width;
        int height;
        sf::IntRect currentRect;
        sf::IntRect startRect;
        sf::IntRect endRect;

        // start_frame_x/y -> frame starting at. frame_x/y -> How many frames in the animation
        Animation(sf::Sprite &sprite, sf::Texture &texture_sheet, float animation_timer, int start_frame_x,
                  int start_frame_y, int frames_x, int frames_y, int width, int height)
            : sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), timer(0.f), done(false), width(width), height(height)
        {
            this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
            this->currentRect = this->startRect;
            this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

            this->sprite.setTexture(this->textureSheet, true);
            this->sprite.setTextureRect(this->startRect);
        }

        // Accessor
        const bool &isDone() const
        {
            return this->done;
        }

        // Functions
        const bool &play(const float &deltaTime)
        {
            // Update timer
            this->done = false;
            this->timer += 100.f * deltaTime;
            if (this->timer >= this->animationTimer)
            {
                // Reset timer - not frame rate dependent
                this->timer = 0.f;

                // Animate
                if (this->currentRect != this->endRect)
                {
                    this->currentRect.left += this->width;
                }
                else // Reset
                {
                    this->currentRect.left = this->startRect.left;
                    this->done = true;
                }

                this->sprite.setTextureRect(this->currentRect);
            }

            return this->done;
        }

        const bool &play(const float &deltaTime, float mod_percent)
        {
            // Update timer
            if (mod_percent < 0.5f)
            {
                mod_percent = 0.5f;
            }
            
            this->done = false;
            this->timer += mod_percent * 100.f * deltaTime;
            if (this->timer >= this->animationTimer)
            {
                // Reset timer - not frame rate dependent
                this->timer = 0.f;

                // Animate
                if (this->currentRect != this->endRect)
                {
                    this->currentRect.left += this->width;
                }
                else // Reset
                {
                    this->currentRect.left = this->startRect.left;
                    this->done = true;
                }

                this->sprite.setTextureRect(this->currentRect);
            }

            return this->done;
        }

        void reset()
        {
            this->timer = this->animationTimer;
            this->currentRect = this->startRect;
        }
    };

    sf::Sprite &sprite;
    sf::Texture &textureSheet;
    std::map<std::string, Animation *> animations;
    Animation *lastAnimation;
    Animation *priorityAnimation;

public:
    AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet);
    virtual ~AnimationComponent();

    // Accessor
    const bool &isDone(const std::string key);

    // Functions
    void addAnimation(const std::string key, float animation_timer, int start_frame_x, int start_frame_y, int frames_x,
                      int frames_y, int width, int height);

    const bool &play(const std::string key, const float &deltaTime, const bool priority = false); // Update all animations
    const bool &play(const std::string key, const float &deltaTime, const float &modifier, const float &modifier_max,
              const bool priority = false);
};

#endif // __ANIMATION_COMPONENT_HPP_C6X66FDSUEB9__
