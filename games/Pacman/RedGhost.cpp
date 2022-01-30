/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** RedGhost
*/

#include "RedGhost.hpp"

RedGhost::RedGhost(char name): Ghost(name)
{
    _incTime = 20;
}

RedGhost::RedGhost(char name, int x, int y): Ghost(name, x, y)
{
    _incTime = 20;
}

RedGhost::~RedGhost()
{
}

void RedGhost::move(std::vector<std::string> map)
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
        if (checkCollision(map, _direction))
            turn(map);
        else if (intersec.size() > 1)
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
        else if (intersec.size() > 1)
            AI(map);
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

void RedGhost::AI(std::vector<std::string> map)
{
    std::string intersec = checkAllIntersect(map);
    std::string pacmanPos = findElementInMap(map, 'P');
    int findPac = pacmanPos.find(';');
    int x = std::stoi(pacmanPos.substr(0, findPac));
    int y = std::stoi(pacmanPos.substr(findPac + 1));
    int diffX = abs(x - _x);
    int diffY = abs(y - _y);
    std::string diffString;

    if (diffX < diffY) {
        if (x < _x) {
            if (y < _y)
                diffString = "0132";
            else
                diffString = "2130";
        }
        else if (x == _x) {
            if (y < _y)
                diffString = "0132";
            else
                diffString = "2310";
        }
        else {
            if (y < _y)
                diffString = "0312";
            else
                diffString = "2310";
        }
    }
    else {
        if (y < _y) {
            if (x < _x)
                diffString = "1023";
            else
                diffString = "3021";
        }
        else if (y == _y) {
            if (x < _x)
                diffString = "1203";
            else
                diffString = "3021";
        }
        else {
            if (x < _x)
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