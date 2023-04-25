/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** Nibbler
*/

#ifndef Nibbler_HPP_
#define Nibbler_HPP_
#define NBAPPLE 25
#include "../IGameModule.hpp"

class Nibbler : public IGameModule {
    public:
        Nibbler();
        ~Nibbler();
        const std::string getName() const { return "";}
        std::vector<std::string> updateMap(); //a voir après changer plus tard le type
        void manageInput(size_t input);
        void createMap();
        void updateScore(){}
        void start();
        void stop();
        size_t getScore() const {return _score;}
    private:
        size_t _score = 0;
        std::vector <std::pair <char, std::pair <size_t, size_t>>> _nibbler;
        //                        apparance              posX     posY
        std::vector<std::string> _map;
        size_t _input = RIGHT;
        std::pair<size_t, size_t> _oldQueue;
        std::pair<size_t, size_t> _newHead;
        std::pair <char, std::pair <size_t, size_t>> _apple;
        bool _isAlive = true;
        size_t _nbApple = NBAPPLE;
};

#endif /* !Nibbler_HPP_ */
