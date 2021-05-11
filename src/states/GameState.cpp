#include "GameState.hpp"

// Initiliazation Functions
void GameState::initKeybinds()
{
    // Load keys from config file
    std::ifstream ifs("config/gamestate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void GameState::initFonts()
{
    if (!this->font.loadFromFile("assets/fonts/Lato-Regular.ttf"))
    {
        throw("ERROR::MAIN_MENU_STATE::Could not load font");
    }
}

void GameState::intiTextures()
{
    if (!this->textures["PLAYER_SHEET"].loadFromFile("assets/images/sprites/player/PLAYER_SHEET.png"))
    {
        throw("ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE");
    }
}

void GameState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->window, this->font);
    this->pmenu->addButton("EXIT_STATE", 600.f, "Quit");
}

void GameState::initPlayers() { this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]); }

// Constructurs / Destructors
GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    this->initKeybinds();
    this->initFonts();
    this->intiTextures();
    this->initPauseMenu();
    this->initPlayers();
}

GameState::~GameState()
{
    delete this->player;
    delete this->pmenu;
}

void GameState::updateInput(const float &deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
    {
        if (!this->paused)
        {
            this->pauseState();
        }
        else
        {
            this->unpauseState();
        }
    }
}

// Functions

void GameState::updatePlayerInput(const float &deltaTime)
{
    // Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
    {
        this->player->move(-1.f, 0.f, deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    {
        this->player->move(1.f, 0.f, deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
    {
        this->player->move(0.f, -1.f, deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
    {
        this->player->move(0.f, 1.f, deltaTime);
    }
}

void GameState::updatePauseMenuButtons()
{
    if (this->pmenu->isButtonPressed("EXIT_STATE"))
    {
        this->endState();
    }
}

void GameState::update(const float &deltaTime)
{
    this->updateMousePositions();
    this->updateKeytime(deltaTime);
    this->updateInput(deltaTime);

    if (!this->paused) // Unpaused update
    {
        this->updatePlayerInput(deltaTime);
        this->player->update(deltaTime);
    }
    else // Paused update
    {
        this->pmenu->update(this->mousePosView);
        this->updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget *target)
{
    if (!target)
    {
        target = this->window;
    }

    this->player->render(*target);

    if (this->paused) // Pause menu render
    {
        this->pmenu->render(*target);
    }
}
