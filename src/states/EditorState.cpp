#include "EditorState.hpp"

// Initialization functions
void EditorState::initVariables() {}

void EditorState::initBackground() {}

void EditorState::initFonts()
{
    if (!this->font.loadFromFile("assets/fonts/Lato-Regular.ttf"))
    {
        throw("ERROR::EDITOR_STATE::Could not load font");
    }
}

void EditorState::initKeybinds()
{
    // Load keys from config file
    std::ifstream ifs("config/editorstate_keybinds.ini");

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

void EditorState::initButtons() {}

EditorState::EditorState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                         std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

EditorState::~EditorState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

// Functions

void EditorState::updateInput(const float &deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
    {
        this->endState();
    }
}

/**
 * @brief Updates all the buttons in the state and handles all their functions
 *
 */
void EditorState::updateButtons()
{
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
}

void EditorState::update(const float &deltaTime)
{
    // Input
    this->updateMousePositions();
    this->updateInput(deltaTime);

    // Buttons
    this->updateButtons();
}

void EditorState::renderButtons(sf::RenderTarget &target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void EditorState::render(sf::RenderTarget *target)
{
    if (!target)
    {
        target = this->window;
    }

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
