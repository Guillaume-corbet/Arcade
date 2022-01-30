/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#include "Pacman.hpp"

/* Class */

Pacman::Pacman()
{
    createAnimationMap();
    createSpritesNames();
}

Pacman::~Pacman()
{
    
}


/* Creation */

void Pacman::createGhosts()
{
    _ghosts.clear();
    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map.at(i).size(); j++) {
            if (strchr("1234", this->map.at(i).at(j))) {
                if (this->map.at(i).at(j) == '1')
                    _ghosts.push_back(new RedGhost(this->map.at(i).at(j), j, i));
                else if (this->map.at(i).at(j) == '2')
                    _ghosts.push_back(new OrangeGhost(this->map.at(i).at(j), j, i));
                else if (this->map.at(i).at(j) == '3')
                    _ghosts.push_back(new PinkGhost(this->map.at(i).at(j), j, i));
                else
                    _ghosts.push_back(new BlueGhost(this->map.at(i).at(j), j, i));
                this->map.at(i).at(j) = ' ';
            }
        }
    }
}

void Pacman::createOrigMap()
{
    std::vector<std::string> tmp;

    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map.at(i).size(); j++) {
            if (strchr("+-|", this->map.at(i).at(j)))
                tmp.push_back(getSprite(this->map, j, i) + ";" + getRotate(this->map, j, i));
            else
                tmp.push_back("");
        }
        this->begin_map.push_back(tmp);
        tmp.clear();
    }
}

void Pacman::createAnimationMap()
{
    animationMap.insert(std::pair<char, std::string>('P', "23"));
    animationMap.insert(std::pair<char, std::string>('1', "18"));
    animationMap.insert(std::pair<char, std::string>('2', "18"));
    animationMap.insert(std::pair<char, std::string>('3', "18"));
    animationMap.insert(std::pair<char, std::string>('4', "18"));
    animationMap.insert(std::pair<char, std::string>('o', "01"));
    animationMap.insert(std::pair<char, std::string>('O', "00"));
    animationMap.insert(std::pair<char, std::string>('f', "12"));
    animationMap.insert(std::pair<char, std::string>('d', "12"));
}

void Pacman::createSpritesNames()
{
    _spritesNames.insert(std::pair<char, std::string>('+', "games/Pacman/sprites/big_angle_pacman.png"));
    _spritesNames.insert(std::pair<char, std::string>('-', "games/Pacman/sprites/simple_wall_pacman.png"));
    _spritesNames.insert(std::pair<char, std::string>('|', "games/Pacman/sprites/simple_wall_pacman.png"));
    _spritesNames.insert(std::pair<char, std::string>('o', "games/Pacman/sprites/point_pacman.png"));
    _spritesNames.insert(std::pair<char, std::string>('O', "games/Pacman/sprites/point_pacman.png"));
    _spritesNames.insert(std::pair<char, std::string>('1', "games/Pacman/sprites/red_ghost_pacman.png"));
    _spritesNames.insert(std::pair<char, std::string>('2', "games/Pacman/sprites/orange_ghost_pacman.png"));
    _spritesNames.insert(std::pair<char, std::string>('3', "games/Pacman/sprites/pink_ghost_pacman.png"));
    _spritesNames.insert(std::pair<char, std::string>('4', "games/Pacman/sprites/blue_ghost_pacman.png"));
    _spritesNames.insert(std::pair<char, std::string>('P', "games/Pacman/sprites/pacman.png"));
    _spritesNames.insert(std::pair<char, std::string>('f', "games/Pacman/sprites/fleeing_ghost_pacman.png"));
    _spritesNames.insert(std::pair<char, std::string>('d', "games/Pacman/sprites/dead_ghost_pacman.png"));
    _spritesNames.insert(std::pair<char, std::string>('n', ""));
    _spritesNames.insert(std::pair<char, std::string>('m', ""));
    _spritesNames.insert(std::pair<char, std::string>('H', ""));
    _spritesNames.insert(std::pair<char, std::string>('B', "games/Pacman/sprites/background_pacman.png"));
}

