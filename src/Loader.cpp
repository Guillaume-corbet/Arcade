/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Loader
*/

#include "../include/Loader.hpp"

Loader::Loader()
{
    this->_vecGraph = new std::vector<IGraphic *>;
    this->_vecGraphHandler = new std::vector<void *>;
    this->_vecGames = new std::vector<IGames *>;
    this->_vecGamesHandler = new std::vector<void *>;
}

Loader::~Loader()
{
}

bool Loader::LoadAllGraph(char *lib)
{
    DIR *dir = opendir("lib");
    struct dirent *sd;
    std::string graph;
    DLLoader<IGraphic> load;
    void *handler;

    if (dir == NULL)
        return (false);
    while ((sd = readdir(dir)) != NULL) {
        graph = "lib/" + std::string(sd->d_name);
        if (strcmp(graph.c_str(),lib) != 0 && graph.rfind("lib/lib_arcade_", 0) == 0 && graph.substr(graph.size() - 3, graph.size()) == ".so") {
            this->_vecGraph->push_back(load.getInstance(graph.c_str(), &handler));
            this->_vecGraphHandler->push_back(handler);
        }
    }
    return (true);
}

bool Loader::LoadAllGames()
{
    DIR *dir = opendir("games");
    struct dirent *sd;
    std::string games;
    DLLoader<IGames> load;
    void *handler;

    if (dir == NULL)
        return (false);
    while ((sd = readdir(dir)) != NULL) {
        games = "games/" + std::string(sd->d_name);
        if (games.rfind("games/lib_arcade_", 0) == 0 && games.substr(games.size() - 3, games.size()) == ".so") {
            this->_vecGames->push_back(load.getInstance(games.c_str(), &handler));
            this->_vecGamesHandler->push_back(handler);
            this->_vecGames->at(this->_vecGames->size() - 1)->initGame();
        }
    }
    return (true);
}

std::vector<IGraphic *> *Loader::getVectorGraph()
{
    return (this->_vecGraph);
}

std::vector<void *> *Loader::getVectorGraphHandler()
{
    return (this->_vecGraphHandler);
}

std::vector<IGames *> *Loader::getVectorGames()
{
    return (this->_vecGames);
}

std::vector<void *> *Loader::getVectorGamesHandler()
{
    return (this->_vecGamesHandler);
}