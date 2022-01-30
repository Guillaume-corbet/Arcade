/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** BlueGhost
*/

#include "BlueGhost.hpp"

BlueGhost::BlueGhost(char name): Ghost(name)
{
    _incTime = 30;
}

BlueGhost::BlueGhost(char name, int x, int y): Ghost(name, x, y)
{
    _incTime = 30;
}

BlueGhost::~BlueGhost()
{
}