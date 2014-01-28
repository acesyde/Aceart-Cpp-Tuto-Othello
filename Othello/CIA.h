#ifndef CIA_H
#define CIA_H

#include "CPlayer.h"
#include "CBoard.h"


using namespace std;

class CIA : public CPlayer
{
    public:
        CIA(string playerName, string imagePath, int playerID);
        virtual ~CIA();
        void InitIA();
        bool VerifMax(int x,int y);
        void AfficherTableMax();

        int getmaxY();
        int getmaxX();
    private:
        int MinMax[8][8];

        int max;
        int maxX;
        int maxY;
};

#endif // CIA_H
