#ifndef CJOUEUR_H
#define CJOUEUR_H

#include "CPlayer.h"

class CJoueur : public CPlayer
{
    public:
        CJoueur(string playerName, string imagePath, int playerID);
        virtual ~CJoueur();
    private:
};

#endif // CJOUEUR_H
