#include "CIA.h"

using namespace std;

CIA::CIA(string playerName, string imagePath, int playerID) : CPlayer(playerName,imagePath,playerID)
{
    InitIA();
}

// Initialisation de l'Intelligence artificielle
void CIA::InitIA()
{
	maxX = maxY = 0;
	
	//Initialisation du tableau pour les Cibles max
    MinMax[0][0]=500;    MinMax[0][1]=-150;     MinMax[0][2]=30;    MinMax[0][3]=10;
    MinMax[0][4]=10;    MinMax[0][5]=30;    MinMax[0][6]=-150;    MinMax[0][7]=500;
    MinMax[1][0]=500;    MinMax[1][1]=-150;     MinMax[1][2]=30;    MinMax[1][3]=10;
    MinMax[1][4]=10;    MinMax[1][5]=30;    MinMax[1][6]=-150;    MinMax[1][7]=500;
    MinMax[2][0]=500;    MinMax[2][1]=-150;     MinMax[2][2]=30;    MinMax[2][3]=10;
    MinMax[2][4]=10;    MinMax[2][5]=30;    MinMax[2][6]=-150;    MinMax[2][7]=500;
    MinMax[3][0]=500;    MinMax[3][1]=-150;     MinMax[3][2]=30;    MinMax[3][3]=10;
    MinMax[3][4]=10;    MinMax[3][5]=30;    MinMax[3][6]=-150;    MinMax[3][7]=500;
    MinMax[4][0]=500;    MinMax[4][1]=-150;     MinMax[4][2]=30;    MinMax[4][3]=10;
    MinMax[4][4]=10;    MinMax[4][5]=30;    MinMax[4][6]=-150;    MinMax[4][7]=500;
    MinMax[5][0]=500;    MinMax[5][1]=-150;     MinMax[5][2]=30;    MinMax[5][3]=10;
    MinMax[5][4]=10;    MinMax[5][5]=30;    MinMax[5][6]=-150;    MinMax[5][7]=500;
    MinMax[6][0]=500;    MinMax[6][1]=-150;     MinMax[6][2]=30;    MinMax[6][3]=10;
    MinMax[6][4]=10;    MinMax[6][5]=30;    MinMax[6][6]=-150;    MinMax[6][7]=500;
    MinMax[7][0]=500;    MinMax[7][1]=-150;     MinMax[7][2]=30;    MinMax[7][3]=10;
    MinMax[7][4]=10;    MinMax[7][5]=30;    MinMax[7][6]=-150;    MinMax[7][7]=500;

    max = -999;

	//    int MinMax[8][8]= {{500,-150,30,10,10,30,-150,500},
	//               { -150,-250,0,0,0,0,-250,-150 },
	//               { 30,0,1,2,2,1,0,30 },
	//               { 10,0,2,16,16,2,0,10 },
	//               { 10,0,2,16,16,2,0,10 },
	//               { 30,0,1,2,2,1,0,30 },
	//               { -150,-250,0,0,0,0,-250,-150 },
	//               { 500,-150,30,10,10,30,-150,500 }
	//            };
}

// destructeur
CIA::~CIA()
{

}

// Modifie les valeurs de maxX et maxY selon le maximum trouvé
bool CIA::VerifMax(int x,int y)
{
    if(maxX != x || maxY != y){
        if( MinMax[x][y] >= max ){
            max = MinMax[x][y];
            return true;
        }
    maxX = x;
    maxY = y;
    }
    return false;
}

// Affiche le tableau des max en mode console
void CIA::AfficherTableMax(){
     for(int x=0 ; x<8 ; x++){
        for(int y=0 ; y<8 ; y++){
            cout << "["<<MinMax[x][y]<<"]";
        }
        cout << endl;
     }
}

// Retourne le x max choisi
int CIA::getmaxX(){
    return maxX;
}

// Retourne le y max choisi
int CIA::getmaxY(){
    return maxY;
}
