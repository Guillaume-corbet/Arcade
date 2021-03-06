/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Ghost
*/

#include "Ghost.hpp"

Ghost::Ghost(char name):_name(name), _isDead(0), _direction(4)
{
}

Ghost::Ghost(char name, int x, int y):_name(name), _isDead(0), _direction(4), _x(x), _y(y), _x0(x), _y0(y), _getOut(false), _incTime(60)
{
}

Ghost::~Ghost()
{
}

std::string Ghost::checkIntersect(std::vector<std::string> map)
{
    std::string res = "";
    std::string toFind = " oOP1234mn";

    if (_isDead == 2 || (!_getOut && _incTime == 0))
        toFind += 'H';
    if (_x < map.at(_y).size() - 1 && strchr(toFind.c_str(), map.at(_y).at(_x + 1)) && _direction != direction::LEFT)
        res += '1';
    if (_y < map.size() - 1 && strchr(toFind.c_str(), map.at(_y + 1).at(_x)) && _direction != direction::TOP)
        res += '0';
    if (_x > 0 && strchr(toFind.c_str(), map.at(_y).at(_x - 1)) && _direction != direction::RIGHT)
        res += '3';
    if (_y > 0 && strchr(toFind.c_str(), map.at(_y - 1).at(_x)) && _direction != direction::BOT)
        res += '2';
    return (res);
}

std::string Ghost::checkAllIntersect(std::vector<std::string> map)
{
    std::string res = "";
    std::string toFind = " oOP1234mn";

    if (_isDead == 2 || (!_getOut && _incTime == 0))
        toFind += 'H';
    if (_x < map.at(_y).size() - 1 && strchr(toFind.c_str(), map.at(_y).at(_x + 1)))
        res += '1';
    if (_y < map.size() - 1 && strchr(toFind.c_str(), map.at(_y + 1).at(_x)))
        res += '0';
    if (_x > 0 && strchr(toFind.c_str(), map.at(_y).at(_x - 1)))
        res += '3';
    if (_y > 0 && strchr(toFind.c_str(), map.at(_y - 1).at(_x)))
        res += '2';
    return (res);
}

bool Ghost::checkCollision(std::vector<std::string> map, int direct)
{
    std::string toFind = " oOP1234mn";

    if (_isDead == 2 || (!_getOut && _incTime == 0))
        toFind += 'H';
    if (direct == direction::BOT && (_y >= map.size() - 1 || !strchr(toFind.c_str(), map.at(_y + 1).at(_x))))
        return (true);
    if (direct == direction::RIGHT && (_x >= map.at(_y).size() - 1 || !strchr(toFind.c_str(), map.at(_y).at(_x + 1))))
        return (true);
    if (direct == direction::TOP && (_y <=0 || !strchr(toFind.c_str(), map.at(_y - 1).at(_x))))
        return (true);
    if (direct == direction::LEFT && (_x <= 0 || !strchr(toFind.c_str(), map.at(_y).at(_x - 1))))
        return (true);
    return (false);
}

void Ghost::turn(std::vector<std::string> map)
{
    int nb = rand() % 2;

    if (!checkCollision(map, (_direction + 1) % 4) && !checkCollision(map, (_direction + 3) % 4))
        _direction = (_direction + (2 * nb) + 1) % 4;
    else if (!checkCollision(map, (_direction + 1) % 4))
        _direction = (_direction + 1) % 4;
    else if (checkCollision(map, (_direction + 1) % 4) && checkCollision(map, (_direction + 3) % 4))
        _direction = (_direction + 2) % 4;
    else
        _direction = (_direction + 3) % 4;
}

void Ghost::checkTimer()
{
    if (_incTime == 0) {
        _isDead = 0;
        return;
    }
    if (_isDead == 1 || _isDead == 0)
        _incTime--;
}

void Ghost::checkGetOut(std::vector<std::string> map)
{
    if (!_getOut) {
        std::string gatePos = findElementInMap(map, 'H');
        int nb = std::stoi(gatePos.substr(gatePos.find(';') + 1));
        if (_y < nb)
            _getOut = true;
    }
}

void Ghost::reachGate(std::vector<std::string> map)
{
    std::string gatePos = findElementInMap(map, 'H');
    int findGate = gatePos.find(';');
    int x = std::stoi(gatePos.substr(0, findGate));
    int y = std::stoi(gatePos.substr(findGate + 1));

    if (x > _x)
        _direction = 1;
    else if (x < _x)
        _direction = 3;
    else
        _direction = 2;
}

void Ghost::move(std::vector<std::string> map)
{
    std::string intersec = checkIntersect(map);
    int nb;

    checkTimer();
    checkGetOut(map);
    if (_incTime && _isDead == 0) {
        if (checkCollision(map, _direction)) {
            turn(map);
        }
        else if (intersec.size() > 1) {
            nb = rand() % (intersec.size());
            _direction = intersec.at(nb) - 48;
        }
    }
    else if (_isDead == 1) {
        if (intersec.size() > 1 || checkCollision(map, _direction))
            moveFlee(map);
        if (_incTime % 2 == 0)
            return;
    }
    else if (_isDead == 2) {
        if (checkCollision(map, _direction))
            turn(map);
        else if (intersec.size() > 1)
            moveDead(map);
    }
    else {
        if (!_getOut)
            reachGate(map);
        else if (intersec.size() > 1) {
            nb = rand() % (intersec.size());
            _direction = intersec.at(nb) - 48;
        }
        else if (checkCollision(map, _direction))
            turn(map);
    }
    if (_direction == direction::BOT)
        _y++;
    else if (_direction == direction::RIGHT)
        _x++;
    else if (_direction == direction::TOP)
        _y--;
    else if (_direction == direction::LEFT)
        _x--;
}

