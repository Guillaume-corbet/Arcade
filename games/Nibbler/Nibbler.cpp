/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

Nibbler::Nibbler()
{
    createAnimationMap();
    createSpritesNames();
    _isLost = false;
}

Nibbler::~Nibbler()
{
}


/* creation */

void Nibbler::createOrigMap()
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
    createSnake();
}

void Nibbler::createSnake()
{
    int x = -1;
    int y;
    int last = -1;

    _snake.clear();
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.at(i).size(); j++) {
            if (map.at(i).at(j) == 'o') {
                x = j;
                y = i;
            }
        }
    }
    if (x != -1) {
        while (map.at(y).at(x) != '8') {
            _snake.push_back(std::to_string(y) + ";" + std::to_string(x));
            if (x > 0 && strchr("8Oo", map.at(y).at(x - 1)) && last != 2) {
                last = 0;
                x--;
            }
            if (y > 0 && strchr("8Oo", map.at(y - 1).at(x)) && last != 3) {
                last = 1;
                y--;
            }
            if (x < map.at(y).size() - 1 && strchr("8Oo", map.at(y).at(x + 1)) && last != 0) {
                last = 2;
                x++;
            }
            if (y < map.size() - 1 && strchr("8Oo", map.at(y + 1).at(x)) && last != 1) {
                last = 3;
                y++;
            }
        }
        _snake.push_back(std::to_string(y) + ";" + std::to_string(x));
    }
}

void Nibbler::createAnimationMap()
{
    animationMap.insert(std::pair<char, std::string>('8', "21"));
    animationMap.insert(std::pair<char, std::string>('O', "21"));
    animationMap.insert(std::pair<char, std::string>('o', "21"));
    animationMap.insert(std::pair<char, std::string>('0', "21"));
}

void Nibbler::createSpritesNames()
{
    _spritesNames.insert(std::pair<char, std::string>('+', "games/Nibbler/sprites/big_angle_nibbler.png"));
    _spritesNames.insert(std::pair<char, std::string>('-', "games/Nibbler/sprites/simple_wall_nibbler.png"));
    _spritesNames.insert(std::pair<char, std::string>('|', "games/Nibbler/sprites/simple_wall_nibbler.png"));
    _spritesNames.insert(std::pair<char, std::string>('x', "games/Nibbler/sprites/point_nibbler.png"));
    _spritesNames.insert(std::pair<char, std::string>('n', ""));
    _spritesNames.insert(std::pair<char, std::string>('m', ""));
    _spritesNames.insert(std::pair<char, std::string>('B', "games/Nibbler/sprites/background_nibbler.jpg"));
    _spritesNames.insert(std::pair<char, std::string>('8', "games/Nibbler/sprites/head_nibbler.png"));
    _spritesNames.insert(std::pair<char, std::string>('O', "games/Nibbler/sprites/body_nibbler.png"));
    _spritesNames.insert(std::pair<char, std::string>('o', "games/Nibbler/sprites/tail_nibbler.png"));
    _spritesNames.insert(std::pair<char, std::string>('0', "games/Nibbler/sprites/body_angle_nibbler.png"));
}

std::string Nibbler::getRotate(std::vector<std::string> map, int x, int y)
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
        if ((y > 0 && (map.at(y - 1).at(x) == 'O' || map.at(y - 1).at(x) == 'x')) || (y < map.size() - 1 && strchr("n1234-+", map.at(y + 1).at(x))))
            rotate = "3";
    }
    else if (current == '|') {
        rotate = "0";
        if ((x > 0 && (map.at(y).at(x - 1) == 'O' || map.at(y).at(x - 1) == 'x')) || (x < map.at(y).size() - 1 && strchr("n1234|+", map.at(y).at(x + 1))))
            rotate = "2";
    }
    return (rotate);
}

int Nibbler::isAngle(int x, int y)const
{
    for (int nb = 1; nb < _snake.size() - 1; nb++) {
        if (_snake.at(nb) == (std::to_string(y) + ";" + std::to_string(x))) {
            if (_snake.at(nb - 1) == (std::to_string(y) + ";" + std::to_string(x - 1)) && _snake.at(nb + 1) == (std::to_string(y + 1) + ";" + std::to_string(x)))
                return (1);
            else if (_snake.at(nb - 1) == (std::to_string(y + 1) + ";" + std::to_string(x)) && _snake.at(nb + 1) == (std::to_string(y) + ";" + std::to_string(x - 1)))
                return (1);
            else if (_snake.at(nb - 1) == (std::to_string(y) + ";" + std::to_string(x + 1)) && _snake.at(nb + 1) == (std::to_string(y + 1) + ";" + std::to_string(x)))
                return (0);
            else if (_snake.at(nb - 1) == (std::to_string(y + 1) + ";" + std::to_string(x)) && _snake.at(nb + 1) == (std::to_string(y) + ";" + std::to_string(x + 1)))
                return (0);
            else if (_snake.at(nb - 1) == (std::to_string(y) + ";" + std::to_string(x - 1)) && _snake.at(nb + 1) == (std::to_string(y - 1) + ";" + std::to_string(x)))
                return (2);
            else if (_snake.at(nb - 1) == (std::to_string(y - 1) + ";" + std::to_string(x)) && _snake.at(nb + 1) == (std::to_string(y) + ";" + std::to_string(x - 1)))
                return (2);
            else if (_snake.at(nb - 1) == (std::to_string(y) + ";" + std::to_string(x + 1)) && _snake.at(nb + 1) == (std::to_string(y - 1) + ";" + std::to_string(x)))
                return (3);
            else if (_snake.at(nb - 1) == (std::to_string(y - 1) + ";" + std::to_string(x)) && _snake.at(nb + 1) == (std::to_string(y) + ";" + std::to_string(x + 1)))
                return (3);
        }
    }
    return (-1);
}

