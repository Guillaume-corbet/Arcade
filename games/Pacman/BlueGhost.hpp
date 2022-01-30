/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** BlueGhost
*/

#ifndef BLUEGHOST_HPP_
#define BLUEGHOST_HPP_

#include "Ghost.hpp"

class BlueGhost: public Ghost {
    public:
        BlueGhost(char name);
        BlueGhost(char name, int x, int y);
        ~BlueGhost();

    protected:
    private:
};

#endif /* !BLUEGHOST_HPP_ */