/*
** EPITECH PROJECT, 2020
** rush3
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include <ncurses.h>
#include <string>
#include <string.h>
#include <vector>
#include "../../interface/IGraphic.hpp"

#define COLS_MAX 100
#define LINES_MAX 40

// YELLOW PACMAN ET BOULE
// GREEN MUR
// RED FANTOME ROUGE
// WHITE LES SUPER BOULES
// BLUE FANTOME QUI ONT PEUR
// CYAN FANTOME BLEU
// MAGENTA FANTOME ROSE
// ORANGE FANTOME ORANGE

class Ncurses : public IGraphic {
	public:
        enum color{YELLOW, GREEN, RED, WHITE, BLUE, CYAN, MAGENTA, ORANGE};
		Ncurses();
		~Ncurses();
        void startGraphic();
        void setRotationMap(std::vector<std::vector<std::string>> rotationMap);
        void setAnimationMap(std::map<char, std::string> animationMap);
        void setSpritesNames(std::map<char, std::string> spritesNames);
        void setMovementDirection(std::map<std::string, char> movement);
        int getEventGraphic();
        int getEventPseudoGraphic();
        void refreshGraphic();
        bool isScreenTooSmallGraphic();
        void displayScreenTooSmallGraphic();
        void ncursesSizeChange();
        bool isTerminalTooSmall();
        int pause();
        void endGraphic();
        void startMenuGraphic();
        void displayMenuGraphic(int place, std::vector<std::string> *games);
        void displayMenuPseudoGraphic(std::string name);
        int getCols() const;
        int getLines() const;
        void displayMap(std::vector<std::string> map);
        void displayScore(int score, std::string highscore);
        void displayVictory(int score, int place, std::string name, std::string high);
        void displayDefeat(int score, int place, std::string name, std::string high);
	protected:
        void setCols(int cols);
        void setLines(int lines);
	private:
        int _cols;
        int _lines;
};

extern "C"
{
    IGraphic *entryPoint()
    {
        return (new Ncurses());
    }
}

#endif /* !IGRAPHIC_HPP_ */