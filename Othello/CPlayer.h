#ifndef CPLAYER_H
#define CPLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class CPlayer
{
    public:
        CPlayer(string playerName, string imagePath, int playerID);
        virtual ~CPlayer();
        sf::Sprite & getSprite();
        unsigned int getPlayerId();
        void setPosition(sf::Vector2f position);
        string getPlayerName() { return playerName; };
    protected:
        sf::Sprite Sprite;
        sf::Image Image;
        string playerName;
        unsigned int playerID;

};

#endif // CPLAYER_H