std::string Pacman::getRotate(std::vector<std::string> map, int x, int y)
{
    std::string rotate = "0";
    char current = map.at(y).at(x);

    if (current == '+') {
        if (x > 0 && (map.at(y).at(x - 1) == '-' || map.at(y).at(x - 1) == '+') && y < map.size() - 1 && (map.at(y + 1).at(x) == '|' || map.at(y + 1).at(x) == '+'))
            rotate = "0";
        if (x > 0 && (map.at(y).at(x - 1) == '-' || map.at(y).at(x - 1) == '+') && y > 0 && (map.at(y - 1).at(x) == '|' || map.at(y - 1).at(x) == '+'))
            rotate = "1";
        if (x < map.at(y).size() - 1 && (map.at(y).at(x + 1) == '-' || map.at(y).at(x + 1) == '+') && y > 0 && (map.at(y - 1).at(x) == '|' || map.at(y - 1).at(x) == '+'))
            rotate = "2";
        if (x < map.at(y).size() - 1 && (map.at(y).at(x + 1) == '-' || map.at(y).at(x + 1) == '+') && y < map.size() - 1 && (map.at(y + 1).at(x) == '|' || map.at(y + 1).at(x) == '+'))
            rotate = "3";
    }
    else if (current == '-') {
        rotate = "1";
        if ((y > 0 && (map.at(y - 1).at(x) == 'o' || map.at(y - 1).at(x) == 'O')) || (y < map.size() - 1 && strchr("n1234-+", map.at(y + 1).at(x))))
            rotate = "3";
    }
    else if (current == '|') {
        rotate = "0";
        if ((x > 0 && (map.at(y).at(x - 1) == 'o' || map.at(y).at(x - 1) == 'O')) || (x < map.at(y).size() - 1 && strchr("n1234|+", map.at(y).at(x + 1))))
            rotate = "2";
    }
    return (rotate);
}

std::string Pacman::getSprite(std::vector<std::string> map, int x, int y)
{
    std::string res;

    for (std::map<char, std::string>::iterator ite = _spritesNames.begin(); ite != _spritesNames.end(); ite++) {
        if (ite->first == map.at(y).at(x)) {
            if (map.at(y).at(x) == '+' && ((y == 0 || !strchr("oOm", map.at(y - 1).at(x))) && (x == 0 || !strchr("oOm", map.at(y).at(x - 1))) && (y >= map.size() - 1 || !strchr("oOm", map.at(y + 1).at(x))) && (x >= map.at(y).size() - 1 || !strchr("oOm", map.at(y).at(x + 1)))))
                res = "";
            else
                res = ite->second;
        }
    }
    return (res);
}

void Pacman::upgradeMovements()
{
    std::string tmp;
    char res;

    movements.clear();
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.at(i).size(); j++) {
            if (map.at(i).at(j) == 'P') {
                tmp = std::to_string(j) + ", " + std::to_string(i);
                break;
            }
        }
        if (!tmp.empty())
            break;
    }
    if (_x == -1)
        res = '3';
    else if (_x == 1)
        res = '1';
    else if (_y == -1)
        res = '2';
    else
        res = '0';
    movements.insert(std::pair<std::string, char>(tmp, res));
    for (int i = 0; i < _ghosts.size(); i++) {
        tmp = std::to_string(_ghosts.at(i)->getX()) + ", " + std::to_string(_ghosts.at(i)->getY());
        if (_ghosts.at(i)->getState() == 0)
            res = _ghosts.at(i)->getDirection() + 48;
        else
            res = 0;
        movements.insert(std::pair<std::string, char>(tmp, res));
    }
}

std::map<std::string, char> Pacman::getMovements()
{
    upgradeMovements();
    return (movements);
}

std::map<char, std::string> Pacman::getSpritesNames()
{
    return (_spritesNames);
}

std::map<char, std::string> Pacman::getAnimationMap()
{
    return (animationMap);
}

std::string Pacman::getHighscore()
{
    return (this->_highscore);
}

void Pacman::setHighscore(std::string highscore)
{
    this->_highscore = highscore;
}

std::vector<std::string> Pacman::getMap() const
{
    std::vector<std::string> tmp = this->map;
    int pacX;
    int pacY;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.at(i).size(); j++) {
            if (map.at(i).at(j) == 'P') {
                pacX = j;
                pacY = i;
            }
        }
    }
    for (int i = 0; i < _ghosts.size(); i++) {
        if (_ghosts.at(i)->getX() == pacX && _ghosts.at(i)->getY() == pacY)
            continue;
        else if (_ghosts.at(i)->getState() == 0)
            tmp.at(_ghosts.at(i)->getY()).at(_ghosts.at(i)->getX()) = _ghosts.at(i)->getName();
        else if (_ghosts.at(i)->getState() == 1)
            tmp.at(_ghosts.at(i)->getY()).at(_ghosts.at(i)->getX()) = 'f';
        else if (_ghosts.at(i)->getState() == 2)
            tmp.at(_ghosts.at(i)->getY()).at(_ghosts.at(i)->getX()) = 'd';
    }
    return (tmp);
}

std::vector<std::vector<std::string>> Pacman::getOrigMap() const
{
    return (this->begin_map);
}


/* Game initialisation */


void Pacman::getHighscoreFile()
{
    std::string line;
    std::ifstream file;

    file.open("highscore/pacman");
    if (!file.is_open()) {
        std::cerr << "arcade: " << "highscore/Pacman" << ": No such file or directory" << std::endl;
        return;
    }
    std::getline(file, line);
    file.close();
    this->_highscore = line;
}

void Pacman::setHighscoreFile(std::string score)
{
    std::ofstream file;

    file.open("highscore/pacman");
    if (!file.is_open()) {
        std::cerr << "arcade: " << "highscore/Pacman" << ": No such file or directory" << std::endl;
        return;
    }
    file << score;
    file.close();
}

