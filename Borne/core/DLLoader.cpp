/*
** EPITECH PROJECT, 2023
** bsArcade
** File description:
** DLLoader
*/

#include "DLLoader.hpp"

template <typename T>
inline T *DLLoader<T>::getInstance(std::string nameLib, std::string nameFunc)
{
    void *handle = dlopen(nameLib.c_str(), RTLD_NOW);
    T *(*entryPoint)(void);
    T *lib = nullptr;

    if (!handle) {
        throw LoaderExeption(dlerror(), nameLib);
        return nullptr;
    }
    *(void**)(&entryPoint) = dlsym(handle, nameFunc.c_str());
    if (!entryPoint) {
        return nullptr;
    }
    _lib.push_back(handle);
    lib = entryPoint();
    return lib;
}

template <typename T>
void DLLoader<T>::closeLib()
{
    while (_lib.size() > 0) {
        if (_lib.back())
            dlclose(_lib.back());
        _lib.pop_back();
    }
}

template class DLLoader<IGameModule>;
template class DLLoader<IDsiplayModule>;