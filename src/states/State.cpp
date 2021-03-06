#include "State.hpp"

State::State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
{
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->states = states;
    this->quit = false;
    this->paused = false;
    this->keytime = 0.f;
    this->keytimeMax = 10.f;
}

State::~State() {}

// Accessors
const bool &State::getQuit() const { return this->quit; }

const bool State::getKeytime()
{
    // Resets the keytime and returns true if keytime is equal to keytimeMax
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }

    return false;
}

// Functions
void State::endState() { this->quit = true; }

void State::pauseState() { this->paused = true; }

void State::unpauseState() { this->paused = false; }

void State::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView =
        this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)); // Maps a pixel on the window to coords
}

void State::updateKeytime(const float &deltaTime)
{
    if (this->keytime < this->keytimeMax)
    {
        this->keytime += 50.f * deltaTime;
    }
}
