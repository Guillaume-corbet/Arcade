/*
** EPITECH PROJECT, 2020
** delivery
** File description:
** Sfml
*/

#include "Sfml.hpp"

/* Class */

Sfml::Sfml()
{
    _spriteSize = 100;
    _clock = sf::Clock();
    createKeysEvents();
}

Sfml::~Sfml()
{
}


/* Start */

void Sfml::startGraphic()
{
    _window.create(sf::VideoMode(1920, 1080), "Arcade", sf::Style::Resize | sf::Style::Close);
    _window.setFramerateLimit(30);
    _windowSize = _window.getSize();
}

void Sfml::createKeysEvents()
{
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Up, 'z'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Down, 's'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Left, 'a'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Right, 'd'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Z, 'z'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::S, 's'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::A, 'a'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::D, 'd'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::T, 't'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Y, 'y'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::G, 'g'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::H, 'h'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Return, '\n'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Escape, 'q'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::P, 'p'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::Q, 'q'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::R, 'r'));
    _evtKeys.insert(std::pair<sf::Keyboard::Key, char>(sf::Keyboard::M, 'm'));
}

void Sfml::setRotationMap(std::vector<std::vector<std::string>> rotationMap)
{
    _RotateMap = rotationMap;
}

void Sfml::setAnimationMap(std::map<char, std::string> animationMap)
{
    sf::IntRect rect;

    _animationMap = animationMap;
    _clock.restart();
    if (animationMap.empty())
        return;
    for (std::map<char, std::string>::iterator ite = _animationMap.begin(); ite != _animationMap.end(); ite++) {
        if (ite->second.at(0) == '1' || ite->second.at(0) == '2')
            rect = {0, 0, _spriteSize, _spriteSize};
        else
            rect = {_spriteSize * (ite->second.at(1) - 48), 0, _spriteSize, _spriteSize};
        _rectAnimation.insert(std::pair<char, sf::IntRect>(ite->first, rect));
    }
}

void Sfml::setSpritesNames(std::map<char, std::string> spritesNames)
{
    _spritesNames = spritesNames;
}

void Sfml::setMovementDirection(std::map<std::string, char> movement)
{
    _movement = movement;
}


/* Events */

int Sfml::getEventGraphic()
{
    int ch = 0;
    sf::Event evt;

    while (_window.pollEvent(evt)) { 
        if (evt.type == sf::Event::Closed)
            return ('q');
        else if (evt.type == sf::Event::KeyPressed)
            ch = _evtKeys[evt.key.code];
    }
    return (ch);
}

int Sfml::getEventPseudoGraphic()
{
    int ch = 0;
    sf::Event evt;

    while (_window.pollEvent(evt)) { 
        if (evt.type == sf::Event::Closed)
            return ('\t');
        else if (evt.type == sf::Event::TextEntered) {
            ch = evt.text.unicode;
            if (ch == 13)
                ch = 10;
        }
    }
    return (ch);
}

void Sfml::refreshGraphic()
{
    _window.clear(sf::Color::Black);
}

bool Sfml::isScreenTooSmallGraphic()
{
    if (_window.getSize().x <= 400 || _window.getSize().y <= 400) {
        return (true);
    }
    return (false);
}

void Sfml::displayScreenTooSmallGraphic()
{
    sf::Text text;
    sf::Font font;

    _window.clear(sf::Color::Black);
    font.loadFromFile("lib/sprites/flotta.otf");
    text.setFont(font);
    text.setString("window is too small");
    text.setOrigin(0.5 * text.getGlobalBounds().width, 0.5 * text.getGlobalBounds().height);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color(0, 0, 0, 255));
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(3);
    text.setPosition({float(_windowSize.x / 2), float(_windowSize.y / 2)});
    _window.draw(text);
    _window.display();
}

int Sfml::pause()
{
    sf::Event evt;
    sf::Text text;
    sf::Font font;

    font.loadFromFile("lib/sprites/flotta.otf");
    text.setFont(font);
    text.setString("PAUSE\nPress P again to continue");
    text.setOrigin(0.5 * text.getGlobalBounds().width, 0.5 * text.getGlobalBounds().height);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color(0, 0, 0, 255));
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(3);
    text.setPosition({float(_windowSize.x / 2), float(_windowSize.y / 2)});
    while (1) {
        while (_window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed || (evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::Q)) {
                endGraphic();
                exit(0);
            }
            else if (evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::P) {
                return (0);
            }
        }
        refreshGraphic();
        _window.draw(text);
        _window.display();
    }
    return (0);
}

