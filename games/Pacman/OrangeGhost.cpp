/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** OrangeGhost
*/

#include "OrangeGhost.hpp"

OrangeGhost::OrangeGhost(char name): Ghost(name)
{
    _incTime = 30;
}

OrangeGhost::OrangeGhost(char name, int x, int y): Ghost(name, x, y)
{
    _incTime = 30;
}

OrangeGhost::~OrangeGhost()
{
}

void OrangeGhost::move(std::vector<std::string> map)
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

void OrangeGhost::AI(std::vector<std::string> map)
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