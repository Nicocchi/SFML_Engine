#ifndef __GUI_HPP_WZCNI5WF7RRK__
#define __GUI_HPP_WZCNI5WF7RRK__

#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

enum button_state
{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

namespace gui
{
    /** Class Description
     *
     * @brief Button
     *
     */
    class Button
    {
    private:
        short unsigned buttonState;

        sf::RectangleShape shape;
        sf::Font *font;
        sf::Text text;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

    public:
        Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, sf::Color idle_color,
               sf::Color hover_color, sf::Color active_color);
        virtual ~Button();

        // Accessors
        bool isPressed() const;

        // Functions
        void update(const sf::Vector2f &mousePos);
        void render(sf::RenderTarget &target);
    };

    class DropDownList
    {
    private:
        sf::Font &font;
        sf::RectangleShape activeElement;
        std::vector<gui::Button *> list;

    public:
        // Functions
        void update(const sf::Vector2f &mousePos);
        void render(sf::RenderTarget &target);
    };
} // namespace gui

#endif // __GUI_HPP_WZCNI5WF7RRK__
