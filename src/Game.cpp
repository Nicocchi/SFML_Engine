#include "Game.hpp"

// Static Functions

// Initialization Functions
void Game::initVariables()
{
    this->window = nullptr;
    this->fullscreen = false;
    this->dt = 0.f;
}

void Game::initWindow()
{
    // Load config init file for window
    std::ifstream ifs("config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    // Set default values
    std::string title = "Untitled";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    // Read config file if open
    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }

    ifs.close();

    this->fullscreen = fullscreen;
    // Context settings
    this->windowSettings.antialiasingLevel = antialiasing_level;

    // Create window
    if (this->fullscreen)
    {
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    }
    else
    {
        this->window =
            new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
    }

    // TODO: TESTING! NEEDS TO BE REFACTORED BEFORE PLATFORM RELEASE
    this->window->setPosition(
        sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 1620, sf::VideoMode::getDesktopMode().height / 2 - 400));
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
    // Load keys from config file
    std::ifstream ifs("config/supported_keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();

    // TODO: DEBUG REMOVE LATER
    for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << std::endl;
    }
}

void Game::initStates() { this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states)); }

// Constructors / Destructors

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    // Delete the states.
    while (!this->states.empty())
    {
        delete this->states.top(); // Removes the data the pointer is holding
        this->states.pop();        // Removes the actual pointer
    }
}

// Functions

void Game::endApplication() { std::cout << "Ending Application!" << std::endl; }

void Game::updateDt()
{
    // Updates the DeltaTime with the time it takes to update & render one frame
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    // Update state
    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    // Application end
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();

    // RENDER ITEMS
    // Render state
    if (!this->states.empty())
    {
        this->states.top()->render();
    }

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
