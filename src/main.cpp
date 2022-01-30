/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** main
*/

#include "../include/Core.hpp"

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 2) {
        std::cout << "Usage :" << std::endl;
        std::cout << "\t./arcade lib_arcade_graph.so" << std::endl;
        std::cout << "\tlib_arcade_graph.so doit hériter de l'interface IGraphic" << std::endl;
        std::cout << "\tLire doc/README.pdf" << std::endl;
        return (84);
    }
    Core *core = new Core;
    core->loadLib(argv[1]);
    core->setLib(std::string(argv[1]));
    core->getVecGraph()->at(0)->startMenuGraphic();
    core->menu(0);
    return (0);
}