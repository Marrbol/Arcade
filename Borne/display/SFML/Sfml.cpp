/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** Sfml
*/

#include "Sfml.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Sfml::Sfml()
{
}

Sfml::~Sfml()
{
}

void Sfml::start()
{
    _window = new sf::RenderWindow();
    _window->create(sf::VideoMode(SIZEWINX, SIZEWINY), "Arcade");
    _window->setFramerateLimit(60);
    _font.loadFromFile("./Borne/assets/Font.ttf");
}

void Sfml::drawMap(std::vector<std::string> map)
{
    _window->clear(sf::Color::Black);

    int y = ((SIZEWINY / 2) - (SQUARESIZE * (map.size() / 2)));
    int x = ((SIZEWINX /2) - (SQUARESIZE * (map[0].size() / 2)));

    if (map[0].at(0) != WALL) {
        for (auto str: map) {
            sf::Text display_text = sf::Text(str.c_str(), _font, 32);
            display_text.setFillColor(sf::Color(GREY));
            display_text.setPosition(x, y);
            _window->draw(display_text);
            y += SQUARESIZE;
        }
    } else {
        sf::RectangleShape rect(sf::Vector2f(SQUARESIZE, SQUARESIZE));
        for (auto line : map) {
            x = ((SIZEWINX /2) - (SQUARESIZE * (map[0].size() / 2)));
            for (auto c : line) {
                switch (c) {
                    case WALL:
                        rect.setFillColor(sf::Color::Red);
                        break;
                    case HEAD:
                        rect.setFillColor(sf::Color::Magenta);
                        break;
                    case BODY:
                        rect.setFillColor(sf::Color::Blue);
                        break;
                    case APPLE:
                        rect.setFillColor(sf::Color::Green);
                        break;
                    default:
                        rect.setFillColor(sf::Color::Black);
                }
                rect.setPosition(sf::Vector2f(x, y));
                _window->draw(rect);
                x += SQUARESIZE;
            }
            y += SQUARESIZE;
        }
    }
    _window->display();
}

size_t Sfml::getInput()
{
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            return QUIT;
        if (_event.type == sf::Event::KeyPressed) {
            switch(_event.key.code) {
                case sf::Keyboard::Num1:
                case sf::Keyboard::Numpad1:
                    return NEXTGAME;
                case sf::Keyboard::Num2:
                case sf::Keyboard::Numpad2:
                    return NEXTDISPLAY;
                case sf::Keyboard::Q:
                case sf::Keyboard::Return:
                    return QUIT;
                case sf::Keyboard::Left:
                    return LEFT;
                case sf::Keyboard::Right:
                    return RIGHT;
                case sf::Keyboard::Up:
                    return UP;
                case sf::Keyboard::Down:
                    return DOWN;
                case sf::Keyboard::R:
                    return RESTART;
                case sf::Keyboard::M:
                    return MENU;
                default:
                    break;
            }
        }
    }
    return 0;
}

void Sfml::stop()
{
    _window->close();
    delete _window;
    _window = nullptr;
}

void Sfml::drawName()
{
    sf::Text nameHeaderText = sf::Text("Name : ", _font, 32);
    nameHeaderText.setFillColor(sf::Color(175, 175, 175, 175));
    nameHeaderText.setPosition(16, 480);
    _window->draw(nameHeaderText);
    if (_userName.size() > 0) {
        sf::Text nameText = sf::Text(_userName, _font, 32);
        nameText.setFillColor(sf::Color(255, 255, 255, 255));
        nameText.setPosition(200, 480);
        _window->draw(nameText);
    }
}

std::string Sfml::getUserName()
{
    return _userName;
}

int Sfml::readUserName()
{
    if (_userName.size() > 0)
        return 0;
    while (1) {
        while (_window->pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                return 1;
            if (_event.type == sf::Event::KeyPressed) {
                if (_event.key.code == sf::Keyboard::Return) {
                    _event.key.code = sf::Keyboard::BackSpace;
                    return 0;
                }
                // if (_event.key.code == sf::Keyboard::BackSpace)
                //     _userName.pop_back();
                if (_event.key.code >= sf::Keyboard::A && _event.key.code <= sf::Keyboard::Z)
                    _userName += _event.key.code + 97;
            }
        }
        drawName();
        _window->display();
    }
    return 0;
}

