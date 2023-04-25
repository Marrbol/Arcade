/*
** EPITECH PROJECT, SQUARESIZE23
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** Sdl
*/

#include "Sdl.hpp"

Sdl::Sdl()
{
}

Sdl::~Sdl()
{
}

void Sdl::start()
{
    SDL_Init(SDL_INIT_VIDEO);
    if (TTF_Init() < 0) {
        return;
        // gestion de l'erreur d'initialisation
    }
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    _font = TTF_OpenFont("Borne/assets/Font.ttf", 30);
    if (_font == nullptr) {
        return;
    // gestion de l'erreur de chargement de la police
    }
   _textColor = {255, 255, 255, 255};
    _textColorSelected = {105, 0, 255, 255};
    _indexGame = 0;
}

void Sdl::stop()
{
    // SDL_FreeSurface(surface_text);
    TTF_CloseFont(_font);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_Quit();
    SDL_Quit();
}

void Sdl::drawScore(std::list<_score_t> scores, int y, int x, int lineHeight)
{
    _score_t score;
    std::string str;
    SDL_Color textColor = { 255, 255, 255, 255 };

    y += lineHeight;
    for (size_t i = 0; i < _scores.size(); i++) {
        score = scores.front();
        str.append(score.game);
        str.append(" : ");
        str.append(score.name);
        str.append(" : ");
        str.append(std::to_string(score.score));
        _surfaceScore = TTF_RenderText_Blended(_font, str.c_str(), textColor);
        _textureScore = SDL_CreateTextureFromSurface(_renderer, _surfaceScore);
        _rectScore = {x, y, _surfaceScore->w, _surfaceScore->h };
        SDL_RenderCopy(_renderer, _textureScore, NULL, &_rectScore);
        y += lineHeight;
        str.clear();
        scores.pop_front();
    }
}

int Sdl::createTextMenu(std::vector<std::string> display, std::vector<std::string> game)
{
    size_t index = 0;
    _surfaceheaderGame = TTF_RenderText_Solid(_font, "Game:", _textColor);
    if (_surfaceheaderGame == nullptr) {
        throw elementCreationError("_surfaceheaderGame creation failed");
        // gestion de l'erreur de création de la surface de texte
    }
    _textureheaderGame = SDL_CreateTextureFromSurface(_renderer, _surfaceheaderGame);
    if (_textureheaderGame == nullptr) {
        throw elementCreationError("_textureheaderGame creation failed");
        // gestion de l'erreur de création de la texture de texte
    }
    _position = {20, 0, _surfaceheaderGame->w, _surfaceheaderGame->h};
    SDL_RenderCopy(_renderer, _textureheaderGame, nullptr, &_position);
    SDL_Color textColor = { 255, 255, 255, 255 };
    int x = 50, y = 50, lineHeight = 45;
    for (auto& str : game) {
        if (_indexGame == index)
            _surfaceGame.push_back(TTF_RenderText_Blended(_font, str.c_str(), _textColorSelected));
        else
            _surfaceGame.push_back(TTF_RenderText_Blended(_font, str.c_str(), textColor));
        _textureGame.push_back(SDL_CreateTextureFromSurface(_renderer, _surfaceGame.back()));
        _rectGame.push_back({ x, y, _surfaceGame.back()->w, _surfaceGame.back()->h });
        SDL_RenderCopy(_renderer, _textureGame.back(), NULL, &_rectGame.back());
        y += lineHeight;
        index++;
    }
    _surfaceheaderDisplay = TTF_RenderText_Solid(_font, "Display:", textColor);
    if (_surfaceheaderDisplay == nullptr) {
        throw elementCreationError("_surfaceheaderDisplay creation failed");
        // gestion de l'erreur de création de la surface de texte
    }
    _textureheaderDisplay = SDL_CreateTextureFromSurface(_renderer, _surfaceheaderDisplay);
    if (_textureheaderDisplay == nullptr) {
        throw elementCreationError("_textureheaderDisplay creation failed");
        // gestion de l'erreur de création de la texture de texte
    }
    _position = {20, 250, _surfaceheaderDisplay->w, _surfaceheaderDisplay->h};
    SDL_RenderCopy(_renderer, _textureheaderDisplay, nullptr, &_position);
    y = 300;

    for (auto& str : display) {
        if (!str.compare("./lib/arcade_sdl2.so"))
            _surfaceDisplay.push_back(TTF_RenderText_Blended(_font, str.c_str(), _textColorSelected));
        else
            _surfaceDisplay.push_back(TTF_RenderText_Blended(_font, str.c_str(), textColor));
        _textureDisplay.push_back(SDL_CreateTextureFromSurface(_renderer, _surfaceDisplay.back()));
        _rectDisplay.push_back({x, y, _surfaceDisplay.back()->w, _surfaceDisplay.back()->h });
        SDL_RenderCopy(_renderer, _textureDisplay.back(), NULL, &_rectDisplay.back());
        y += lineHeight;
    }

    _surfaceScore = TTF_RenderText_Solid(_font, "Score:", textColor);
    if (_surfaceScore == nullptr) {
        throw elementCreationError("_surfaceScore creation failed");
        // gestion de l'erreur de création de la surface de texte
    }
    _textureScore = SDL_CreateTextureFromSurface(_renderer, _surfaceScore);
    if (_textureScore == nullptr) {
        throw elementCreationError("_textureScore creation failed");
        // gestion de l'erreur de création de la texture de texte
    }
    y = 630;
    x = 50;
    _position = {20, y, _surfaceScore->w, _surfaceScore->h};
    SDL_RenderCopy(_renderer, _textureScore, nullptr, &_position);
    if (_scores.size() < 0)
        return 0;
    drawScore(_scores, y, x, lineHeight);
    return 0;
}

