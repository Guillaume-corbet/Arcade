/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "RedGhost.hpp"
#include "PinkGhost.hpp"
#include "OrangeGhost.hpp"
#include "BlueGhost.hpp"
#include "../../interface/IGames.hpp"

class Pacman : public IGames {
    public:
        Pacman();
        ~Pacman();
        void createGhosts();
        void createOrigMap();
        void createAnimationMap();
        void createSpritesNames();
        std::string getRotate(std::vector<std::string> map, int x, int y);
        std::string getSprite(std::vector<std::string> map, int x, int y);
        void upgradeMovements();
        std::map<std::string, char> getMovements();
        std::map<char, std::string> getSpritesNames();
        std::map<char, std::string> getAnimationMap();
        std::vector<std::string> getMap() const;
        std::vector<std::vector<std::string>> getOrigMap() const;
        void initGame();
        void restartGame();
        void move(int x, int y);
        void setFleeState();
        void setX(int x);
        void setY(int y);
        int getX();
        int getY();
        void setLast(struct timeval last);
        struct timeval getLast();
        void setScore(int score);
        int getScore();
        bool isWin();
        bool isLost();
        void getHighscoreFile();
        void setHighscoreFile(std::string highscore);
        std::string getHighscore();
        void setHighscore(std::string highscore);
    protected:
    private:
        std::vector<std::string> map;
        std::vector<std::vector<std::string>> begin_map;
        std::map<char, std::string> animationMap;
        std::map<char, std::string> _spritesNames;
        std::map<std::string,char> movements;
        int _x;
        int _y;
        struct timeval _last;
        int _score;
        std::vector<Ghost *> _ghosts;
        std::string _highscore;
};

extern "C"
{
    IGames *entryPoint()
    {
        return (new Pacman());
    }
}


#endif /* !PACMAN_HPP_ */