void Sfml::drawScore(std::list<_score_t> scores)
{
    sf::Text scoreHeaderText = sf::Text("Score : ", _font, 32);
    scoreHeaderText.setFillColor(sf::Color(175, 175, 175, 175));
    scoreHeaderText.setPosition(16, 650);
    _window->draw(scoreHeaderText);
    int y = 700;
    while (!scores.empty()) {
        sf::Text scoreText = sf::Text(scores.front().game + " : " + scores.front().name + " : " + std::to_string(scores.front().score), _font, 25);
        scoreText.setFillColor(sf::Color(255, 255, 255, 255));
        scoreText.setPosition(20, y);
        _window->draw(scoreText);
        y += 50;
        scores.pop_front();
    }
}

std::pair<bool, std::string> Sfml::menu(std::vector<std::string> display, std::vector<std::string> game)
{
    unsigned int selected_game = 0;
    unsigned int selected_display = 0;

    for (; display[selected_display] != "./lib/arcade_sfml.so"; selected_display++);

    sf::Text display_text = sf::Text("Display", _font, 32);
    display_text.setFillColor(sf::Color(175, 175, 175, 175));
    display_text.setPosition(16, 250);

    sf::Text game_text = sf::Text("Game", _font, 32);
    game_text.setFillColor(sf::Color(175, 175, 175, 175));
    game_text.setPosition(16, 16);

    std::vector<sf::Text> display_text_vector;
    for (size_t i = 0; i < display.size(); i++) {
        sf::Text text = sf::Text(display[i], _font, 25);
        text.setFillColor(sf::Color::White);
        text.setPosition(16, 270 + (i + 1) * 32);
        display_text_vector.push_back(text);
    }

    std::vector<sf::Text> game_text_vector;
    for (size_t i = 0; i < game.size(); i++) {
        sf::Text text = sf::Text(game[i], _font, 25);
        text.setFillColor(sf::Color::White);
        text.setPosition(16, 36 + (i + 1) * 32);
        game_text_vector.push_back(text);
    }
    drawScore(_scores);
    while (_window->isOpen()) {
        while (_window->pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                return {false, "quit"};
            if (_event.type == sf::Event::KeyPressed) {
                if (_event.key.code == sf::Keyboard::Num1 || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
                    selected_game++;
                if (_event.key.code == sf::Keyboard::Num2 || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
                    return {true, display[selected_display % display.size() + 1]};
                if (_event.key.code == sf::Keyboard::Q)
                    return {false, "quit"};
                if (_event.key.code == sf::Keyboard::Return)
                    return {false, game[selected_game % game.size()]};
                if (_event.key.code == sf::Keyboard::N)
                    if (readUserName())
                        return {false, "quit"};
            }
        }
        _window->clear();
        _window->draw(display_text);
        for (size_t i = 0; i < display_text_vector.size(); i++) {
            if (i == selected_display % display_text_vector.size()) {
                display_text_vector[i].setFillColor(sf::Color(105, 0, 255, 255));
                display_text_vector[i].setString(display[i] + " +");
            } else {
                display_text_vector[i].setFillColor(sf::Color::White);
                display_text_vector[i].setString(display[i]);
            }
            _window->draw(display_text_vector[i]);
        }
        _window->draw(game_text);
        for (size_t i = 0; i < game_text_vector.size(); i++) {
            if (i == selected_game % game_text_vector.size()) {
                game_text_vector[i].setFillColor(sf::Color(105, 0, 255, 255));
                game_text_vector[i].setString(game[i] + " +");
            } else {
                game_text_vector[i].setFillColor(sf::Color::White);
                game_text_vector[i].setString(game[i]);
            }
            _window->draw(game_text_vector[i]);
        }
        drawName();
        drawScore(_scores);
        _window->display();
    }
    return {false, "quit"};
}

extern "C" IDsiplayModule *entryDisplay()
{
    return new Sfml();
}