void Sdl::destroy_menu()
{
    size_t i = _surfaceGame.size();
    for (; i > 0; i--) {
        SDL_FreeSurface(_surfaceGame.back());
        _surfaceGame.pop_back();
    }
    i = _textureGame.size();
    for (; i > 0; i--) {
        SDL_DestroyTexture(_textureGame.back());
        _textureGame.pop_back();
    }
    i = _rectGame.size();
    for (; i > 0; i--) {
        _rectGame.pop_back();
    }
    i = _surfaceDisplay.size();
    for (; i > 0; i--) {
        SDL_FreeSurface(_surfaceDisplay.back());
        _surfaceDisplay.pop_back();
    }
    i = _textureDisplay.size();
    for (; i > 0; i--) {
        SDL_DestroyTexture(_textureDisplay.back());
        _textureDisplay.pop_back();
    }
    i = _rectDisplay.size();
    for (; i > 0; i--) {
        _rectDisplay.pop_back();
    }
    SDL_FreeSurface(_surfaceheaderGame);
    SDL_DestroyTexture(_textureheaderGame);
    SDL_FreeSurface(_surfaceheaderDisplay);
    SDL_DestroyTexture(_textureheaderDisplay);
    SDL_RenderClear(_renderer);
}

size_t Sdl::getInput()
{
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT)
            return QUIT;
        if (_event.type == SDL_KEYDOWN) {
            switch (_event.key.keysym.sym) {
                case SDLK_KP_2:
                case SDLK_2:
                    return NEXTDISPLAY;
                case SDLK_KP_1:
                case SDLK_1:
                    return NEXTGAME;
                case SDLK_q:
                    return QUIT;
                case SDLK_r:
                    return RESTART;
                case SDLK_m:
                    return MENU;
            }
            switch (_event.key.keysym.scancode) {
                case SDL_SCANCODE_RIGHT:
                    return RIGHT;
                case SDL_SCANCODE_LEFT:
                    return LEFT;
                case SDL_SCANCODE_UP:
                    return UP;
                case SDL_SCANCODE_DOWN:
                    return DOWN;
                default:
                    break;
            }
        }
    }
    return 0;
}

