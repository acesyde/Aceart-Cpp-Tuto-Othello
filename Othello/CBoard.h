#ifndef CBOARD_H
#define CBOARD_H

#define PIONW 78
#define PIONH 78

#include <SFML/Graphics.hpp>
#include <iostream>

#include "CPlayer.h"

using namespace std;

class CBoard
{
    public:
        CBoard();
        virtual ~CBoard();
        void InitGame();
        bool setJeton(int x, int y,CPlayer &humanPlayer, CPlayer &iaPlayer);
        void showJeton(int x, int y,sf::RenderWindow &App,CPlayer &humanPlayer, CPlayer &iaPlayer);
        void DrawBoard(sf::RenderWindow &App, CPlayer &humanPlayer, CPlayer &iaPlayer);
        void toggleScore();
        void togglePause();
        void setFin(bool);

        int GetScore(int);
        int getNbrPions();
        bool getPause();
        bool getFin();
        unsigned int getplayerTour();

        void setplayerTour(int playertour);
    private:
        int tab[8][8];
        unsigned int playerTour;

        bool score,pause,fin,tabClear;

        bool MoveIsValid(int posX,int posY,int playerID);
        bool gestionRetournement(int posX,int posY,int ecartX, int ecartY);
        bool EstValide(int x, int y);
        bool EstVide(int x, int y);
        bool jetonAutour(int, int);
        void DrawGrid(sf::RenderWindow &App);
        void DrawScore(sf::RenderWindow &App,CPlayer &humanPlayer, CPlayer &iaPlayer);
        void DrawFin(sf::RenderWindow &App,CPlayer &humanPlayer, CPlayer &iaPlayer);
		void clearBoard(int nbrP1, int nbrP2);
        sf::Sprite showPions(int x, int y,CPlayer &player);

        string GetScoreString(CPlayer &player);

        sf::Shape fond,fondScore;
        sf::Font maPolice;
        sf::Sprite tempJetons;
};

#endif // CBOARD_H
