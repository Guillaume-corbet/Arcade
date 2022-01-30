##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## program
##

SRC	=	src/main.cpp		\
		src/Core.cpp		\
		src/Loader.cpp

NAME	=	arcade

FLAGS	=	-W -Wall -Werror -Wextra -Wunused-macros -Wendif-labels -pedantic -Wcomment -Wmissing-braces -Wmissing-include-dirs -Wparentheses -Wsequence-point -ansi -ggdb -Wunused -Wduplicated-branches -Wmisleading-indentation

NCURSES	=	-lncurses

SFML	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

.PHONY: games

all:	core graphicals games

valgrind:	graphicals games
			g++ -o $(NAME) $(SRC) -g3 -ldl

warning:	graphicals games
			g++ -o $(NAME) $(SRC) $(FLAGS) -g3 -ldl

optimize:	graphicals games
			g++ -o $(NAME) $(SRC) -O4 -ldl

clean:
		rm -f $(NAME)

fclean:
		rm -f $(NAME)
		rm -f *~
		rm -f *#

core:
		g++ -o $(NAME) $(SRC) -ldl

graphicals:
		g++ -shared -o lib_arcade_ncurses.so -fPIC lib/Ncurses/Ncurses.cpp $(NCURSES)
		mv lib_arcade_ncurses.so lib/
		g++ -shared -o lib_arcade_sfml.so -fPIC lib/SFML/Sfml.cpp $(SFML)
		mv lib_arcade_sfml.so lib/

games:
		g++ -shared -o lib_arcade_pacman.so -fPIC games/Pacman/Pacman.cpp games/Pacman/Ghost.cpp games/Pacman/RedGhost.cpp games/Pacman/OrangeGhost.cpp games/Pacman/PinkGhost.cpp games/Pacman/BlueGhost.cpp
		g++ -shared -o lib_arcade_nibbler.so -fPIC games/Nibbler/Nibbler.cpp
		mv lib_arcade_pacman.so games/
		mv lib_arcade_nibbler.so games/

test:	fclean all
		clear

re:		fclean all
