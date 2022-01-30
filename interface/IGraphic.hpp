/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** IGraphic
*/

#ifndef IGRAPHIC_HPP_
#define IGRAPHIC_HPP_

#include <string>
#include <vector>
#include <map>

class IGraphic {
    public:
        virtual ~IGraphic(){};
        virtual void setRotationMap(std::vector<std::vector<std::string>> rotationMap) = 0;
        virtual void setAnimationMap(std::map<char, std::string> animationMap) = 0;
        virtual void setSpritesNames(std::map<char, std::string> spritesNames) = 0;
        virtual void setMovementDirection(std::map<std::string, char> movement) = 0;
        virtual void startMenuGraphic() = 0;
        virtual int getEventGraphic() = 0;
        virtual int getEventPseudoGraphic() = 0;
        virtual void refreshGraphic() = 0;
        virtual bool isScreenTooSmallGraphic() = 0;
        virtual void endGraphic() = 0;
        virtual void displayMenuGraphic(int place, std::vector<std::string> *games) = 0;
        virtual void displayMenuPseudoGraphic(std::string name) = 0;
        virtual void displayScreenTooSmallGraphic() = 0;
        virtual void displayMap(std::vector<std::string> map) = 0;
        virtual int pause() = 0;
        virtual void displayScore(int score, std::string highscore) = 0;
        virtual void startGraphic() = 0;
        virtual void displayVictory(int score, int place, std::string name, std::string high) = 0;
        virtual void displayDefeat(int score, int place, std::string name, std::string high) = 0;
    protected:
    private:
};

#endif /* !IGRAPHIC_HPP_ */