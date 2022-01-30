/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** PinkGhost
*/

#ifndef PINKGHOST_HPP_
#define PINKGHOST_HPP_

#include "Ghost.hpp"

class PinkGhost: public Ghost {
    public:
        PinkGhost(char name);
        PinkGhost(char name, int x, int y);
        ~PinkGhost();
        void move(std::vector<std::string> map);
        void AI(std::vector<std::string> map);

    protected:
    private:
};

#endif /* !PINKGHOST_HPP_ */