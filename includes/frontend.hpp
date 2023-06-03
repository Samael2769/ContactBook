/**
 * @ Author: Samael
 * @ Create Time: 2023-05-30 14:28:40
 * @ Modified by: Samael
 * @ Modified time: 2023-06-03 02:17:18
 * @ Description:
 */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>


#include "backend.hpp"

typedef enum pages_e{
    MAIN,
    SPECIAL
} pages_e;

class Frontend {
public:
    Frontend();
    ~Frontend();
    void setBackend(Backend *backend);
    void createPrintBdd();
    void printBdd();
    std::string getClickedText(sf::Vector2i mousePosition);
    void run();
    void printUser(std::string user);
    void returnButton();
protected:
private:
    Backend *_backend;
    sf::RenderWindow * _window;
    sf::Event * _event;
    std::map<std::string, std::vector<std::string>> _bdd;
    std::vector<std::pair<sf::Font *, sf::Text *>> _text;
    pages_e _page;
    std::string _actualUser;
};