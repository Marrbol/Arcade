##
## EPITECH PROJECT, 2023
## B-OOP-400-REN-4-1-arcade-martin.boucault
## File description:
## Makefile
##

#DIRECTORY

GAME_DIR = Borne/games/

SNAKE_DIR = Snake/

NIBBLER_DIR = Nibbler/

DISPLAY_DIR = Borne/display/

NCURSES_DIR = NCURSES/

SDL_DIR = SDL/

SFML_DIR = SFML/

CORE_DIR = Borne/core/

LIB_DIR = lib/

#CORE

NAME_CORE = arcade

SRC_CORE = $(CORE_DIR)Core.cpp \
		   $(CORE_DIR)DLLoader.cpp \

OBJ_CORE = $(SRC_CORE:.cpp=.o)

#FLAGS

CFLAGS = -Wall -Werror

SHARED_FLAGS = -shared  -fpic

LDFLAGS = -ldl

# SNAKE

SRC_SNAKE = $(GAME_DIR)$(SNAKE_DIR)Snake.cpp \

NAME_SNAKE = $(LIB_DIR)arcade_snake.so

OBJ_SNAKE = $(SRC_SNAKE:.cpp=.o)

#NIBBLER

SRC_NIBBLER = $(GAME_DIR)$(NIBBLER_DIR)Nibbler.cpp \

NAME_NIBBLER = $(LIB_DIR)arcade_nibbler.so

OBJ_NIBBLER = $(SRC_NIBBLER:.cpp=.o)

#NCURSES

SRC_NCURSES = $(DISPLAY_DIR)$(NCURSES_DIR)Ncurses.cpp \

NAME_NCURSES = $(LIB_DIR)arcade_ncurses.so

OBJ_NCURSES = $(SRC_NCURSES:.cpp=.o)


#SDL

SRC_SDL = $(DISPLAY_DIR)$(SDL_DIR)Sdl.cpp \

NAME_SDL = $(LIB_DIR)arcade_sdl2.so

OBJ_SDL = $(SRC_SDL:.cpp=.o)

#SFML

SRC_SFML = $(DISPLAY_DIR)$(SFML_DIR)Sfml.cpp \

NAME_SFML = $(LIB_DIR)arcade_sfml.so

OBJ_SFML = $(SRC_SFML:.cpp=.o)

all: games graphicals core

games: $(NAME_SNAKE) $(NAME_NIBBLER)

graphicals: $(NAME_NCURSES) $(NAME_SDL) $(NAME_SFML)

core: $(NAME_CORE)

$(NAME_SNAKE):
	mkdir -p lib/
	g++ -std=c++20 $(SRC_SNAKE) -o $(NAME_SNAKE) $(CFLAGS) $(SHARED_FLAGS)

$(NAME_NIBBLER):
	g++ -std=c++20 $(SRC_NIBBLER) -o $(NAME_NIBBLER) $(CFLAGS) $(SHARED_FLAGS)

$(NAME_NCURSES):
	mkdir -p lib/
	g++ -std=c++20 $(SRC_NCURSES) -o $(NAME_NCURSES) $(CFLAGS) $(SHARED_FLAGS) -lncurses -lpanel -ltinfo

$(NAME_SDL):
	g++ -std=c++20 $(SRC_SDL) -fno-gnu-unique -o $(NAME_SDL) $(CFLAGS) $(SHARED_FLAGS) -D_REENTRANT -lSDL2 -lSDL2_ttf -L/usr/lib64

$(NAME_SFML):
	g++ -std=c++20 $(SRC_SFML) -o $(NAME_SFML) $(CFLAGS) $(SHARED_FLAGS) -lsfml-graphics -lsfml-window -lsfml-system

$(NAME_CORE):
	g++ -std=c++20 $(SRC_CORE) -fno-gnu-unique -o $(NAME_CORE) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ_CORE) $(OBJ_NCURSES) $(OBJ_NIBBLER) $(OBJ_SDL) $(OBJ_SFML) $(OBJ_SNAKE)

fclean: clean
	rm -f $(NAME_CORE) $(NAME_NCURSES) $(NAME_NIBBLER) $(NAME_SDL) $(NAME_SFML) $(NAME_SNAKE) vgcore.*

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY : games
.PHONY : libs
.PHONY : core
.PHONY : all