/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Ghost
*/

#ifndef GHOST_HPP_
#define GHOST_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <bits/stdc++.h> 
#include <sys/time.h> 

class Ghost {
    public:
        enum direction {BOT, RIGHT, TOP, LEFT};
        Ghost(char name);
        Ghost(char name, int x, int y);
        ~Ghost();
        std::string checkIntersect(std::vector<std::string> map);
        std::string checkAllIntersect(std::vector<std::string> map);
        bool checkCollision(std::vector<std::string> map, int direct);
        void turn(std::vector<std::string> map);
        void checkTimer();
        void checkGetOut(std::vector<std::string> map);
        void reachGate(std::vector<std::string> map);
        virtual void move(std::vector<std::string> map);
        void moveFlee(std::vector<std::string> map);
        void moveDead(std::vector<std::string> map);
        std::string findElementInMap(std::vector<std::string> map, char c)const;
        void setXBegin(int x);
        void setYBegin(int y);
        char getName()const;
        void setState(int value);
        int getState()const;
        void setTime(int value);
        void incTime(int value);
        int getTime()const;
        bool isIn()const;
        void setX(int x);
        void setY(int y);
        int getX()const;
        int getY()const;
        int getDirection()const;
    protected:
        char _name;
        int _isDead;
        int _direction;
        int _x;
        int _y;
        int _x0;
        int _y0;
        bool _getOut;
        size_t _incTime;
    private:
};

/* 
    0: ghost is going toward bottom
    1: ghost is going toward right
    2: ghost is going toward top
    3: ghost is going toward left
*/

#endif /* !GHOST_HPP_ */