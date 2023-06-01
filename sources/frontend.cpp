/**
 * @ Author: Samael
 * @ Create Time: 2023-05-30 14:30:43
 * @ Modified by: Samael
 * @ Modified time: 2023-06-01 06:39:57
 * @ Description:
 */

#include "frontend.hpp"

Frontend::Frontend() {
    // TODO
    std::cout << "Frontend created" << std::endl;
    _window = new sf::RenderWindow(sf::VideoMode(800, 600), "Contact Book");
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
        createPrintBdd();
        while(_window->pollEvent(*_event)) {
            if (_event->type == sf::Event::Closed)
                _window->close();
            else if (_event->type == sf::Event::MouseButtonPressed) {
                if (_event->mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
                    std::string clickedText = getClickedText(mousePosition);
                    std::cout << clickedText << std::endl;
                }
            }
        }
        printBdd();
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
        text->setCharacterSize(24);
        text->setFillColor(sf::Color::White);
        text->setPosition(10, 10 + offset);
        offset += 30;
        _text.push_back(std::make_pair(font, text));
    }
}

void Frontend::printBdd() {
    for (auto &i : _text) {
        i.second->setFont(*i.first);
        _window->draw(*i.second);
    }
}