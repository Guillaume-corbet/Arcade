/*
** EPITECH PROJECT, 2020
** rush3
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

/* Class */

Ncurses::Ncurses()
{
    this->_cols = 0;
    this->_lines = 0;
}

Ncurses::~Ncurses()
{
}


/* Start */

void Ncurses::startGraphic()
{
    initscr();
    noecho();
    nodelay(stdscr, true);
    clear();
    curs_set(0);
    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_color(COLOR_GREEN, 500, 1000, 200);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(COLOR_MAGENTA, 1000, 800, 1000);
    init_color(9, 1000, 500, 0);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, 9, COLOR_BLACK);
    bkgd(COLOR_PAIR(4));
}

void Ncurses::setRotationMap(std::vector<std::vector<std::string>> rotationMap)
{
}

void Ncurses::setAnimationMap(std::map<char, std::string> animationMap)
{
}

void Ncurses::setSpritesNames(std::map<char, std::string> spritesNames)
{
}

void Ncurses::setMovementDirection(std::map<std::string, char> movement)
{
}


/* events */

int Ncurses::getEventGraphic()
{
    int ch = 0;

    return (ch = getch());
}

int Ncurses::getEventPseudoGraphic()
{
    return (this->getEventGraphic());
}

void Ncurses::refreshGraphic()
{
    clear();
    refresh();
}

bool Ncurses::isScreenTooSmallGraphic()
{
    this->ncursesSizeChange();
    return (this->isTerminalTooSmall());
}

void Ncurses::displayScreenTooSmallGraphic()
{
    if (LINES < LINES_MAX || COLS < COLS_MAX) {
        clear();
    }
    this->ncursesSizeChange();
    mvprintw(LINES / 2, COLS / 2 - 10, "Terminal too small");
}

void Ncurses::ncursesSizeChange()
{
    if (this->getCols() != COLS || this->getLines() != LINES) {
        this->setCols(COLS);
        this->setLines(LINES);
        clear();
        refresh();
    }
}

bool Ncurses::isTerminalTooSmall()
{
    if (LINES < LINES_MAX || COLS < COLS_MAX) {
        return (true);
    }
    return (false);
}

int Ncurses::pause(void)
{
    int ch = getch();

    clear();
    while (ch != 'p') {
        this->ncursesSizeChange();
        mvprintw(LINES / 2, COLS / 2 - 14, "PAUSE press again to continue");
        ch = getch();
        if (ch == 'q') {
            this->endGraphic();
            exit(0);
        }
    }
    clear();
    return (0);
}

void Ncurses::endGraphic()
{
    endwin();
}


/* Menu */

void Ncurses::startMenuGraphic()
{
    initscr();
    noecho();
    nodelay(stdscr, true);
    clear();
    curs_set(0);
    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_color(COLOR_GREEN, 500, 1000, 200);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(COLOR_MAGENTA, 1000, 800, 1000);
    init_color(9, 1000, 500, 0);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, 9, COLOR_BLACK);
    bkgd(COLOR_PAIR(4));
}

void Ncurses::displayMenuGraphic(int place, std::vector<std::string> *games)
{
    mvprintw(10 + (5 * place), COLS / 2 - 10, "->");
    for (size_t i = 0; i < games->size(); i++) {
        mvprintw(15 + (5 * i), COLS / 2 - (games->at(i).size()) / 2, games->at(i).c_str());
        if ((i + 1) == games->size()) {
            mvprintw(20 + (5 * i), COLS / 2 - 2, "exit");
        }
    }
}

void Ncurses::displayMenuPseudoGraphic(std::string name)
{
    mvprintw(LINES / 2 - 2, COLS / 2 - 8, "Enter your name");
    mvprintw(LINES / 2 + 1, COLS / 2 - (name.size() / 2), name.c_str());
}

/* Display game */

int Ncurses::getCols() const
{
    return (this->_cols);
}

int Ncurses::getLines() const
{
    return (this->_lines);
}

void Ncurses::setCols(int cols)
{
    this->_cols = cols;
}

void Ncurses::setLines(int lines)
{
    this->_lines = lines;
}