void Sfml::endGraphic()
{
    _window.close();
}


/* Menu */

void Sfml::startMenuGraphic()
{
    _window.create(sf::VideoMode(1920, 1080), "Arcade", sf::Style::Resize | sf::Style::Close);
    _window.setFramerateLimit(30);
    _windowSize = _window.getSize();
}

void Sfml::displayMenuGraphic(int place, std::vector<std::string> *map)
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f pos_tmp = {0, 0};
    sf::Text text;
    sf::FloatRect bounds;
    sf::Font font;
    std::vector<std::string> map_cpy = *map;
    float beginPos;
    float endPos;
    float pos;
    float ResizeCoeff;

    _window.clear(sf::Color::Black);
    texture.loadFromFile("lib/sprites/background_menu.png");
    sprite.setTexture(texture);
    bounds = sprite.getGlobalBounds();
    ResizeCoeff = std::min(float(_windowSize.y / (bounds.height)), float(_windowSize.x / (bounds.width)));
    sprite.setScale({ResizeCoeff, ResizeCoeff});
    bounds = sprite.getGlobalBounds();
    pos_tmp = {(_windowSize.x - bounds.width) / 2, (_windowSize.y - bounds.height) / 2};
    sprite.setPosition(pos_tmp);
    _window.draw(sprite);

    beginPos = float(0.3 * bounds.height);
    endPos = float(0.9 * bounds.height);
    pos = beginPos;
    map_cpy.push_back("Exit");
    for (int i = 0; i < map_cpy.size(); i++) {
        pos_tmp = {float(bounds.width * 0.35), pos};
        font.loadFromFile("lib/sprites/flotta.otf");
        text.setFont(font);
        text.setString(map_cpy.at(i));
        text.setCharacterSize(100);
        text.setFillColor(sf::Color(0, 0, 0, 255));
        text.setOutlineColor(sf::Color::White);
        text.setOutlineThickness(3);
        text.setPosition(pos_tmp);
        _window.draw(text);
        if (i == place - 1) {
            texture.loadFromFile("lib/sprites/crosshair.png");
            sprite.setTexture(texture);
            sprite.setScale({ResizeCoeff, ResizeCoeff});
            sprite.setPosition({pos_tmp.x + (float(0.33) * bounds.width), pos_tmp.y + (text.getGlobalBounds().height / 2)});
            _window.draw(sprite);
        }
        pos += float((endPos - beginPos) / (map_cpy.size()));
    }
    _window.display();
}

void Sfml::displayMenuPseudoGraphic(std::string name)
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::FloatRect bounds;
    float ResizeCoeff;
    sf::Text text;
    sf::Font font;
    sf::Vector2f pos_tmp;

    texture.loadFromFile("lib/sprites/background_menu.png");
    sprite.setTexture(texture);
    bounds = sprite.getGlobalBounds();
    ResizeCoeff = std::min(float(_windowSize.y / (bounds.height)), float(_windowSize.x / (bounds.width)));
    sprite.setScale({ResizeCoeff, ResizeCoeff});
    bounds = sprite.getGlobalBounds();
    pos_tmp = {(_windowSize.x - bounds.width) / 2, (_windowSize.y - bounds.height) / 2};
    sprite.setPosition(pos_tmp);
    _window.draw(sprite);
    font.loadFromFile("lib/sprites/flotta.otf");
    text.setFont(font);
    text.setString("Enter your name");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color(0, 0, 0, 255));
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(3);
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(_windowSize.x / 2, _windowSize.y / 2 - 100);
    _window.draw(text);
    text.setString(name);
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(_windowSize.x / 2, _windowSize.y / 2 + 50);
    _window.draw(text);
    _window.display();
}

/* Display game */

int Sfml::setNbRotate(std::vector<std::string> map, int x, int y)
{
    std::string cur;
    
    if (_RotateMap.empty())
        return (0);
    cur = _RotateMap.at(y).at(x);
    cur = cur.substr(cur.find(';') + 1);
    if (!cur.empty())
        return (std::stoi(cur));
    else if (!(_animationMap[map.at(y).at(x)].empty()) && _animationMap[map.at(y).at(x)].at(0) == '2') {
        return (getMovementDirection(std::to_string(x) + ", " + std::to_string(y)));
    }else
        return (0);
}

