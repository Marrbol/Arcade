/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../games/IGameModule.hpp"
#include "../display/IDsiplayModule.hpp"
#include "../define.hpp"
#include <dlfcn.h>
#include <chrono>
#include "DLLoader.hpp"
#include <map>
#include "../errorGestion.hpp"
#include <fstream>
#include <list>

class Core {
    public:
        Core();
        ~Core();
        void update();
        void call_menu(std::string name);
        int manageInput();
        void saveScore();
        void parseScore();
    private:
        std::vector<std::string> nameGame;
        std::vector<std::string> nameDisplay;
        // std::unique_ptr<IGameModule> display;
        std::vector<void *> _lib;
        std::map<std::string, std::unique_ptr<IGameModule>> game;
        std::map<std::string, std::unique_ptr<IDsiplayModule>> display;
        size_t indexDisplay = 0;
        size_t indexGame = 0;
        std::string actualGame;
        std::string actualDisplay;
        std::vector<std::string> map;
        std::list<size_t> input;
        DLLoader<IGameModule> gameLoader;
        std::string userName  = "";
        DLLoader<IDsiplayModule> displayLoader;
        size_t _score = 0;
        std::ofstream _writeFile;
        std::ifstream _readFile;
        std::list<_score_t> _allScore;
};

#endif /* !CORE_HPP_ */
