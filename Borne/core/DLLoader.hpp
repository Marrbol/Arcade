/*
** EPITECH PROJECT, 2023
** bsArcade
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_
#include <string>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "../games/IGameModule.hpp"
#include "../display/IDsiplayModule.hpp"
#include <set>
#include "../errorGestion.hpp"

template <typename T>
class DLLoader {
    public:
        DLLoader() {}
        ~DLLoader() = default;
        T *getInstance (std::string name_lib, std::string name_entry);
        void closeLib();
    private:
        std::vector<void *> _lib;
};


#endif
