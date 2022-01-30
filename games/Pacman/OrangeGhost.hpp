/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** OrangeGhost
*/

#ifndef ORANGEGHOST_HPP_
#define ORANGEGHOST_HPP_

#include "Ghost.hpp"

class OrangeGhost: public Ghost {
    public:
        OrangeGhost(char name);
        OrangeGhost(char name, int x, int y);
        ~OrangeGhost();
        void move(std::vector<std::string> map);
        void AI(std::vector<std::string> map);

    protected:
    private:
};

#endif /* !ORANGEGHOST_HPP_ */