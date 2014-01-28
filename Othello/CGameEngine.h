#ifndef CGAMEENGINE_H
#define CGAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "CBoard.h"

#include "CJoueur.h"
#include "CIA.h"

#include "CViewManager.h"

using namespace std;

class CGameEngine
{
    public:
        CGameEngine();
        virtual ~CGameEngine();
        bool GameLoop();
    private:
        CViewManager *managerView;

        CBoard *maTable;
        sf::RenderWindow * App;
        sf::Font myFont;

        const sf::Input * Input;
        sf::Event Event;

        void InitGameEngine();
        void InitPlayer();
        void InitViewManager();

        bool LancerIA();

        void DrawMenu();
        void takeScreenShot();

        float CenterText(float textWidth);

        CJoueur * humanPlayer;
        CIA * iaPlayer;
};

#endif // CGAMEENGINE_H
