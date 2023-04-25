/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** Core
*/

#include "Core.hpp"
#include <filesystem>
#include <type_traits>
#include <fstream>

Core::Core()
{
    std::string path = "./lib/";
    try {
        for (const auto & file : std::filesystem::directory_iterator(path)) {
            auto tmp = gameLoader.getInstance(file.path(), "entryGame");
            if (tmp != nullptr) {
                nameGame.push_back(file.path());
                game[file.path()] = std::unique_ptr<IGameModule>(tmp);
            } else {
                auto tmp = displayLoader.getInstance(file.path(), "entryDisplay");
                if (tmp != nullptr) {
                    nameDisplay.push_back(file.path());
                    display[file.path()] = std::unique_ptr<IDsiplayModule>(tmp);
                } else {
                    std::string msgError = "Error: ";
                    msgError.append(file.path());
                    msgError.append(" is not a valid library");
                    throw LoaderExeption(msgError, file.path());
                }
            }
        }
    } catch (const LoaderExeption &e) {
        throw e;
    }
}
void Core::saveScore()
{
    _score_t score;
    if (actualGame.compare("./lib/arcade_nibbler.so") == 0)
        score.game = "Nibbler";
    if (actualGame.compare("./lib/arcade_snake.so") == 0)
        score.game = "Snake";
    score.name = userName;
    if (userName.size() == 0)
        score.name = "Anonymous";
    score.score = _score;
    if (_allScore.size() > 5)
        _allScore.pop_back();
    _allScore.push_front(score);
}

Core::~Core()
{
    _writeFile.close();
    for (auto &i : nameGame)
        game[i].reset();
    for (auto &i : nameDisplay)
        display[i].reset();
    gameLoader.closeLib();
    displayLoader.closeLib();
}

int Core::manageInput()
{
    size_t newInput = display[actualDisplay]->getInput();

    switch (newInput) {
        case QUIT:
            _score = game[actualGame]->getScore();
            saveScore();
            game[actualGame]->stop();
            display[actualDisplay]->stop();
            input.clear();
            return 1;
        case MENU:
            _score = game[actualGame]->getScore();
            saveScore();
            display[actualDisplay]->setScore(_allScore);
            game[actualGame]->stop();
            display[actualDisplay]->stop();
            newInput = 0;
            input.clear();
            call_menu(actualDisplay);
            return 1;
        case NEXTDISPLAY:
            display[actualDisplay]->stop();
            indexDisplay++;
            if (indexDisplay > nameDisplay.size() - 1)
                indexDisplay = 0;
            actualDisplay = nameDisplay[indexDisplay];
            display[actualDisplay]->start();
            newInput = 0;
            break;
        case NEXTGAME:
            _score = game[actualGame]->getScore();
            saveScore();
            game[actualGame]->stop();
            indexGame++;
            if (indexGame > nameGame.size() - 1)
                indexGame = 0;
            actualGame = nameGame[indexGame];
            game[actualGame]->start();
            newInput = 0;
            break;
        case RESTART:
            game[actualGame]->stop();
            saveScore();
            game[actualGame]->start();
            newInput = 0;
            break;
        default:
            break;
    }
    if (newInput != 0)
        input.push_back(newInput);
    return 0;
}

void Core::update()
{
    clock_t last_time = clock(); // Initialisez la variable last_time avec le temps actuel
    while (true) {
        if (manageInput())
            return;
        clock_t current_time = clock();
        double elapsed_time = double(current_time - last_time) / CLOCKS_PER_SEC;
        while (elapsed_time >= 0.17) {
            if (input.size() > 0) {
                game[actualGame]->manageInput(input.front());
                input.pop_front();
            }
            map = game[actualGame]->updateMap();
            display[actualDisplay]->drawMap(map);
            elapsed_time -= 0.3;
            last_time = current_time;
        }
    }
    display[actualDisplay]->stop();
}

void Core::call_menu(std::string name)
{
    size_t index = 0;
    if (display.find(name) == display.end())
        throw argError("Error: " + name + " is not a valid library");
    actualDisplay = name;
    for (auto &i : nameDisplay) {
        if (i == actualDisplay) {
            indexDisplay = index;
            break;
        }
        index++;
    }
    display[actualDisplay]->start();
    if (userName.size() > 0)
        display[actualDisplay]->setUserName(userName);
    display[actualDisplay]->setScore(_allScore);
    std::pair<bool, std::string> r = display[actualDisplay]->menu(nameDisplay, nameGame);
    if (r.second == "quit") {
        display[actualDisplay]->stop();
        return;
    }
    if (userName.size() == 0) {
        userName = display[actualDisplay]->getUserName();
    }
    if (r.first == true) {
        display[actualDisplay]->stop();
        call_menu(r.second);
    } else {
        actualGame = r.second;
        for (index = 0; index < nameGame.size(); index++) {
            if (!actualGame.compare(nameGame[index])) {
                indexGame = index;
                break;
            }
        }
        game[actualGame]->start();
        update();
        return;
    }
}

void help()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./arcade lib_path" << std::endl;
    std::cout << "mapped key:" << std::endl;
    std::cout << "\tq: quit" << std::endl;
    std::cout << "\tm: menu" << std::endl;
    std::cout << "\t1: next game" << std::endl;
    std::cout << "\t2: next display" << std::endl;
    std::cout << "\tr: restart" << std::endl;
    std::cout << "\tIn menu:" << std::endl;
    std::cout << "\tenter: confirm game" << std::endl;
    std::cout << "\tIn game:" << std::endl;
    std::cout << "\tup: up" << std::endl;
    std::cout << "\tdown: down" << std::endl;
    std::cout << "\tleft: left" << std::endl;
    std::cout << "\tright: right" << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    if (std::string(av[1]) == "-h") {
        help();
        return 0;
    }
    try {
        Core *core = new Core;
        core->call_menu(av[1]);
        delete core;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

template class DLLoader<IGameModule>;
template class DLLoader<IDsiplayModule>;