std::string Sfml::setSprite(std::vector<std::string> map, int x, int y)
{
    std::string cur;

    if (_RotateMap.empty())
        return (getSpriteName(map.at(y).at(x)));
    cur = _RotateMap.at(y).at(x);
    if (!cur.empty())
        return (cur.substr(0, cur.find(';')));
    else
        return (getSpriteName(map.at(y).at(x)));
}

std::string Sfml::getSpriteName(char c)
{
    std::string res;

    if (_spritesNames.empty())
        return (res);
    for (std::map<char, std::string>::iterator ite = _spritesNames.begin(); ite != _spritesNames.end(); ite++) {
        if (ite->first == c) {
            res = ite->second;
        }
    }
    return (res);
}

int Sfml::getMovementDirection(std::string pos)
{
    if (!(_movement[pos]))
        return (0);
    return (_movement[pos] - 48);
}

sf::IntRect Sfml::animate(std::vector<std::string> map, int x, int y)
{
    int value = 0;
    static int last = 0;
    sf::Time time = _clock.getElapsedTime();
    float sec = time.asMilliseconds() / 1000;
    sf::IntRect rect = {0, 0, 100, 100};
    std::string animationInfo;

    if (_animationMap.empty())
        return (rect);
    animationInfo = _animationMap[map.at(y).at(x)];
    if (sec > 0.5)
        value = _spriteSize;
    if (animationInfo.empty())
        return (rect);
    else if (animationInfo.at(0) == '0')
        return (_rectAnimation[map.at(y).at(x)]);
    else if (animationInfo.at(0) == '1') {
        value = getMovementDirection(std::to_string(x) + ", " + std::to_string(y)) * _spriteSize * 2 + value;
        if (value > animationInfo.at(1) * _spriteSize)
            rect = {0, 0, _spriteSize,_spriteSize};
        else
            rect = {value, 0, _spriteSize, _spriteSize};
        return (rect);
    }
    else {
        if (value != last) {
            last = value;
            (_rectAnimation[map.at(y).at(x)]).left += _spriteSize;
            if (_rectAnimation[map.at(y).at(x)].left >= _spriteSize * ((animationInfo.at(1) - 48)))
                _rectAnimation[map.at(y).at(x)].left = 0;
        }
        return (_rectAnimation[map.at(y).at(x)]);
    }
}

void Sfml::displayMap(std::vector<std::string> map)
{
    int x = 0;
    int y = 0;
    int posx = -1;
    int posy = -1;
    int SpriteResize;
    int adjustx;
    int adjusty;
    sf::Texture texture;
    sf::Sprite sprite;

    _ResizeCoeff = 1;
    if (_spriteSize * map.size() > _windowSize.y || _spriteSize * map.at(0).size() > _windowSize.x) {
        _ResizeCoeff = std::min(float(float(_windowSize.y) / float(map.size() * _spriteSize)), float(float(_windowSize.x) / float(map.at(0).size() * _spriteSize + 200)));
        if (_spriteSize * map.size() > _windowSize.y)
            posy = 0;
        if (_spriteSize * map.at(0).size() > _windowSize.x)
            posx = 0;
        SpriteResize = (_ResizeCoeff * _spriteSize);
    }
    if (posx == -1)
        posx = (_windowSize.x - 400 - (map.at(0).size() * (SpriteResize))) / 2;
    if (posy == -1)
        posy = (_windowSize.y - (map.size() * (SpriteResize))) / 2;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.at(i).size(); j++) {
            if (!setSprite(map, j, i).empty()) {
                adjustx = 0;
                adjusty = 0;
                texture.loadFromFile(setSprite(map, j, i));
                sprite.setTexture(texture);
                sprite.setTextureRect(animate(map, j, i));
                sprite.setScale({_ResizeCoeff, _ResizeCoeff});
                sprite.setRotation(setNbRotate(map, j, i) * 90);
                if (setNbRotate(map, j, i) == 1 || setNbRotate(map, j, i) == 2)
                    adjustx = SpriteResize;
                if (setNbRotate(map, j, i) == 2 || setNbRotate(map, j, i) == 3)
                    adjusty = SpriteResize;
                sprite.setPosition({float(x + posx + adjustx), float(y + posy + adjusty)});
                _window.draw(sprite);
            }
            x += SpriteResize;
        }
        x = posx;
        y += SpriteResize;
    }
    resetClock();
}

void Sfml::resetClock()
{
    if (_clock.getElapsedTime().asMilliseconds() / 1000 > 1)
        _clock.restart();
}

