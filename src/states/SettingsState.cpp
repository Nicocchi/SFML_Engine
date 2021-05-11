#include "SettingsState.hpp"

SettingsState::SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                             std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

SettingsState::~SettingsState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

// Initialization functions
void SettingsState::initVariables() {}

void SettingsState::initBackground()
{
    this->background.setSize(
        sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

    if (!this->backgroundTexture.loadFromFile("assets/images/backgrounds/bg1.png"))
    {
        throw("ERROR::SETTINGS_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
    }
    this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
    if (!this->font.loadFromFile("assets/fonts/Lato-Regular.ttf"))
    {
        throw("ERROR::SETTINGS_STATE::Could not load font");
    }
}

void SettingsState::initKeybinds()
{
    // Load keys from config file
    std::ifstream ifs("config/mainmenustate_keybinds.ini");

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

void SettingsState::initButtons()
{
    this->buttons["EXIT_STATE"] = new gui::Button(
        300.f, 680.f, 250.f, 50.f, &this->font, "Exit", 50, sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250),
        sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

// Accessors

// Functions

void SettingsState::updateInput(const float &deltaTime) {}

/**
 * @brief Updates all the buttons in the state and handles all their functions
 *
 */
void SettingsState::updateButtons()
{
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    if (this->buttons["EXIT_STATE"]->isPressed())
    {
        this->endState();
    }
}

void SettingsState::update(const float &deltaTime)
{
    // Input
    this->updateMousePositions();
    this->updateInput(deltaTime);

    // Buttons
    this->updateButtons();
}

void SettingsState::renderButtons(sf::RenderTarget &target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget *target)
{
    if (!target)
    {
        target = this->window;
    }

    target->draw(this->background);

    // Buttons
    this->renderButtons(*target);

    // TODO: DEBUG REMOVE LATER
    // sf::Text mouseText;
    // mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    // mouseText.setFont(this->font);
    // mouseText.setCharacterSize(12);
    // std::stringstream ss;
    // ss << this->mousePosView.x << " " << this->mousePosView.y;
    // mouseText.setString(ss.str());
    // target->draw(mouseText);
}