char Nibbler::getSnakeRotate(int x, int y)
{
    if (isAngle(x, y) != -1) {
        map_tmp.at(y).at(x) = '0';
        return (isAngle(x, y) + 48);
    }
    for (int nb = 0; nb < _snake.size(); nb++) {
        if (_snake.at(nb) == (std::to_string(y) + ";" + std::to_string(x))) {
            if ((nb > 0 && _snake.at(nb - 1) == (std::to_string(y - 1) + ";" + std::to_string(x))) || (nb != _snake.size() - 1 && _snake.at(nb + 1) == (std::to_string(y - 1) + ";" + std::to_string(x))))
                return ('3');
            else if ((nb > 0 && _snake.at(nb - 1) == (std::to_string(y + 1) + ";" + std::to_string(x))) || (nb != _snake.size() - 1 && _snake.at(nb + 1) == (std::to_string(y + 1) + ";" + std::to_string(x))))
                return ('1');
            else if ((nb > 0 && _snake.at(nb - 1) == (std::to_string(y) + ";" + std::to_string(x + 1))) || (nb != _snake.size() - 1 && _snake.at(nb + 1) == (std::to_string(y) + ";" + std::to_string(x + 1))))
                return ('0');
            else if ((nb > 0 && _snake.at(nb - 1) == (std::to_string(y) + ";" + std::to_string(x - 1))) || (nb != _snake.size() - 1 && _snake.at(nb + 1) == (std::to_string(y) + ";" + std::to_string(x - 1))))
                return ('2');
        }
    }
}

std::string Nibbler::getSprite(std::vector<std::string> map, int x, int y)
{
    std::string res;

    for (std::map<char, std::string>::iterator ite = _spritesNames.begin(); ite != _spritesNames.end(); ite++) {
        if (ite->first == map.at(y).at(x)) {
            if (map.at(y).at(x) == '+' && ((y == 0 || !strchr("xm", map.at(y - 1).at(x))) && (x == 0 || !strchr("xm", map.at(y).at(x - 1))) && (y >= map.size() - 1 || !strchr("xm", map.at(y + 1).at(x))) && (x >= map.at(y).size() - 1 || !strchr("xm", map.at(y).at(x + 1)))))
                res = "";
            else
                res = ite->second;
        }
    }
    return (res);
}

std::map<char, std::string> Nibbler::getSpritesNames()
{
    return (_spritesNames);
}

std::map<char, std::string> Nibbler::getAnimationMap()
{
    return (animationMap);
}

std::string Nibbler::getHighscore()
{
    return (this->_highscore);
}

void Nibbler::setHighscore(std::string highscore)
{
    this->_highscore = highscore;
}

std::map<std::string, char> Nibbler::getMovements()
{
    char mov;

    map_tmp = map;
    movements.clear();
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.at(i).size(); j++) {
            if (strchr("8Oo", map.at(i).at(j))) {
                mov = getSnakeRotate(j, i);
                movements.insert(std::pair<std::string, char>(std::to_string(j) + ", " + std::to_string(i), mov));
            }
        }
    }
    return (movements);
}

std::vector<std::string> Nibbler::getMap() const
{
    if (!map_tmp.empty())
        return (map_tmp);
    return (map);
}

std::vector<std::vector<std::string>> Nibbler::getOrigMap() const
{
    return (this->begin_map);
}


/* Game initialisation */

void Nibbler::getHighscoreFile()
{
    std::string line;
    std::ifstream file;

    file.open("highscore/nibbler");
    if (!file.is_open()) {
        std::cerr << "arcade: " << "highscore/nibbler" << ": No such file or directory" << std::endl;
        return;
    }
    std::getline(file, line);
    file.close();
    this->_highscore = line;
}

void Nibbler::setHighscoreFile(std::string score)
{
    std::ofstream file;

    file.open("highscore/nibbler");
    if (!file.is_open()) {
        std::cerr << "arcade: " << "highscore/nibbler" << ": No such file or directory" << std::endl;
        return;
    }
    file << score;
    file.close();
}

