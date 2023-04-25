/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <istream>
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <istream>
#include <string>
#include <cstring>
#include <ncurses.h>

#include "../IDsiplayModule.hpp"

class Ncurses : public IDsiplayModule {
    public:
        Ncurses();
        ~Ncurses();
        const std::string getName() const { return "Ncurses";}
        void drawMap(std::vector<std::string> map);
        size_t getInput();
        void clearBuffer() {}
        void displayBuffer() {}
        void setUserName(std::string name) {_userName = name;}
        std::string getUserName() {return _userName;}
        std::pair<bool, std::string> menu(std::vector<std::string> display, std::vector<std::string> game);
        void start();
        void stop();
        void drawNameLib();
        void drawName();
        int readUserName();
        void setScore(std::list<_score_t> scores) {_scores = scores;}
        void drawScore(std::list<_score_t> _scores);

    private:
        std::string _userName;
        std::vector<std::string> _game;
        std::vector<std::string> _display;
        size_t pos_game = 0;
        size_t pos_display = 0;
        size_t posCursor = 0;
        std::list<_score_t> _scores;
};

#endif /* !NCURSES_HPP_ */