void Sfml::displayScore(int score, std::string highscore)
{
    sf::Text text;
    sf::Font font;
    int nb = 10;

    if (!_RotateMap.empty())
        nb = _RotateMap.at(0).size();
    font.loadFromFile("lib/sprites/flotta.otf");
    text.setFont(font);
    text.setString("Score: " + std::to_string(score));
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition((_windowSize.x + nb * _spriteSize * _ResizeCoeff) / 2 - 10, _windowSize.y / 2);
    _window.draw(text);
    _window.display();
}

void Sfml::displayVictory(int score, int place, std::string name, std::string high)
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Sprite background;
    sf::Text text;
    sf::Font font;
    float nb;

    if (getSpriteName('B').empty()) {
        texture.loadFromFile(getSpriteName('B'));
        background.setTexture(texture);
        nb = std::min(float(_windowSize.x / background.getGlobalBounds().width), float(_windowSize.y / background.getGlobalBounds().height));
        background.setOrigin({background.getGlobalBounds().width / 2, background.getGlobalBounds().height / 2});
        background.setPosition({float(_windowSize.x / 2), float(_windowSize.y / 2)});
        background.setScale({nb, nb});
        _window.draw(background);
    }
    font.loadFromFile("lib/sprites/flotta.otf");
    text.setFont(font);
    text.setString("Score: " + std::to_string(score) + "\nHighscore: " + high);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(3 * _windowSize.x / 4, _windowSize.y / 5 + 100);
    _window.draw(text);
    text.setString("VICTORY");
    text.setCharacterSize(120);
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(_windowSize.x / 3, _windowSize.y / 5);
    _window.draw(text);
    text.setString(name);
    text.setCharacterSize(60);
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(3 * _windowSize.x / 4, _windowSize.y / 5);
    _window.draw(text);
    text.setString("Continuer");
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(_windowSize.x / 2, 3 * _windowSize.y / 6);
    _window.draw(text);
    text.setString("Menu");
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(_windowSize.x / 2, 4 * _windowSize.y / 6);
    _window.draw(text);
    text.setString("Exit");
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(_windowSize.x / 2, 5 * _windowSize.y / 6);
    _window.draw(text);
    texture.loadFromFile("lib/sprites/crosshair.png");
    sprite.setTexture(texture);
    sprite.setOrigin({sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2});
    sprite.setPosition(3 * _windowSize.x / 4, (3 + place) * _windowSize.y / 6 + 30);
    _window.draw(sprite);
    _window.display();
}

void Sfml::displayDefeat(int score, int place, std::string name, std::string high)
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Sprite background;
    sf::Text text;
    sf::Font font;
    float nb;

    if (getSpriteName('B').empty()) {
        texture.loadFromFile(getSpriteName('B'));
        background.setTexture(texture);
        nb = std::min(float(_windowSize.x / background.getGlobalBounds().width), float(_windowSize.y / background.getGlobalBounds().height));
        background.setOrigin({background.getGlobalBounds().width / 2, background.getGlobalBounds().height / 2});
        background.setPosition({float(_windowSize.x / 2), float(_windowSize.y / 2)});
        background.setScale({nb, nb});
        _window.draw(background);
    }
    font.loadFromFile("lib/sprites/flotta.otf");
    text.setFont(font);
    text.setString("Score: " + std::to_string(score) + "\nHighscore: " + high);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(3 * _windowSize.x / 4, _windowSize.y / 5 + 100);
    _window.draw(text);
    text.setString("DEFEAT");
    text.setCharacterSize(120);
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(_windowSize.x / 3, _windowSize.y / 5);
    _window.draw(text);
    text.setString(name);
    text.setCharacterSize(60);
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(3 * _windowSize.x / 4, _windowSize.y / 5);
    _window.draw(text);
    text.setString("Continuer");
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(_windowSize.x / 2, 3 * _windowSize.y / 6);
    _window.draw(text);
    text.setString("Menu");
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(_windowSize.x / 2, 4 * _windowSize.y / 6);
    _window.draw(text);
    text.setString("Exit");
    text.setOrigin({text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2});
    text.setPosition(_windowSize.x / 2, 5 * _windowSize.y / 6);
    _window.draw(text);
    texture.loadFromFile("lib/sprites/crosshair.png");
    sprite.setTexture(texture);
    sprite.setOrigin({sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2});
    sprite.setPosition(3 * _windowSize.x / 4, (3 + place) * _windowSize.y / 6 + 30);
    _window.draw(sprite);
    _window.display();
}