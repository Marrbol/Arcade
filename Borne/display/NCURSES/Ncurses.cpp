/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

Ncurses::Ncurses()
{
}

Ncurses::~Ncurses()
{
}

void Ncurses::start()
{
    initscr();
    noecho();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    posCursor = 0;
}

void Ncurses::stop()
{
    posCursor = 0;
    endwin();
}

size_t Ncurses::getInput()
{
    nodelay(stdscr, TRUE);
    int input = getch();

    switch (input) {
        case KEY_UP:
            return (UP);
        case KEY_DOWN:
            return (DOWN);
        case KEY_LEFT:
            return (LEFT);
        case KEY_RIGHT:
            return (RIGHT);
        case ' ':
            return (SPACE);
        case 'q':
            return (QUIT);
        case 'r':
            return (RESTART);
        case 'm':
            return (MENU);
        case ERR:
            return (ERROR);
        case '1':
            return (NEXTGAME);
        case '2':
            return (NEXTDISPLAY);
        default:
            return (ERROR);
    }
}

void Ncurses::drawMap(std::vector<std::string> map)
{
    clear();
    int row, col;
    getmaxyx(stdscr, row, col);

    // Vérifier si l'écran est assez grand pour afficher la carte
    int mapHeight = map.size();
    int mapWidth = map[0].size();
    if (mapHeight > row || mapWidth > col) {
        printw("The screen is not big enough\n");
        refresh();
        return;
    }

    // Calculer la position de départ pour l'affichage de la carte
    int startRow, startCol;
    if (mapHeight == 1) {
        startRow = row / 2;
        startCol = (col - mapWidth) / 2;
    } else {
        startRow = (row - mapHeight) / 2;
        startCol = (col - mapWidth) / 2;
    }

    // Afficher la carte centrée
    for (int i = 0; i < mapHeight; i++) {
        move(startRow + i, startCol);
        for (int j = 0; j < mapWidth; j++) {
            char c = map[i][j];
            if (c == APPLE) {
                attron(COLOR_PAIR(2));
                printw("%c", c);
                attroff(COLOR_PAIR(2));
            } else if (c == WALL) {
                attron(COLOR_PAIR(3));
                printw("%c", c);
                attroff(COLOR_PAIR(3));
            } else if (c == HEAD || c == BODY) {
                attron(COLOR_PAIR(4));
                printw("%c", c);
                attroff(COLOR_PAIR(4));
            } else {
                printw("%c", c);
            }
        }
        printw("\n");
    }
    refresh();
}

void Ncurses::drawName()
{
    posCursor += 8;
    mvprintw(posCursor, 0, "Name:");
    if (_userName.size() > 0)
        mvprintw(posCursor, 7, _userName.c_str());
    posCursor += 3;
}

int Ncurses::readUserName()
{
    int input;
    int i = 0;

    if (_userName.size() > 0)
        return (0);
    nodelay(stdscr, FALSE);

    while (true) {
        input = getch();
        if (input == '\n')
            return (0);
        else if (input == ERR)
            continue;
        else {
            _userName += input;
            i++;
        }
        clear();
        drawNameLib();
        drawName();
        refresh();
    }
}

void Ncurses::drawScore(std::list<_score_t> scores)
{
    mvprintw(posCursor, 0, "Score:");
    posCursor += 1;

    std::string str;
    while (!scores.empty()) {
        str = scores.front().game + " : " + scores.front().name + " : " + std::to_string(scores.front().score);
        mvprintw(posCursor, 2, str.c_str());
        posCursor += 1;
        scores.pop_front();
    }
}

void Ncurses::drawNameLib()
{
    size_t i = 0;
    // Affichage des vecteurs
    mvprintw(0, 0, "game:");
    for (size_t i = 0; i < _game.size(); i++) {
        printw("\n    ");
        if (i == pos_game) {
            attron(COLOR_PAIR(1));
            printw("%s", _game[i].c_str());
            attroff(COLOR_PAIR(1));
        } else
            printw("%s", _game[i].c_str());
    }
    mvprintw(_display.size()+2, 0, "display: ");
    for (const auto& str : _display) {
        if (str == "./lib/arcade_ncurses.so") {
            pos_display = i;
            // If the string is "ncurses", print it with the custom color pair
            attron(COLOR_PAIR(1));
            mvprintw(_display.size()+i+3, 4,"%s", str.c_str());
            attroff(COLOR_PAIR(1));
        } else {
            // If the string is not "ncurses", print it normally
            mvprintw(_display.size()+i+3, 4,"%s\n", str.c_str());
        }
        i++;
    }
    posCursor = i;
}

std::pair<bool, std::string> Ncurses::menu(std::vector<std::string> display, std::vector<std::string> game)
{
    int input;
    nodelay(stdscr, FALSE);
    _game = game;
    _display = display;

    while (true) {
        // Effacement de la console
        clear();
        drawNameLib();
        drawName();
        drawScore(_scores);
        refresh();
        input = getch();
        if (input == NEXTGAME) {
            pos_game += 1;
            if (pos_game >= game.size())
                pos_game = 0;
        }
        if (input == NEXTDISPLAY) {
            pos_display += 1;
            if (pos_display >= display.size())
                pos_display = 0;
            return std::make_pair(true, display[pos_display]);
        }
        if (input == QUIT) {
            return std::make_pair(true, "quit");
        }
        if (input == ENTER) {
            return std::make_pair(false, game[pos_game]);
        }
        if (input == 'n') {
            readUserName();
        }
    }
    return std::make_pair(false, "");
}

extern "C" IDsiplayModule *entryDisplay()
{
    return new Ncurses();
}
