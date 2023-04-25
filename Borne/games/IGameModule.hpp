/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_
#include <iostream>
#include <vector>
#include "../define.hpp"

class IGameModule {
    public:
        virtual ~IGameModule() = default;
        virtual const std::string getName() const = 0;
        virtual size_t getScore() const = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual std::vector<std::string> updateMap() = 0;
        virtual void manageInput(size_t input) = 0;
    private:
};

#endif /* !IGAMEMODULE_HPP_ */
