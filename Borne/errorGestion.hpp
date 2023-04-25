/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** errorGestion
*/

#ifndef ERRORGESTION_HPP_
#define ERRORGESTION_HPP_
#include <string>
class LoaderExeption : public std::exception
{
    public:
        LoaderExeption(std::string msg, std::string errorHandle) {_msg = msg; nameLib = errorHandle;}
        const char *what() const noexcept override {return _msg.c_str();}
        const char *why() const noexcept {return nameLib.c_str();}
    private:
        std::string _msg; //what
        std::string nameLib; //why?
};

class argError : public std::exception
{
    public:
        argError(std::string msg) {_msg = msg;}
        const char *what() const noexcept override {return _msg.c_str();}
    private:
        std::string _msg; //what
};

class elementCreationError : public std::exception
{
    public:
        elementCreationError(std::string msg) {_msg = msg;}
        const char *what() const noexcept override {return _msg.c_str();}
    private:
        std::string _msg; //what
};

#endif /* !ERRORGESTION_HPP_ */
