/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** Sfml
*/

#ifndef Sfml_HPP_
#define Sfml_HPP_

#include "../IDsiplayModule.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../../errorGestion.hpp"

class Sfml : public IDsiplayModule{
    public:
        Sfml();
        ~Sfml();
        const std::string getName() const {return "Sfml";}
        std::string getUserName();
        int readUserName();
        void setUserName(std::string name) {_userName = name;}
        void drawMap(std::vector<std::string> map);
        size_t getInput();
        void clearBuffer() {}
        void displayBuffer() {}
        std::pair<bool, std::string> menu(std::vector<std::string> display, std::vector<std::string> game);
        void start();
        void stop();
        void drawName();
        void setScore(std::list<_score_t> score) {_scores = score;}
        void drawScore(std::list<_score_t> _scores);

    private:
        sf::RenderWindow *_window = nullptr;
        sf::Event _event;
        sf::Font _font;
        std::string _userName;
        std::list<_score_t> _scores;
};

#endif /* !Sfml_HPP_ */
