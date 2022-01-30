/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** RedGhost
*/

#ifndef REDGHOST_HPP_
#define REDGHOST_HPP_

#include "Ghost.hpp"

class RedGhost: public Ghost {
    public:
        RedGhost(char name);
        RedGhost(char name, int x, int y);
        ~RedGhost();
        void move(std::vector<std::string> map);
        void AI(std::vector<std::string> map);

    protected:
    private:
};

#endif /* !REDGHOST_HPP_ */