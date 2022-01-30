/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include "../include/Core.hpp"

Core::Core()
{
    this->_vecGraph = new std::vector<IGraphic *>;
    this->_vecGraphHandler = new std::vector<void *>;
    this->_vecGames = new std::vector<IGames *>;
    this->_vecGamesHandler = new std::vector<void *>;
    this->_name = "";
}

Core::~Core()
{
}

void Core::setName(const std::string &name)
{
    this->_name = name;
}

std::string Core::getName()
{
    return (this->_name);
}

void Core::setLib(std::string lib)
{
    this->_libName = lib;
}

std::vector<std::string> *Core::getAllGames()
{
    std::vector<std::string> *games = new std::vector<std::string>;
    DIR *dir = opendir("games");
    struct dirent *sd;
    std::string game;

    if (dir == NULL)
        return (NULL);
    while ((sd = readdir(dir)) != NULL) {
        game = std::string(sd->d_name);
        if (game.rfind("lib_arcade_", 0) == 0 && game.substr(game.size() - 3, game.size()) == ".so") {
            games->push_back(game.substr(11, game.size() - 3 - 11));
        }
    }
    return (games);
}

std::vector<std::string> *Core::getAllGraph(const char *lib)
{
    std::vector<std::string> *graphs = new std::vector<std::string>;
    DIR *dir = opendir("lib");
    struct dirent *sd;
    std::string graph;
    std::string libs;

    if (dir == NULL)
        return (NULL);
    libs = std::string(lib);
    libs = libs.substr(4, libs.size());
    graphs->push_back(libs.substr(11, libs.size() - 3 - 11));
    while ((sd = readdir(dir)) != NULL) {
        graph = std::string(sd->d_name);
        if (libs != graph && graph.rfind("lib_arcade_", 0) == 0 && graph.substr(graph.size() - 3, graph.size()) == ".so") {
            graphs->push_back(graph.substr(11, graph.size() - 3 - 11));
        }
    }
    return (graphs);
}

void Core::destroyHandler()
{
    while (this->_vecGamesHandler->size() > 0) {
        dlclose(this->_vecGamesHandler->at(0));
        this->_vecGamesHandler->erase(this->_vecGamesHandler->begin());
    }
    /*while (this->_vecGraphHandler->size() > 0) {
        dlclose(this->_vecGraphHandler->at(0));
        this->_vecGraphHandler->erase(this->_vecGraphHandler->begin());
    }*/
}

std::vector<IGraphic *> *Core::getVecGraph()
{
    return (this->_vecGraph);
}

void Core::checkSmallScreenMenu(IGraphic *graphique)
{
    int ch = 0;

    while (graphique->isScreenTooSmallGraphic()) {
        graphique->displayScreenTooSmallGraphic();
        ch = graphique->getEventGraphic();
        if (ch == 'q') {
            graphique->endGraphic();
            this->destroyHandler();
            exit(0);
        }
    }
}

void Core::checkSmallScreen(IGraphic *graphique)
{
    int ch = 0;

    while (graphique->isScreenTooSmallGraphic()) {
        graphique->displayScreenTooSmallGraphic();
        ch = graphique->getEventGraphic();
        if (ch == 'q') {
            graphique->endGraphic();
            this->destroyHandler();
            exit(0);
        }
    }
}

int Core::getScore(std::string highscore)
{
    size_t pos = 0;
    std::string high;

    pos = highscore.find(' ', 0);
    if (pos == std::string::npos)
        return (0);
    high = highscore.substr(pos, highscore.size() - pos);
    return (std::stoi(high));
}

void Core::menuEndGame(int place, int placeGraph, bool victory)
{
    int ch = 0;
    int fleche = 0;

    this->_vecGraph->at(placeGraph)->refreshGraphic();
    if (this->_vecGames->at(place)->getScore() > this->getScore(this->_vecGames->at(place)->getHighscore())) {
        this->_vecGames->at(place)->setHighscore(this->getName() + " " + std::to_string(this->_vecGames->at(place)->getScore()));
        this->_vecGames->at(place)->setHighscoreFile(this->getName() + " " + std::to_string(this->_vecGames->at(place)->getScore()));
    }
    while (1) {
        this->checkSmallScreen(this->_vecGraph->at(placeGraph));
        if (victory)
            this->_vecGraph->at(placeGraph)->displayVictory(this->_vecGames->at(place)->getScore(), fleche, this->getName(), this->_vecGames->at(place)->getHighscore());
        else
            this->_vecGraph->at(placeGraph)->displayDefeat(this->_vecGames->at(place)->getScore(), fleche, this->getName(), this->_vecGames->at(place)->getHighscore());
        ch = this->_vecGraph->at(placeGraph)->getEventGraphic();
        if (ch == 'q') {
            this->_vecGraph->at(placeGraph)->endGraphic();
            this->destroyHandler();
            exit(0);
        }  else if (ch == 'B' || ch == 's') {
            (fleche) = fleche + 1;
            if ((fleche) > 2)
                (fleche) = 0;
            this->_vecGraph->at(placeGraph)->refreshGraphic();
        } else if (ch == 'A' || ch == 'z') {
            (fleche) = fleche - 1;
            if ((fleche) < 0)
                (fleche) = 2;
            this->_vecGraph->at(placeGraph)->refreshGraphic();
        } else if (ch == '\n') {
            if (fleche == 0) {
                this->_vecGames->at(place)->restartGame();
                startGame(place, placeGraph);
            } else if (fleche == 1) {
                this->_vecGames->at(place)->initGame();
                this->menu(placeGraph);
            } else if (fleche == 2) {
                this->_vecGraph->at(placeGraph)->endGraphic();
                this->destroyHandler();
                exit(0);
            }
        }
    }
}

