/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** IDsiplayModule
*/

#ifndef IDSIPLAYMODULE_HPP_
#define IDSIPLAYMODULE_HPP_
#include <iostream>
#include <chrono>
#include "../games/IGameModule.hpp"
#include "../define.hpp"
#include <list>

class IDsiplayModule {
    public:
        virtual ~IDsiplayModule()= default;
        virtual std::string getUserName() = 0;
        virtual void setUserName(std::string userName) = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void drawMap(std::vector<std::string> map) = 0;
        virtual size_t getInput() = 0;
        virtual std::pair<bool, std::string> menu(std::vector<std::string> display, std::vector<std::string> game) = 0;
        virtual void setScore(std::list<_score_t>) = 0;
};

#endif /* !IDSIPLAYMODULE_HPP_ */
