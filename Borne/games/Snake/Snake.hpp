/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** Snake
*/

#ifndef Snake_HPP_
#define Snake_HPP_
#include "../IGameModule.hpp"

class Snake : public IGameModule {
    public:
        Snake();
        ~Snake();
        const std::string getName() const {return "snake";}
        std::vector<std::string> updateMap(); //a voir après changer plus tard le type
        void manageInput(size_t input);
        void createMap();
        void updateScore(){}
        void start();
        void stop();
        size_t getScore() const {return _score;}
    private:
        size_t _score;
        std::vector <std::pair <char, std::pair <size_t, size_t>>> _snake;
        //                        apparance              posX     posY
        std::vector<std::string> _map;
        size_t _input = RIGHT;
        std::pair<size_t, size_t> _oldQueue;
        std::pair<size_t, size_t> _newHead;
        std::pair <char, std::pair <size_t, size_t>> _apple;
        bool _isAlive = true;
};

#endif /* !Snake_HPP_ */