void Ncurses::displayMap(std::vector<std::string> map)
{
    std::vector<std::string> mapResize;

    for (size_t i = 0; i < map.size(); i++) {
        mapResize.push_back("");
        mapResize.at(i).push_back(map.at(i).at(0));
        for (size_t j = 1; j < map.at(i).size(); j++) {
            if ((map.at(i).at(j - 1) == '+' && map.at(i).at(j) == '+') || (map.at(i).at(j - 1) == '+' && map.at(i).at(j) == '-') || (map.at(i).at(j - 1) == '-' && map.at(i).at(j) == '+') || (map.at(i).at(j - 1) == '-' && map.at(i).at(j) == '-'))
                mapResize.at(i).push_back('-');
            else
                mapResize.at(i).push_back(' ');
            if (map.at(i).at(j) != 'n' && map.at(i).at(j) != 'm' && map.at(i).at(j) != 'H')
                mapResize.at(i).push_back(map.at(i).at(j));
            else
                mapResize.at(i).push_back(' ');
        }
    }

    for (size_t i = 0; i < mapResize.size(); i++) {
        for (size_t j = 0; j < mapResize.at(i).size(); j++) {
            if (mapResize.at(i).at(j) == 'o' || mapResize.at(i).at(j) == 'P') {
                attron(COLOR_PAIR(color::YELLOW + 1));
                mvprintw((LINES - mapResize.size()) / 2 + i, (COLS - mapResize.at(i).size()) / 2 + j, &mapResize.at(i).at(j));
                attroff(COLOR_PAIR(color::YELLOW + 1));
            } else if (mapResize.at(i).at(j) == '-' || mapResize.at(i).at(j) == '|' || mapResize.at(i).at(j) == '+') {
                attron(COLOR_PAIR(color::GREEN + 1));
                mvprintw((LINES - mapResize.size()) / 2 + i, (COLS - mapResize.at(i).size()) / 2 + j, &mapResize.at(i).at(j));
                attroff(COLOR_PAIR(color::GREEN + 1));
            } else {
                mvprintw((LINES - mapResize.size()) / 2 + i, (COLS - mapResize.at(i).size()) / 2 + j, &mapResize.at(i).at(j));
            }
        }
    }
}

void Ncurses::displayScore(int score, std::string highscore)
{
    std::string strScore = "score = " + std::to_string(score);
    mvprintw(3, COLS / 2 - (strScore.size() / 2), strScore.c_str());
    strScore = "highscore : " + highscore;
    mvprintw(4, COLS / 2 - (strScore.size() / 2), strScore.c_str());
}

void Ncurses::displayVictory(int score, int place, std::string name, std::string high)
{
    std::string strScore = "score = " + std::to_string(score) + ", Highscore: " + high;
    mvprintw(LINES / 4 - 2, COLS / 2 - 9, "Bravo tu as gagné");
    mvprintw(LINES / 4, COLS / 2 - (name.size() / 2), name.c_str());
    mvprintw(LINES / 4 + 2, COLS / 2 - (strScore.size() / 2), strScore.c_str());
    mvprintw(LINES / 4 * 2 + (5 * place), COLS / 2 - 10, "->");
    mvprintw(LINES / 4 * 2, COLS / 2 - 5, "Continuer");
    mvprintw(LINES / 4 * 2 + 5, COLS / 2 - 2, "menu");
    mvprintw(LINES / 4 * 2 + 10, COLS / 2 - 2, "exit");
}

void Ncurses::displayDefeat(int score, int place, std::string name, std::string high)
{
    std::string strScore = "score = " + std::to_string(score) + ", Highscore: " + high;
    mvprintw(LINES / 4 - 2, COLS / 2 - 14, "Tu as perdu misérablement !");
    mvprintw(LINES / 4, COLS / 2 - (name.size() / 2), name.c_str());
    mvprintw(LINES / 4 + 2, COLS / 2 - (strScore.size() / 2), strScore.c_str());
    mvprintw(LINES / 4 * 2 + (5 * place), COLS / 2 - 10, "->");
    mvprintw(LINES / 4 * 2, COLS / 2 - 5, "Continuer");
    mvprintw(LINES / 4 * 2 + 5, COLS / 2 - 2, "menu");
    mvprintw(LINES / 4 * 2 + 10, COLS / 2 - 2, "exit");
}