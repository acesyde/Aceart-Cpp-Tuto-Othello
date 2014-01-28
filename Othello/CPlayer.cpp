#include "CPlayer.h"

CPlayer::CPlayer(string playerName, string imagePath, int playerID)
{
    this->playerName = playerName;
    this->playerID = playerID;

    if(!Image.LoadFromFile(imagePath)) {
        cout << "Impossible de charger l'image" << endl;
    }

    Image.SetSmooth(true);
    Image.CreateMaskFromColor(sf::Color::Magenta);
    Sprite.SetImage(Image);

}

CPlayer::~CPlayer()
{
    //dtor
}

sf::Sprite & CPlayer::getSprite() {
    return Sprite;
}

unsigned int CPlayer::getPlayerId() {
    return playerID;
}

void CPlayer::setPosition(sf::Vector2f position) {
    Sprite.SetPosition(position);
}
