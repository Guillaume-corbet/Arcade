/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../../interface/IGames.hpp"

class Nibbler : public IGames {
    public:
        Nibbler();
        ~Nibbler();
        void createOrigMap();
        void createSnake();
        void createMovement();
        void createAnimationMap();
        void createSpritesNames();
        std::string getRotate(std::vector<std::string> map, int x, int y);
        int isAngle(int x, int y)const;
        char getSnakeRotate(int x, int y);
        std::string getSprite(std::vector<std::string> map, int x, int y);
        std::map<char, std::string> getSpritesNames();
        std::map<char, std::string> getAnimationMap();
        std::map<std::string, char> getMovements();
        std::vector<std::string> getMap() const;
        std::vector<std::vector<std::string>> getOrigMap() const;
        void initGame();
        void restartGame();
        void move(int x, int y);
        void PlaceFood();
        void eraseTail();
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
        std::vector<std::string> map_tmp;
        std::vector<std::vector<std::string>> begin_map;
        std::map<char, std::string> animationMap;
        std::map<char, std::string> _spritesNames;
        std::map<std::string,char> movements;
        std::vector<std::string> _snake;
        int _x;
        int _y;
        struct timeval _last;
        int _score;
        bool _isLost;
        bool _eraseTail;
        std::string _highscore;
};

extern "C"
{
    IGames *entryPoint()
    {
        return (new Nibbler());
    }
}

#endif /* !NIBBLER_HPP_ */