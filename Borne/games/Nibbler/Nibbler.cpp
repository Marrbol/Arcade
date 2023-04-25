/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** Nibbler
*/

#include "Nibbler.hpp"
#include <iostream>
// void printMap(std::vector<std::string> map);
Nibbler::Nibbler()
{
}

void Nibbler::start()
{
    std::srand(time(NULL));
    _nibbler.push_back(std::pair<char, std::pair<size_t, size_t>> {HEAD, std::pair<size_t, size_t> {12, 17}});
    _nibbler.push_back(std::pair<char, std::pair<size_t, size_t>> {BODY, std::pair<size_t, size_t> {11, 17}});
    _nibbler.push_back(std::pair<char, std::pair<size_t, size_t>> {BODY, std::pair<size_t, size_t> {10, 17}});
    _nibbler.push_back(std::pair<char, std::pair<size_t, size_t>> {BODY, std::pair<size_t, size_t> {9, 17}});
    _newHead  = _nibbler[0].second;
    _input = RIGHT;
    _isAlive = true;
    _nbApple = NBAPPLE;
    createMap();
}

Nibbler::~Nibbler()
{
}

void Nibbler::stop()
{
    _score = 0;
    size_t maxMap = _map.size();
    for (size_t i = 0; i < maxMap; i++)
        _map.pop_back();
    size_t maxNibbler = _nibbler.size();
    for (size_t i = 0; i < maxNibbler; i++)
        _nibbler.pop_back();
}

std::vector<std::string> Nibbler::updateMap()
{
    if (!_isAlive || _map.size() == 0)
        return _map;
    if (_nbApple == 0) {
        for (size_t i = 0; i <= SIZEMAP; i++)
            if (!_map.back().empty())
                _map.pop_back();
        _map.push_back("gg, Your score is : " + std::to_string(_score));
        _isAlive = false;
        return _map;
    }
    _newHead = _nibbler[0].second;

    if (_input == RIGHT)
        _newHead.first++;
    if (_input == LEFT)
        _newHead.first--;
    if (_input == UP)
        _newHead.second--;
    if (_input == DOWN)
        _newHead.second++;

    //the big switch for the virage
    if (_map[_newHead.second].at(_newHead.first) == WALL) {
        switch (_input) {
        case RIGHT: case LEFT:
            if (_nibbler[0].second.second > 0 && (_map[_nibbler[0].second.second - 1].at(_nibbler[0].second.first) != WALL))  {
                if (_nibbler[0].second.second < _map.size() && (_map[_nibbler[0].second.second + 1].at(_nibbler[0].second.first) != WALL))
                    return _map;
                _input = UP;
            }
            if (_nibbler[0].second.second < _map.size() && (_map[_nibbler[0].second.second + 1].at(_nibbler[0].second.first) != WALL)) {
                if (_nibbler[0].second.second > 0 && (_map[_nibbler[0].second.second - 1].at(_nibbler[0].second.first) != WALL))
                    return _map;
                _input = DOWN;
            }
            break;
        case UP: case DOWN:
            if (_nibbler[0].second.first > 0 && (_map[_nibbler[0].second.second].at(_nibbler[0].second.first - 1) != WALL)) {
                if (_nibbler[0].second.first < _map.size() && (_map[_nibbler[0].second.second].at(_nibbler[0].second.first + 1) != WALL))
                    return _map;
                _input = LEFT;
            }
            if (_nibbler[0].second.second < _map.size() && (_map[_nibbler[0].second.second].at(_nibbler[0].second.first + 1) != WALL)) {
                if (_nibbler[0].second.second > 0 && (_map[_nibbler[0].second.second].at(_nibbler[0].second.first - 1) != WALL))
                    return _map;
                _input = RIGHT;
            }
            break;
        default:
            break;
        }
    }

    _oldQueue = _nibbler.back().second;
    _newHead  = _nibbler[0].second;
    if (_input == RIGHT)
        _newHead.first++;
    if (_input == LEFT)
        _newHead.first--;
    if (_input == UP)
        _newHead.second--;
    if (_input == DOWN)
        _newHead.second++;
    // move nibbler's body
    _map.at(_nibbler.back().second.second)[_nibbler.back().second.first] = EMPTY;
    for (size_t i = _nibbler.size() - 1; i > 0; i--)
        _nibbler.at(i).second = _nibbler.at(i - 1).second;

    //chek a wall and the body
    if (_map[_newHead.second].at(_newHead.first) == BODY) {
        for (size_t i = 0; i <= SIZEMAP; i++)
            _map.pop_back();
        _map.push_back("Your score is : " + std::to_string(_score));
        _isAlive = false;
        return _map;
    }

    //update the head position
    _nibbler[0].second = _newHead ;

    //check if he eats an apple
    if (_map[_newHead.second].at(_newHead.first) == APPLE) {
        _nibbler.push_back(std::pair<char, std::pair<size_t, size_t>> {BODY, _oldQueue});
        _score += 10;
        _nbApple--;
    }

    //print the nibbler
    for (auto items: _nibbler)
        _map.at(items.second.second)[items.second.first] = items.first;

    return _map;
}

void Nibbler::createMap()
{
    for (size_t i = 0; i <= SIZEMAP; i++) {
        _map.push_back("");
        for (size_t j = 0; j <= SIZEMAP; j++)
            _map.at(i).push_back(EMPTY);
    }
    _map[0] = "###################";
    _map[1] = "#  @   @   @   @  #";
    _map[2] = "# ### # ### # ### #";
    _map[3] = "#@# # #     # # #@#";
    _map[4] = "# ### # # # # ### #";
    _map[5] = "#     #@# #@#     #";
    _map[6] = "# ##### # # ##### #";
    _map[7] = "#@# @         @ #@#";
    _map[8] = "# # ##       ## # #";
    _map[9] = "#   @         @   #";
   _map[10] = "# ####  ###  #### #";
   _map[11] = "#  @    # #    @  #";
   _map[12] = "# ### # ### # ### #";
   _map[13] = "# # # #  @  # # # #";
   _map[14] = "#@###@#@###@#@###@#";
   _map[15] = "#     # # # #     #";
   _map[16] = "#@##### ### #####@#";
   _map[17] = "#                 #";
   _map[18] = "###################";
}

void Nibbler::manageInput(size_t input)
{
    if (input == RIGHT && _input == LEFT)
        return;
    if (input == LEFT && _input == RIGHT)
        return;
    if (input == UP && _input == DOWN)
        return;
    if (input == DOWN && _input == UP)
        return;
    if (input == RIGHT && _map[_nibbler[0].second.second].at(_nibbler[0].second.first + 1) == WALL)
        return;
    if (input == LEFT && _map[_nibbler[0].second.second].at(_nibbler[0].second.first - 1) == WALL)
        return;
    if (input == UP && _map[_nibbler[0].second.second - 1].at(_nibbler[0].second.first) == WALL)
        return;
    if (input == DOWN && _map[_nibbler[0].second.second + 1].at(_nibbler[0].second.first) == WALL)
        return;
    _input = input;
}

//snif rip le print map et le main

extern "C" IGameModule *entryGame()
{
    return new Nibbler();
}