void Sdl::drawName()
{
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface *surface = TTF_RenderText_Solid(_font, "Name:", textColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_Rect position = {16, 520, surface->w, surface->h};
    SDL_RenderCopy(_renderer, texture, nullptr, &position);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    if (_userName.size() > 0) {
        textColor = { 255, 255, 255, 255 };
        surface = TTF_RenderText_Solid(_font, _userName.c_str(), textColor);
        texture = SDL_CreateTextureFromSurface(_renderer, surface);
        position = {200, 520, surface->w, surface->h};
        SDL_RenderCopy(_renderer, texture, nullptr, &position);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}


int Sdl::readUserName()
{
    if (_userName.size() > 0)
        return 0;

    while (SDL_WaitEvent(&_event)) {
        if (_event.type == SDL_QUIT)
            return 1;
        if (_event.type == SDL_KEYDOWN) {
            if (_event.key.keysym.sym == SDLK_KP_ENTER || _event.key.keysym.sym == SDLK_RETURN) {
                _event.key.keysym.sym = SDLK_0;
                return 0;
            }
            // if (_event.key.code == sf::Keyboard::BackSpace)
            //     _userName.pop_back();
            if (_event.key.keysym.sym >= SDLK_a && _event.key.keysym.sym <= SDLK_z)
                _userName += _event.key.keysym.sym;
        }
        createTextMenu(_display, _game);
        // Affichage de la fenêtre
        drawName();
        SDL_RenderPresent(_renderer);
        destroy_menu();
    }
    return 0;
}

std::pair<bool, std::string> Sdl::menu(std::vector<std::string> display, std::vector<std::string> game)
{
    _display = display;
    _game = game;
    size_t i = 0;
    for (auto &str : display) {
        if (!str.compare("./lib/arcade_sdl2.so"))
            _indexDisplay = i;
        i++;
    }
    createTextMenu(display, game);
    drawName();
    // Affichage de la fenêtre
    SDL_RenderPresent(_renderer);
    destroy_menu();
    // Attendre la fin du programme
    while (SDL_WaitEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            break;
        }
        if (_event.type == SDL_KEYDOWN) {
            switch (_event.key.keysym.sym) {
                case SDLK_KP_ENTER:
                case SDLK_RETURN:
                    return std::make_pair(false, game[_indexGame]);
                case SDLK_KP_2:
                case SDLK_2:
                    _indexDisplay++;
                    if (_indexDisplay >= display.size())
                        _indexDisplay = 0;
                    return std::make_pair(true, display[_indexDisplay]);
                case SDLK_KP_1:
                case SDLK_1:
                    _indexGame++;
                    if (_indexGame >= game.size())
                        _indexGame = 0;
                    break;
                case SDLK_q:
                    return std::make_pair(false, "quit");
                case SDLK_n:
                    if (readUserName() == 1)
                        return std::make_pair(false, "quit");
                    break;
                default:
                    break;
            }
        }
        createTextMenu(display, game);
        // Affichage de la fenêtre
        drawName();
        SDL_RenderPresent(_renderer);
        destroy_menu();
    }
    return std::make_pair(false, "quit");
}

int main()
{
    Sdl sdl;
    sdl.start();
    sdl.menu(std::vector<std::string>(), std::vector<std::string>());
    sdl.stop();
    return 0;
}

void Sdl::drawMap(std::vector<std::string> map)
{
    SDL_RenderClear(_renderer);
    int y = ((SIZEWINY / 2) - (SQUARESIZE * (map.size() / 2)));
    int x = ((SIZEWINX /2) - (SQUARESIZE * (map[0].size() / 2)));
    if (map[0].at(0) != WALL) {
        for (auto str: map) {
            _surfaceheaderGame = TTF_RenderText_Solid(_font, str.c_str(), _textColor);
            _textureheaderGame = SDL_CreateTextureFromSurface(_renderer, _surfaceheaderGame);
            _position = {x, y, _surfaceheaderGame->w, _surfaceheaderGame->h};
            SDL_RenderCopy(_renderer, _textureheaderGame, nullptr, &_position);
            y += SQUARESIZE;
        }
    } else {
        // print the game map
        for (auto line : map) {
            x = ((SIZEWINX /2) - (SQUARESIZE * (map[0].size() / 2)));
            for (auto c : line) {
                SDL_Rect rect = {x, y, SQUARESIZE, SQUARESIZE};
                switch (c) {
                    case WALL:
                        SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
                        break;
                    case HEAD:
                        SDL_SetRenderDrawColor(_renderer, 105, 0, 255, 255);
                        break;
                    case BODY:
                        SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
                        break;
                    case APPLE:
                        SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
                        break;
                    default:
                        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
                }
                SDL_RenderFillRect(_renderer, &rect);
                x += SQUARESIZE;
            }
            y +=SQUARESIZE;
        }
    }
    SDL_RenderPresent(_renderer);
}

extern "C" IDsiplayModule *entryDisplay()
{
    return new Sdl();
}