void Ghost::moveFlee(std::vector<std::string> map)
{
    std::string intersec = checkAllIntersect(map);
    std::string pacmanPosition = findElementInMap(map, 'P');
    int findPac = pacmanPosition.find(';');
    int diffX = abs(std::stoi(pacmanPosition.substr(0, findPac)) - _x);
    int diffY = abs(std::stoi(pacmanPosition.substr(findPac + 1)) - _y);
    std::string diffString;

    if (diffX < diffY) {
        if (std::stoi(pacmanPosition.substr(0, findPac)) > _x) {
            if (std::stoi(pacmanPosition.substr(findPac + 1)) > _y)
                diffString = "1023";
            else
                diffString = "1203";
        }
        else if (std::stoi(pacmanPosition.substr(0, findPac)) == _x) {
            if (std::stoi(pacmanPosition.substr(findPac + 1)) > _y)
                diffString = "0132";
            else
                diffString = "2310";
        }
        else {
            if (std::stoi(pacmanPosition.substr(findPac + 1)) > _y)
                diffString = "3021";
            else
                diffString = "3201";
        }
    }
    else {
        if (std::stoi(pacmanPosition.substr(findPac + 1)) > _y) {
            if (std::stoi(pacmanPosition.substr(0, findPac)) > _x)
                diffString = "0132";
            else
                diffString = "0312";
        }
        else if (std::stoi(pacmanPosition.substr(findPac + 1)) == _y) {
            if (std::stoi(pacmanPosition.substr(0, findPac)) < _x)
                diffString = "3021";
            else
                diffString = "1203";
        }
        else {
            if (std::stoi(pacmanPosition.substr(0, findPac)) > _x)
                diffString = "2130";
            else
                diffString = "2310";
        }
    }
    for (int i = 0; i < diffString.size(); i++) {
        if (strchr(intersec.c_str(), diffString.at(i)))
            _direction = diffString.at(i) - 48;
    }
}

void Ghost::moveDead(std::vector<std::string> map)
{
    std::string intersec = checkIntersect(map);
    std::string gatePos = findElementInMap(map, 'H');
    int findGate = gatePos.find(';');
    int diffX = abs(std::stoi(gatePos.substr(0, findGate)) - _x);
    int diffY = abs(std::stoi(gatePos.substr(findGate + 1)) - _y);
    std::string diffString;

    if (diffX == 0 && diffY == 1 && std::stoi(gatePos.substr(findGate + 1)) < _y) {
        _direction = 0;
        _isDead = 0;
        _getOut = false;
        incTime(60);
        return;
    }
    else if (diffX < diffY) {
        if (std::stoi(gatePos.substr(0, findGate)) < _x) {
            if (std::stoi(gatePos.substr(findGate + 1)) < _y)
                diffString = "0132";
            else
                diffString = "2130";
        }
        else if (std::stoi(gatePos.substr(0, findGate)) == _x) {
            if (std::stoi(gatePos.substr(findGate + 1)) < _y)
                diffString = "0132";
            else
                diffString = "2310";
        }
        else {
            if (std::stoi(gatePos.substr(findGate + 1)) < _y)
                diffString = "0312";
            else
                diffString = "2310";
        }
    }
    else {
        if (std::stoi(gatePos.substr(findGate + 1)) < _y) {
            if (std::stoi(gatePos.substr(0, findGate)) < _x)
                diffString = "1023";
            else
                diffString = "3021";
        }
        else if (std::stoi(gatePos.substr(findGate + 1)) == _y) {
            if (std::stoi(gatePos.substr(0, findGate)) < _x)
                diffString = "1203";
            else
                diffString = "3021";
        }
        else {
            if (std::stoi(gatePos.substr(0, findGate)) < _x)
                diffString = "1203";
            else
                diffString = "3201";
        }
    }
    for (int i = 0; i < diffString.size(); i++) {
        if (strchr(intersec.c_str(), diffString.at(i)))
            _direction = diffString.at(i) - 48;
    }
}

std::string Ghost::findElementInMap(std::vector<std::string> map, char c)const
{
    std::string res;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.at(i).size(); j++) {
            if (map.at(i).at(j) == c) {
                res = std::to_string(j) + ";" + std::to_string(i);
            }
        }
    }
    return (res);
}

void Ghost::setXBegin(int x)
{
    _x0 = x;
    _x = x;
}

void Ghost::setYBegin(int y)
{
    _y0 = y;
    _y = y;
}

char Ghost::getName()const
{
    return (_name);
}

void Ghost::setState(int value)
{
    _isDead = value;
}

int Ghost::getState()const
{
    return (_isDead);
}

void Ghost::setTime(int value)
{
    _incTime = value;
}

void Ghost::incTime(int value)
{
    _incTime += value;
}

int Ghost::getTime()const
{
    return (_incTime);
}

bool Ghost::isIn()const
{
    return (_getOut);
}

void Ghost::setX(int x)
{
    _x = x;
}

void Ghost::setY(int y)
{
    _y = y;
}

int Ghost::getX()const
{
    return (_x);
}

int Ghost::getY()const
{
    return (_y);
}

int Ghost::getDirection()const
{
    return (_direction);
}