/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <string>
#include <iostream>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "../../interface/IGraphic.hpp"

class Sfml: public IGraphic {
    public:
        Sfml();
        ~Sfml();
        void startGraphic();
        void createKeysEvents();
        void setRotationMap(std::vector<std::vector<std::string>> rotationMap);
        void setAnimationMap(std::map<char, std::string> animationMap);
        void setSpritesNames(std::map<char, std::string> spritesNames);
        void setMovementDirection(std::map<std::string, char> movement);
        int getEventGraphic();
        int getEventPseudoGraphic();
        void refreshGraphic();
        bool isScreenTooSmallGraphic();
        void displayScreenTooSmallGraphic();
        int pause();
        void endGraphic();
        void startMenuGraphic();
        void displayMenuGraphic(int place, std::vector<std::string> *games);
        void displayMenuPseudoGraphic(std::string name);
        int setNbRotate(std::vector<std::string> map, int x, int y);
        std::string setSprite(std::vector<std::string> map, int x, int y);
        std::string getSpriteName(char c);
        int getMovementDirection(std::string pos);
        sf::IntRect animate(std::vector<std::string> map, int x, int y);
        void displayMap(std::vector<std::string> map);
        void resetClock();
        void displayScore(int score, std::string highscore);
        void displayVictory(int score, int place, std::string name, std::string high);
        void displayDefeat(int score, int place, std::string name, std::string high);

    protected:
    private:
        std::vector<std::vector<std::string>> _RotateMap;
        std::map<char, std::string> _spritesNames;
        std::map<char, std::string> _animationMap;
        std::map<std::string, char> _movement;
        std::map<char, sf::IntRect> _rectAnimation;
        sf::Vector2u _windowSize;
        float _ResizeCoeff;
        sf::RenderWindow _window;
        int _spriteSize;
        sf::Clock _clock;
        std::map<sf::Keyboard::Key, char> _evtKeys;
};

extern "C"
{
    IGraphic *entryPoint()
    {
        return (new Sfml());
    }
}

#endif /* !SFML_HPP_ */