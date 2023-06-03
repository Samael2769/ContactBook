/**
 * @ Author: Samael
 * @ Create Time: 2023-05-30 14:30:43
 * @ Modified by: Samael
 * @ Modified time: 2023-06-03 03:09:29
 * @ Description:
 */

#include "frontend.hpp"

Frontend::Frontend() {
    // TODO
    std::cout << "Frontend created" << std::endl;
    _window = new sf::RenderWindow(sf::VideoMode(1900, 1000), "Contact Book");
    _page = MAIN;
}

Frontend::~Frontend() {
    // TODO
}

void Frontend::run() {
    std::cout << "Start to run" << std::endl;
    _bdd = _backend->getAll();
    _event = new sf::Event();
    while(_window->isOpen()) {
        _window->clear(sf::Color::Black);
        _bdd = _backend->getAll();
        if (_page == MAIN)
            createPrintBdd();
        if (_page == SPECIAL)
            returnButton();
        while(_window->pollEvent(*_event)) {
            if (_event->type == sf::Event::Closed)
                _window->close();
            else if (_event->type == sf::Event::MouseButtonPressed) {
                if (_event->mouseButton.button == sf::Mouse::Left) {
                    if (_page == MAIN) {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
                        std::string clickedText = getClickedText(mousePosition);
                        if (clickedText != "") {
                            _page = SPECIAL;
                            _actualUser = clickedText;
                        }
                        std::cout << clickedText << std::endl;
                    }
                    if (_page == SPECIAL) {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
                        //position 10 10 caractere size 45 text "return" if mouse position is in this area return to main page
                        if (mousePosition.x >= 10 && mousePosition.x <= 10 + 45 * 6 && mousePosition.y >= 10 && mousePosition.y <= 10 + 45) {
                            _page = MAIN;
                        }
                    }
                }
            }
        }
        if (_page == MAIN)
            printBdd();
        if (_page == SPECIAL)
            printUser(_actualUser);
        _window->display();
    }
}

std::string Frontend::getClickedText(sf::Vector2i mousePosition) {
    for (const auto& pair : _text) {
        sf::Text* text = pair.second;
        if (text->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            return text->getString();
        }
    }
    return ""; // Return an empty string if no text was clicked
}


void Frontend::setBackend(Backend *backend) {
    _backend = backend;
}

void Frontend::createPrintBdd() {
    sf::Font * font = new sf::Font();
    if (!font->loadFromFile("../assets/fonts/text_font.ttf"))
        std::cout << "Error loading font" << std::endl;
    int offset = 50;
    for (auto &i : _bdd) {
        sf::Text *text = new sf::Text();
        text->setFont(*font);
        text->setString(i.first);
        text->setCharacterSize(45);
        text->setFillColor(sf::Color::White);
        text->setPosition(10, 10 + offset);
        offset += 50;
        _text.push_back(std::make_pair(font, text));
    }
}

void Frontend::printBdd() {
    for (auto &i : _text) {
        i.second->setFont(*i.first);
        _window->draw(*i.second);
    }
}

void Frontend::returnButton() {
    sf::Text *text = new sf::Text();
    sf::Font *font = new sf::Font();
    if (!font->loadFromFile("../assets/fonts/text_font.ttf"))
        std::cout << "Error loading font" << std::endl;
    text->setFont(*font);
    text->setString("Return");
    text->setCharacterSize(45);
    text->setFillColor(sf::Color::White);
    text->setPosition(10, 10);
    _window->draw(*text);
}

void Frontend::printUser(std::string user) {
    std::vector<std::vector<std::string>> userInfos = _backend->get(user);
    std::vector<std::string> userData = userInfos[0];
    sf::Font *font = new sf::Font();
    if (!font->loadFromFile("../assets/fonts/text_font.ttf"))
        std::cout << "Error loading font" << std::endl;
    sf::Text *text = new sf::Text();
    text->setFont(*font);
    text->setString(user);
    text->setCharacterSize(45);
    text->setFillColor(sf::Color::White);
    text->setPosition(50, 100);
    _window->draw(*text);
    int index = 0;
    int imgIndex = 0;
    for (auto &i : userData) {
        if (strncmp(i.c_str(), "img", 3) == 0) {
            sf::Texture *texture = new sf::Texture();
            std::string path = i.substr(4);
            if (!texture->loadFromFile(path))
                std::cout << "Error loading texture - " << path << std::endl;
            sf::Sprite *sprite = new sf::Sprite();
            sprite->setTexture(*texture);
            sprite->setPosition(50 + imgIndex * 350, 500);
            sf::Vector2f newSize(300.f, 350.f);
            sprite->setScale(newSize.x / sprite->getLocalBounds().width, newSize.y / sprite->getLocalBounds().height);
            _window->draw(*sprite);
            imgIndex++;
            continue;
        }
        sf::Text *text = new sf::Text();
        text->setFont(*font);
        text->setString(i);
        text->setCharacterSize(45);
        text->setFillColor(sf::Color::White);
        text->setPosition(50, 150 + index * 50);
        _window->draw(*text);
        index++;
    }
}