void Core::startGame(int place, int placeGraph)
{
    int ch = 0;
    struct timeval now;

    this->_vecGraph->at(placeGraph)->setSpritesNames(this->_vecGames->at(place)->getSpritesNames());
    this->_vecGraph->at(placeGraph)->setAnimationMap(this->_vecGames->at(place)->getAnimationMap());
    this->_vecGraph->at(placeGraph)->setRotationMap(this->_vecGames->at(place)->getOrigMap());
    this->_vecGraph->at(placeGraph)->refreshGraphic();
    while (1) {
        this->_vecGraph->at(placeGraph)->setMovementDirection(this->_vecGames->at(place)->getMovements());
        this->checkSmallScreen(this->_vecGraph->at(placeGraph));
        this->_vecGraph->at(placeGraph)->displayMap(this->_vecGames->at(place)->getMap());
        this->_vecGraph->at(placeGraph)->displayScore(this->_vecGames->at(place)->getScore(), this->_vecGames->at(place)->getHighscore());
        ch = this->_vecGraph->at(placeGraph)->getEventGraphic();
        if (ch == 'q') {
            this->_vecGraph->at(placeGraph)->endGraphic();
            this->destroyHandler();
            exit(0);
        } else if (ch == 'p') {
            this->_vecGraph->at(place)->pause();
        } else if (ch == 'B' || ch == 's') {
            this->_vecGames->at(place)->setX(1);
            this->_vecGames->at(place)->setY(0);
        } else if (ch == 'A' || ch == 'z') {
            this->_vecGames->at(place)->setX(-1);
            this->_vecGames->at(place)->setY(0);
        } else if (ch == 'D' || ch == 'a') {
            this->_vecGames->at(place)->setX(0);
            this->_vecGames->at(place)->setY(-1);
        } else if (ch == 'C' || ch == 'd') {
            this->_vecGames->at(place)->setX(0);
            this->_vecGames->at(place)->setY(1);
        } else if (ch == 'g') {
            place = place - 1;
            if (place < 0)
                place = this->_vecGames->size() - 1;
            this->_vecGames->at(place)->initGame();
            startGame(place, placeGraph);
        } else if (ch == 'h') {
            place = place + 1;
            if (place > this->_vecGames->size() - 1)
                place = 0;
            this->_vecGames->at(place)->initGame();
            startGame(place, placeGraph);
        } else if (ch == 't') {
            this->_vecGraph->at(placeGraph)->endGraphic();
            placeGraph = placeGraph - 1;
            if (placeGraph < 0)
                placeGraph = this->_vecGraph->size() - 1;
            this->_vecGraph->at(placeGraph)->startGraphic();
            this->_vecGraph->at(placeGraph)->setSpritesNames(this->_vecGames->at(place)->getSpritesNames());
            this->_vecGraph->at(placeGraph)->setAnimationMap(this->_vecGames->at(place)->getAnimationMap());
            this->_vecGraph->at(placeGraph)->setRotationMap(this->_vecGames->at(place)->getOrigMap());
        } else if (ch == 'y') {
            this->_vecGraph->at(placeGraph)->endGraphic();
            placeGraph = placeGraph + 1;
            if (placeGraph > this->_vecGraph->size() - 1)
                placeGraph = 0;
            this->_vecGraph->at(placeGraph)->startGraphic();
            this->_vecGraph->at(placeGraph)->setSpritesNames(this->_vecGames->at(place)->getSpritesNames());
            this->_vecGraph->at(placeGraph)->setAnimationMap(this->_vecGames->at(place)->getAnimationMap());
            this->_vecGraph->at(placeGraph)->setRotationMap(this->_vecGames->at(place)->getOrigMap());
        } else if (ch == 'r') {
            this->_vecGames->at(place)->initGame();
            startGame(place, placeGraph);
        } else if (ch == 'm') {
            this->_vecGames->at(place)->initGame();
            this->menu(placeGraph);
        }
        gettimeofday(&now, NULL);
        if ((((now.tv_sec) * 1000 + (now.tv_usec) / 1000) - ((this->_vecGames->at(place)->getLast().tv_sec) * 1000 + (this->_vecGames->at(place)->getLast().tv_usec) / 1000)) > 150) {
            this->_vecGames->at(place)->move(this->_vecGames->at(place)->getX(), this->_vecGames->at(place)->getY());
            this->_vecGames->at(place)->setLast(now);
            this->_vecGraph->at(placeGraph)->refreshGraphic();
            if (this->_vecGames->at(place)->isLost() && _name != "God") {
                menuEndGame(place, placeGraph, false);
            }
            else if (this->_vecGames->at(place)->isWin()) {
                menuEndGame(place, placeGraph, true);
            }
        }
    }
}