void Nibbler::initGame()
{
    std::string line;
    std::ifstream file;

    this->map.clear();
    this->begin_map.clear();
    file.open("map/mapNibbler");
    if (!file.is_open()) {
        std::cerr << "arcade: " << "mapNibbler" << ": No such file or directory" << std::endl;
        return;
    }
    while (std::getline (file,line)) {
        this->map.push_back(line);
    }
    file.close();
    createOrigMap();
    PlaceFood();
    this->_x = 0;
    this->_y = 0;
    gettimeofday(&this->_last, NULL);
    this->_score = 0;
    _isLost = false;
}

void Nibbler::restartGame()
{
    std::string line;
    std::ifstream file;

    this->_score = 0;
    this->_x = 0;
    this->_y = 0;
    this->map.clear();
    this->begin_map.clear();
    file.open("map/mapNibbler");
    if (!file.is_open()) {
        std::cerr << "arcade: " << "mapNibbler" << ": No such file or directory" << std::endl;
        return;
    }
    while (std::getline (file,line)) {
        this->map.push_back(line);
    }
    file.close();
    createOrigMap();
    PlaceFood();
    this->_x = 0;
    this->_y = 0;
    gettimeofday(&this->_last, NULL);
    _isLost = false;
}


/* Game events */

void Nibbler::move(int x, int y)
{
    _eraseTail = true;
    for (size_t i = 0; i < this->map.size(); i++) {
        for (size_t j = 0; j < this->map.at(i).size(); j++) {
            if (this->map.at(i).at(j) == '8' && (i + x) < this->map.size() && (j + y) < this->map.at(i).size() && (i + x) >= 0 && (j + y) >= 0) {
                if (this->map.at(i + x).at(j + y) == 'x') {
                    this->setScore(this->getScore() + 10);
                    PlaceFood();
                    _eraseTail = false;
                } else if (this->map.at(i + x).at(j + y) == 'O' || this->map.at(i + x).at(j + y) == 'o' || this->map.at(i + x).at(j + y) == '-' || this->map.at(i + x).at(j + y) == '|' || this->map.at(i + x).at(j + y) == '+') {
                    _isLost = true;
                    return;
                }
                this->map.at(i).at(j) = 'O';
                this->map.at(i + x).at(j + y) = '8';
                if ((std::to_string(i + x) + ";" + std::to_string(j + y)) != _snake.at(_snake.size() - 1))
                    _snake.push_back(std::to_string(i + x) + ";" + std::to_string(j + y));
                eraseTail();
                return;
            }
        }
    }
}

void Nibbler::PlaceFood()
{
    int countSpaces = 0;
    int nb;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.at(i).size(); j++) {
            if (map.at(i).at(j) == ' ')
                countSpaces++;
        }
    }
    nb = rand() % countSpaces;
    countSpaces = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.at(i).size(); j++) {
            if (map.at(i).at(j) && map.at(i).at(j) == ' ')
                countSpaces++;
            if (countSpaces == nb) {
                map.at(i).at(j) = 'x';
                return;
            }
        }
    }
}

void Nibbler::eraseTail()
{
    int x;
    int y;

    if (_x == 0 && _y == 0)
        return;
    if (!_eraseTail) {
        _eraseTail = true;
    }
    else {
        x = std::stoi(_snake.at(0).substr(0, _snake.at(0).find(';')));
        y = std::stoi(_snake.at(0).substr(_snake.at(0).find(';') + 1));
        map.at(x).at(y) = ' ';
        _snake.erase(_snake.begin() + 0);
        x = std::stoi(_snake.at(0).substr(0, _snake.at(0).find(';')));
        y = std::stoi(_snake.at(0).substr(_snake.at(0).find(';') + 1));
        map.at(x).at(y) = 'o';
    }
    return;
}

void Nibbler::setX(int x)
{
    this->_x = x;
}

void Nibbler::setY(int y)
{
    this->_y = y;
}

int Nibbler::getX()
{
    return (this->_x);
}

int Nibbler::getY()
{
    return (this->_y);
}

void Nibbler::setLast(struct timeval last)
{
    this->_last = last;
}

struct timeval Nibbler::getLast()
{
    return (this->_last);
}

void Nibbler::setScore(int score)
{
    this->_score = score;
}

int Nibbler::getScore()
{
    return (this->_score);
}

bool Nibbler::isWin()
{
    bool isWin = true;
    bool isThereFood = false;

    for (size_t i = 0; i < this->map.size(); i++) {
        for (size_t j = 0; j < this->map.at(i).size(); j++) {
            if (this->map.at(i).at(j) == ' ')
                isWin = false;
            else if (this->map.at(i).at(j) == 'x')
                isThereFood = true;
        }
    }
    if (!isThereFood)
        PlaceFood();
    return (isWin);
}

bool Nibbler::isLost()
{
    return (_isLost);
}