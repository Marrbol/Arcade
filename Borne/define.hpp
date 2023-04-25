/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-martin.boucault
** File description:
** define
*/

#ifndef DEFINE_HPP_
#define DEFINE_HPP_

#define UP 403          //up key
#define DOWN 402        //down key
#define LEFT 404        //left key
#define RIGHT 405       //right key
#define ENTER 10        //'\n'/ enter key
#define QUIT 113        //q key
#define SPACE 32        //space key
#define RESTART 114     // r key
#define MENU 109        // m key
#define ERROR 0         //error/no key entered
#define NEXTGAME 49     // 1 key
#define NEXTDISPLAY 50  // 2 key
#define EMPTY ' '       //empty space
#define APPLE '@'
#define WALL '#'
#define HEAD 'o'
#define BODY 'x'
#define SIZEMAP 20
#define SIZEWINX 1000
#define SIZEWINY 1000
#define SQUARESIZE 30
#define GREY 175, 175, 175, 175

typedef struct _score {
    size_t score;
    std::string name;
    std::string game;
} _score_t;

#endif /* !DEFINE_HPP_ */