void Core::loadLib(char *lib)
{
    DLLoader<IGraphic> load;
    Loader loader;
    void *handler;

    loader.LoadAllGraph(lib);
    loader.LoadAllGames();
    this->_vecGames = loader.getVectorGames();
    this->_vecGamesHandler = loader.getVectorGamesHandler();
    this->_vecGraph = loader.getVectorGraph();
    this->_vecGraphHandler = loader.getVectorGraphHandler();
    this->_vecGraph->insert(this->_vecGraph->begin(), load.getInstance(lib, &handler));
    this->_vecGraphHandler->insert(this->_vecGraphHandler->begin(), handler);
}

void Core::menuPseudo(int placeGraph)
{
    char ch = 0;

    while (1) {
        checkSmallScreenMenu(this->_vecGraph->at(placeGraph));
        this->_vecGraph->at(placeGraph)->displayMenuPseudoGraphic(this->getName());
        ch = this->_vecGraph->at(placeGraph)->getEventPseudoGraphic();
        if (ch == '\t') {
            this->_vecGraph->at(placeGraph)->endGraphic();
            this->destroyHandler();
            exit(0);
        } else if (ch == '\n') {
            this->_vecGraph->at(placeGraph)->refreshGraphic();
            break;
        } else if ((ch > 64 && ch < 91) || (ch > 95 && ch < 123)) {
            this->setName(this->getName() + ch);
            this->_vecGraph->at(placeGraph)->refreshGraphic();
            ch = 0;
        }
    }
}

int Core::menuGraph(int placeGraph)
{
    int ch = 0;
    int tmpPlace = placeGraph;
    std::vector<std::string> *graph = this->getAllGraph(this->_libName.c_str());

    while (1) {
        checkSmallScreenMenu(this->_vecGraph->at(placeGraph));
        this->_vecGraph->at(placeGraph)->displayMenuGraphic(tmpPlace + 1, graph);
        ch = this->_vecGraph->at(placeGraph)->getEventGraphic();
        if (ch == 'q') {
            this->_vecGraph->at(placeGraph)->endGraphic();
            this->destroyHandler();
            exit(0);
        } else if (ch == 'B' || ch == 's') {
            (tmpPlace) = tmpPlace + 1;
            if ((tmpPlace) > graph->size())
                (tmpPlace) = 0;
            this->_vecGraph->at(placeGraph)->refreshGraphic();
        } else if (ch == 'A' || ch == 'z') {
            (tmpPlace) = tmpPlace - 1;
            if ((tmpPlace) < 0)
                (tmpPlace) = graph->size();
            this->_vecGraph->at(placeGraph)->refreshGraphic();
        } else if (ch == '\n') {
            if (tmpPlace == (graph->size())) {
                this->_vecGraph->at(placeGraph)->endGraphic();
                this->destroyHandler();
                exit(0);
            }
            if (tmpPlace != placeGraph) {
                this->_vecGraph->at(placeGraph)->endGraphic();
                placeGraph = tmpPlace;
                this->_vecGraph->at(placeGraph)->startGraphic();
            }
            this->_vecGraph->at(placeGraph)->refreshGraphic();
            break;
        }
    }
    return (placeGraph);
}

int Core::menu(int placeGraph)
{
    int place = 1;
    int ch = 0;
    std::vector<std::string> *games = this->getAllGames();

    this->_vecGraph->at(placeGraph)->refreshGraphic();
    this->setName("");
    this->menuPseudo(placeGraph);
    placeGraph = this->menuGraph(placeGraph);
    while (1) {
        checkSmallScreenMenu(this->_vecGraph->at(placeGraph));
        this->_vecGraph->at(placeGraph)->displayMenuGraphic(place, games);
        ch = this->_vecGraph->at(placeGraph)->getEventGraphic();
        if (ch == 'q') {
            this->_vecGraph->at(placeGraph)->endGraphic();
            this->destroyHandler();
            exit(0);
        } else if (ch == 'B' || ch == 's') {
            (place) = place + 1;
            if ((place) > games->size() + 1)
                (place) = 1;
            this->_vecGraph->at(placeGraph)->refreshGraphic();
        } else if (ch == 'A' || ch == 'z') {
            (place) = place - 1;
            if ((place) < 1)
                (place) = games->size() + 1;
            this->_vecGraph->at(placeGraph)->refreshGraphic();
        } else if (ch == '\n') {
            if (place == (games->size() + 1)) {
                this->_vecGraph->at(placeGraph)->endGraphic();
                this->destroyHandler();
                exit(0);
            }
            break;
        }
    }
    startGame(place - 1, placeGraph);
    return (0);
}