/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>
#include <bits/stdc++.h>
#include <sys/time.h>
#include "../interface/IGraphic.hpp"
#include "../interface/IGames.hpp"
#include "../include/DLLoader.hpp"
#include "../include/Loader.hpp"

class Core {
    public:
        Core();
        ~Core();
        void setName(const std::string &name);
        std::string getName();
        void loadLib(char *lib);
        void menuPseudo(int placeGraph);
        int menuGraph(int placeGraph);
        int menu(int placeGraph);
        void setLib(std::string lib);
        void destroyHandler();
        std::vector<IGraphic *> *getVecGraph();
        int getScore(std::string highscore);
    protected:
        std::vector<std::string> *getAllGames();
        std::vector<std::string> *getAllGraph(const char *lib);
        void loadOneGraph(const char *lib);
        void loadAllGraph(char *lib);
        void loadOneGames(const char *lib);
        void loadAllGames();
        void checkSmallScreenMenu(IGraphic *graphique);
        void startGame(int place, int placeGraph);
        void checkSmallScreen(IGraphic *graphique);
        void menuEndGame(int place, int placeGraph, bool victory);
    private:
        std::string _name;
        std::vector<IGraphic *> *_vecGraph;
        std::vector<void *> *_vecGraphHandler;
        std::vector<IGames *> *_vecGames;
        std::vector<void *> *_vecGamesHandler;
        std::string _libName;
};

#endif /* !CORE_HPP_ */