void Pacman::initGame()
{
    std::string line;
    std::ifstream file;

    this->map.clear();
    this->begin_map.clear();
    file.open("map/mapPacman");
    if (!file.is_open()) {
        std::cerr << "arcade: " << "map/mapPacman" << ": No such file or directory" << std::endl;
        return;
    }
    while (std::getline(file,line)) {
        this->map.push_back(line);
    }
    file.close();
    createOrigMap();
    createGhosts();
    this->_x = 0;
    this->_y = 0;
    gettimeofday(&this->_last, NULL);
    this->_score = 0;
    this->getHighscoreFile();
}

void Pacman::restartGame()
{
    std::string line;
    std::ifstream file;

    this->_score = 0;
    this->_x = 0;
    this->_y = 0;
    this->map.clear();
    this->begin_map.clear();
    file.open("map/mapPacman");
    if (!file.is_open()) {
        std::cerr << "arcade: " << "map/mapPacman" << ": No such file or directory" << std::endl;
        return;
    }
    while (std::getline (file,line)) {
        this->map.push_back(line);
    }
    file.close();
    createOrigMap();
    createGhosts();
    this->_x = 0;
    this->_y = 0;
    gettimeofday(&this->_last, NULL);
    this->getHighscoreFile();
}


/* Game events */

void Pacman::move(int x, int y)
{
    for (size_t i = 0; i < this->map.size(); i++) {
        for (size_t j = 0; j < this->map.at(i).size(); j++) {
            if (this->map.at(i).at(j) == 'P' && (i + x) < this->map.size() && (j + y) < this->map.at(i).size() && (i + x) >= 0 && (j + y) >= 0 && this->map.at(i + x).at(j + y) != '-' && this->map.at(i + x).at(j + y) != '|' && this->map.at(i + x).at(j + y) != '+' && this->map.at(i + x).at(j + y) != 'H') {
                if (this->map.at(i + x).at(j + y) == 'o') {
                    this->setScore(this->getScore() + 10);
                } else if (this->map.at(i + x).at(j + y) == 'O') {
                    this->setScore(this->getScore() + 10);
                    setFleeState();
                }
                this->map.at(i).at(j) = ' ';
                this->map.at(i + x).at(j + y) = 'P';
                if (isLost())
                    return;
                for (int i = 0; i < _ghosts.size(); i++) {
                    _ghosts.at(i)->move(map);
                }
                return;
            }
        }
    }
    if (isLost())
        return;
    for (int i = 0; i < _ghosts.size(); i++) {
        _ghosts.at(i)->move(map);
    }
}

void Pacman::setFleeState()
{
    for (int i = 0; i < _ghosts.size(); i++) {
        if (_ghosts.at(i)->getState() != 2 && _ghosts.at(i)->isIn()) {
            _ghosts.at(i)->setState(1);
            _ghosts.at(i)->incTime(50);
            _ghosts.at(i)->moveFlee(map);
        }
    }
}

void Pacman::setX(int x)
{
    this->_x = x;
}

void Pacman::setY(int y)
{
    this->_y = y;
}

int Pacman::getX()
{
    return (this->_x);
}

int Pacman::getY()
{
    return (this->_y);
}

void Pacman::setLast(struct timeval last)
{
    this->_last = last;
}

struct timeval Pacman::getLast()
{
    return (this->_last);
}

void Pacman::setScore(int score)
{
    this->_score = score;
}

int Pacman::getScore()
{
    return (this->_score);
}

bool Pacman::isWin()
{
    bool isWin = true;

    for (size_t i = 0; i < this->map.size(); i++) {
        for (size_t j = 0; j < this->map.at(i).size(); j++) {
            if (this->map.at(i).at(j) == 'o' || this->map.at(i).at(j) == 'O')
                isWin = false;
        }
    }
    return (isWin);
}

bool Pacman::isLost()
{
    std::string PacmanPosition;
    int x;
    int y;
    int len;

    if (!_ghosts.at(0))
        return (false);
    PacmanPosition = _ghosts.at(0)->findElementInMap(this->map, 'P');
    len = PacmanPosition.find(';');
    if (len == std::string::npos)
        return (false);
    x = std::stoi(PacmanPosition.substr(0, len));
    y = std::stoi(PacmanPosition.substr(len + 1));
    for (int i = 0; i < _ghosts.size(); i++) {
        if (_ghosts.at(i)->getX() == x && _ghosts.at(i)->getY() == y && _ghosts.at(i)->getState() == 0) {
            return (true);
        }
        else if (_ghosts.at(i)->getX() == x && _ghosts.at(i)->getY() == y && _ghosts.at(i)->getState() == 1) {
            _ghosts.at(i)->setState(2);
            setScore(getScore() + 100);
            return (false);
        }
    }
    return (false);
}