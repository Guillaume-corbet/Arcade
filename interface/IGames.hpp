/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGames
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

#include <bits/stdc++.h> 
#include <sys/time.h>

class IGames {
    public:
        virtual ~IGames(){};
        virtual std::vector<std::string> getMap() const = 0;
        virtual std::vector<std::vector<std::string>> getOrigMap() const = 0;
        virtual void move(int x, int y) = 0;
        virtual std::map<std::string, char> getMovements() = 0;
        virtual std::map<char, std::string> getSpritesNames() = 0;
        virtual std::map<char, std::string> getAnimationMap() = 0;
        virtual void setX(int x) = 0;
        virtual void setY(int y) = 0;
        virtual int getX() = 0;
        virtual int getY() = 0;
        virtual void setLast(struct timeval last) = 0;
        virtual struct timeval getLast() = 0;
        virtual int getScore() = 0;
        virtual bool isWin() = 0;
        virtual bool isLost() = 0;
        virtual void initGame() = 0;
        virtual void restartGame() = 0;
        virtual void getHighscoreFile() = 0;
        virtual void setHighscoreFile(std::string highscore) = 0;
        virtual std::string getHighscore() = 0;
        virtual void setHighscore(std::string highscore) = 0;
    protected:
    private:
};

#endif /* !IGAMES_HPP_ */
