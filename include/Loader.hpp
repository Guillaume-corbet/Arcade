/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Loader
*/

#ifndef LOADER_HPP_
#define LOADER_HPP_

#include <dirent.h>
#include <dlfcn.h>
#include <vector>
#include <map>
#include "../interface/IGraphic.hpp"
#include "../interface/IGames.hpp"
#include "../include/DLLoader.hpp"

class Loader {
    public:
        Loader();
        ~Loader();
        bool LoadAllGraph(char *lib);
        bool LoadAllGames();
        std::vector<IGraphic *> *getVectorGraph();
        std::vector<void *> *getVectorGraphHandler();
        std::vector<IGames *> *getVectorGames();
        std::vector<void *> *getVectorGamesHandler();
    protected:
    private:
        std::vector<IGraphic *> *_vecGraph;
        std::vector<void *> *_vecGraphHandler;
        std::vector<IGames *> *_vecGames;
        std::vector<void *> *_vecGamesHandler;
};

#endif /* !LOADER_HPP_ */
