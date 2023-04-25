/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** Sdl
*/

#ifndef Sdl_HPP_
#define Sdl_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../errorGestion.hpp"

#include "../IDsiplayModule.hpp"
class Sdl : public IDsiplayModule{
    public:
        Sdl();
        ~Sdl();
        const std::string getName() const {return "Sdl";}
        void drawMap(std::vector<std::string> map);
        size_t getInput();
        std::string getUserName() {return _userName;}
        int readUserName();
        void setUserName(std::string name) {_userName = name;}
        void drawName();
        void clearBuffer() {}
        void displayBuffer() {}
        std::pair<bool, std::string> menu(std::vector<std::string> display, std::vector<std::string> game);
        int createTextMenu(std::vector<std::string> display, std::vector<std::string> game);
        void start();
        void stop();
        void destroy_menu();
        void setScore(std::list<_score_t> scores) {_scores = scores;}
        void drawScore(std::list<_score_t> scores, int x, int y, int lineHeight);
    private:
        std::vector<std::string> _game;
        std::vector<std::string> _display;
        std::string _userName;
        SDL_Window *_window;
        TTF_Font *_font;
        SDL_Color _textColor;
        SDL_Color _textColorSelected;
        SDL_Surface *_surfaceScore;
        SDL_Texture *_textureScore;
        SDL_Rect _rectScore;
        SDL_Surface *_surfaceheaderGame;
        SDL_Surface *_surfaceheaderDisplay;
        SDL_Texture *_textureheaderGame;
        SDL_Texture *_textureheaderDisplay;
        std::vector<SDL_Surface *> _surfaceGame;
        std::vector<SDL_Surface *> _surfaceDisplay;
        std::vector<SDL_Texture *> _textureGame;
        std::vector<SDL_Texture *> _textureDisplay;
        std::vector<SDL_Rect> _rectGame;
        std::vector<SDL_Rect> _rectDisplay;
        SDL_Renderer *_renderer;
        SDL_Rect _position;
        size_t _indexGame;
        size_t _indexDisplay;
        size_t _sizeWinX = 1000;
        size_t _sizeWinY = 1000;
        SDL_Event _event;
        std::list<_score_t> _scores = {};
};

#endif /* !Sdl_HPP_ */
