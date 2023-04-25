/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** Snake
*/

#include "Snake.hpp"
#include <iostream>
// void printMap(std::vector<std::string> map);
Snake::Snake()
{
}

void Snake::start()
{
    std::srand(time(NULL));
    _snake.push_back(std::pair<char, std::pair<size_t, size_t>> {HEAD, std::pair<size_t, size_t> {12, 12}});
    _snake.push_back(std::pair<char, std::pair<size_t, size_t>> {BODY, std::pair<size_t, size_t> {11, 12}});
    _snake.push_back(std::pair<char, std::pair<size_t, size_t>> {BODY, std::pair<size_t, size_t> {10, 12}});
    _snake.push_back(std::pair<char, std::pair<size_t, size_t>> {BODY, std::pair<size_t, size_t> {9, 12}});
    _apple = std::pair <char, std::pair <size_t, size_t>> {APPLE, std::pair<size_t, size_t>{14, 12}};
    _newHead = _snake[0].second;
    _input = RIGHT;
    _isAlive = true;
    _score = 0;
    createMap();
}

Snake::~Snake()
{
}

void Snake::stop()
{
    _score = 0;
    size_t maxMap = _map.size();
    for (size_t i = 0; i < maxMap; i++)
        _map.pop_back();
    size_t maxSnake = _snake.size();
    for (size_t i = 0; i < maxSnake; i++)
        _snake.pop_back();
}

std::vector<std::string> Snake::updateMap()
{
    if (!_isAlive)
        return _map;

    bool verif_apple = false;
    for (auto str : _map) {
        for (auto c : str) {
            if (c == APPLE) {
                verif_apple = true;
                break;
            }
        }
    }
    if (!verif_apple) {
        while (_map[_apple.second.second].at(_apple.second.first) != EMPTY)
            _apple.second = std::pair<size_t, size_t> {std::rand() % (SIZEMAP - 1), rand() % (SIZEMAP - 1)};
        _map[_apple.second.second].at(_apple.second.first) = APPLE;
    }
    if (_snake.size() > 0)
        _oldQueue = _snake.back().second;

    // move snake's body
    _map.at(_snake.back().second.second)[_snake.back().second.first] = EMPTY;
    for (size_t i = _snake.size() - 1; i > 0; i--)
        _snake.at(i).second = _snake.at(i - 1).second;

    //move the head
    if (_input == RIGHT)
        _newHead.first++;
    if (_input == LEFT)
        _newHead.first--;
    if (_input == UP)
        _newHead.second--;
    if (_input == DOWN)
        _newHead.second++;

    //chek a wall and the body
   if (_map[_newHead.second].at(_newHead.first) == WALL || _map[_newHead.second].at(_newHead.first) == BODY) {
        for (size_t i = 0; i <= SIZEMAP; i++)
            _map.pop_back();
        _map.push_back("Your score is : " + std::to_string(_score));
        _isAlive = false;
        return _map;
    }

    //update the head position
    _snake[0].second = _newHead;

    //check if he eats an apple
    if (_map[_newHead.second].at(_newHead.first) == APPLE) {
        _snake.push_back(std::pair<char, std::pair<size_t, size_t>> {BODY, _oldQueue});
        _score += 10;
        while (_map[_apple.second.second].at(_apple.second.first) != EMPTY)
            _apple.second = std::pair<size_t, size_t> {std::rand() % (SIZEMAP - 1), rand() % (SIZEMAP - 1)};
        _map[_apple.second.second].at(_apple.second.first) = APPLE;
    }

    //print the snake
    for (auto items: _snake)
        _map.at(items.second.second)[items.second.first] = items.first;

    return _map;
}

void Snake::createMap()
{
    for (size_t i = 0; i <= SIZEMAP; i++) {
        _map.push_back("");
        for (size_t j = 0; j <= SIZEMAP; j++)
            _map.at(i).push_back(EMPTY);
    }
    for (size_t i = 0; i <= SIZEMAP; i++) {
        _map.at(0)[i] = WALL;
        _map.at(SIZEMAP)[i] = WALL;
        _map.at(i)[0] = WALL;
        _map.at(i)[SIZEMAP] = WALL;
    }

    do
        _apple.second = std::pair<size_t, size_t> {std::rand() % (SIZEMAP - 1), rand() % (SIZEMAP - 1)};
    while (_map[_apple.second.second].at(_apple.second.first) != EMPTY);

    _map[_apple.second.second].at(_apple.second.first) = APPLE;
}

void Snake::manageInput(size_t input)
{
    if (input == RIGHT && _input == LEFT)
        return;
    if (input == LEFT && _input == RIGHT)
        return;
    if (input == UP && _input == DOWN)
        return;
    if (input == DOWN && _input == UP)
        return;
    _input = input;
}

extern "C" IGameModule *entryGame()
{
    return new Snake();
}
