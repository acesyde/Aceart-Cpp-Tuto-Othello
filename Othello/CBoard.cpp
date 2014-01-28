#include "CBoard.h"
#include <sstream>

CBoard::CBoard()
{
    InitGame();
    fond = sf::Shape::Rectangle(0,0,624,624,sf::Color(0,0,0,100));
    fondScore = sf::Shape::Rectangle(0,580,624,624,sf::Color(0,0,0,150));
}

CBoard::~CBoard()
{

}

// Initialisation du jeux
void CBoard::InitGame() {
    // Chargement du fond du plateau

    // Initialisation du plateau
    for(int y=0;y<8;y++) {
        for(int x=0;x<8;x++) {
            tab[x][y] = 0;
        }
    }

    // Mise en place des jetons
    tab[3][3]=1;
    tab[4][3]=2;
    tab[3][4]=2;
    tab[4][4]=1;

    playerTour = 1;

    score = false;
    pause = false;
    fin = false;
	tabClear = false;
}

// change le mode d'affichage en mode score
void CBoard::toggleScore() {
    score = !score;

}

// change le mode de jeux en pause
void CBoard::togglePause() {
    pause = !pause;
}

// change de mode de jeu en fin
void CBoard::setFin(bool state) {
    fin = state;
}

// retourne si le jeux est en pause
bool CBoard::getPause() {
    return pause;
}

bool CBoard::getFin() {
    return fin;
}

// dessin de la grille
void CBoard::DrawGrid(sf::RenderWindow &App) {
    for (int y=0;y<8;y++) {
        sf::Shape ligneY = sf::Shape::Line(0,y*78,624,y*78,1.f,sf::Color::Black);
        App.Draw(ligneY);
    }

    for (int x=0;x<8;x++) {
        sf::Shape ligneX = sf::Shape::Line(x*78,0,x*78,624,1.f,sf::Color::Black);
        App.Draw(ligneX);
    }
}

// dessin des scores
void CBoard::DrawScore(sf::RenderWindow &App,CPlayer &humanPlayer, CPlayer &iaPlayer) {
    App.Draw(fondScore);

    sf::String PlayerOneText(GetScoreString( humanPlayer ),sf::Font::GetDefaultFont(),30);
    sf::String PlayerTwoText(GetScoreString( iaPlayer ),sf::Font::GetDefaultFont(),30);
    PlayerOneText.SetPosition(0,580);
    PlayerTwoText.SetPosition(App.GetWidth()-PlayerTwoText.GetRect().GetWidth(),580);

    App.Draw(PlayerOneText);
    App.Draw(PlayerTwoText);

}

void CBoard::DrawFin(sf::RenderWindow &App,CPlayer &humanPlayer, CPlayer &iaPlayer) {
    
	clearBoard(humanPlayer.getPlayerId(),iaPlayer.getPlayerId());
	
	App.Draw(fond);

	sf::String winText;
	winText.SetFont(sf::Font::GetDefaultFont());
	winText.SetSize(30);

	if(GetScore(humanPlayer.getPlayerId()) > GetScore(iaPlayer.getPlayerId())) {
		winText.SetText("Winner : " + humanPlayer.getPlayerName());
	} else {
		winText.SetText("Winner : " + iaPlayer.getPlayerName());
	}

	winText.SetPosition(App.GetWidth()/3,App.GetHeight()/2-winText.GetRect().GetHeight());

    App.Draw(winText);
}

// Affiche le pions au passage de la souris
void CBoard::showJeton(int x, int y,sf::RenderWindow &App,CPlayer &humanPlayer, CPlayer &iaPlayer) {
    int posX = x/PIONW;
    int posY = y/PIONH;

    if(tab[posX][posY] == 0) {
        if(playerTour == humanPlayer.getPlayerId()) {
            humanPlayer.setPosition(sf::Vector2f(posX*78,posY*78));
            App.Draw(humanPlayer.getSprite());
        } else {
            iaPlayer.setPosition(sf::Vector2f(posX*78,posY*78));
            App.Draw(iaPlayer.getSprite());
        }
    }
}


// Ajout d'un pion sur la table
bool CBoard::setJeton(int x, int y, CPlayer &humanPlayer, CPlayer &iaPlayer) {

    if( !getPause() ) {
        int posX = x/PIONW;
        int posY = y/PIONH;

        if(MoveIsValid(posX,posY,playerTour)) {
            if(playerTour == humanPlayer.getPlayerId()) {
                tab[posX][posY]=humanPlayer.getPlayerId();
                playerTour = 2;
                return true;
            } else if(playerTour == iaPlayer.getPlayerId()) {

                tab[posX][posY]=iaPlayer.getPlayerId();
                playerTour = 1;
                return true;
            }
        }
    }
    return false;
}


// Verifie la validité du coup
bool CBoard::MoveIsValid(int posX,int posY,int playerID) {

    if(tab[posX][posY] != 0){
        return false;
    }
    // Si il n'y a aucuns jetons autour alors on renvois faux
    if(!jetonAutour(posX,posY)) {
        return false;
    }

    // Teste les jetons
    bool resultat = false;
    // Lignes
    resultat |= gestionRetournement(posX,posY,1,0);
    resultat |= gestionRetournement(posX,posY,-1,0);

    // Colonnes
    resultat |= gestionRetournement(posX,posY,0,1);
    resultat |= gestionRetournement(posX,posY,0,-1);

    // Diagonales
    resultat |= gestionRetournement(posX,posY,1,1);
    resultat |= gestionRetournement(posX,posY,-1,-1);
    resultat |= gestionRetournement(posX,posY,-1,1);
    resultat |= gestionRetournement(posX,posY,1,-1);

    return resultat;
}

// Verifie si il y a un jeton autour
bool CBoard::jetonAutour(int posX, int posY) {
    bool jetonAutour = false;

    // Verification des bords du plateau
    int debutX,finX,debutY,finY;

    if(posX == 0) {
        debutX=posX;
    } else {
        debutX=posX-1;
    }

    if(posX == 7) {
        finX=posX;
    } else {
        finX=posX+2;
    }

    if(posY == 0) {
        debutY=posY;
    } else {
        debutY=posY-1;
    }

    if(posY == 7) {
        finY=posY;
    } else {
        finY=posY+2;
    }

    // Verifie les jetons autour
    for(int y=debutY;y<finY;y++) {
        for(int x=debutX;x<finX;x++) {
            if(tab[x][y] != 0)
                jetonAutour = true;
        }
    }

    return jetonAutour;
}


// Fonctions de testes diagonales / Horizontales / Verticales
bool CBoard::gestionRetournement(int posX, int posY,int ecartX, int ecartY) {

    int x,y,i;
    x = posX;
    y = posY;
    i=0;

    do {
        i++;
        posX+=ecartX;
        posY+=ecartY;
    } while(EstValide(posX,posY) && !EstVide(posX,posY) && playerTour != tab[posX][posY]);

    if(EstValide(posX,posY) && !EstVide(posX,posY) && i > 1) {
        while(i>1) {
            x+=ecartX;
            y+=ecartY;
            tab[x][y] = playerTour;
            i--;
        }
        return true;
    }

    return false;
}

// vérifie la validité du pion
bool CBoard::EstValide(int x, int y)
{
    return x < 8 && x >= 0 && y >= 0 && y < 8;
}

// Verifie si la case est vide
bool CBoard::EstVide(int x, int y) {
    if(tab[x][y] != 0)
        return false;
    return true;
}

// Affiche le pion sous le pointeur de la souris
sf::Sprite CBoard::showPions(int x, int y,CPlayer &player) {
        sf::Sprite Sprite;
        Sprite = player.getSprite();
        Sprite.SetPosition(x*PIONW,y*PIONH);
        return Sprite;
}

// Dessin de la table
void CBoard::DrawBoard(sf::RenderWindow &App,CPlayer &humanPlayer, CPlayer &iaPlayer) {

    DrawGrid(App);

    for(int y=0;y<8;y++) {
        for(int x=0;x<8;x++) {
            if(tab[x][y] == humanPlayer.getPlayerId())
                App.Draw( showPions(x,y,humanPlayer) );
            if(tab[x][y] == iaPlayer.getPlayerId())
                App.Draw( showPions(x,y,iaPlayer) );

        }
    }

	(getNbrPions() == 64)?setFin(true):setFin(false);

    if(getPause()) {
        App.Draw(fond);
        sf::String pauseText("GAME PAUSED",sf::Font::GetDefaultFont(),30);
        App.Draw(pauseText);
    }

    if(score && !getPause()) {
        DrawScore(App,humanPlayer,iaPlayer);
    }

    if(getFin()){
        DrawFin(App,humanPlayer,iaPlayer);
    }

}

// Retourne la chaine de caracteres contenant le score du joueur
string CBoard::GetScoreString(CPlayer &player) {
        ostringstream oss;
        string tmpString;

        oss << GetScore(player.getPlayerId());

        tmpString = player.getPlayerName() + " : " + oss.str();

        return tmpString;
}

// Retourne le score des joueurs
int CBoard::GetScore(int playerId) {
    int score = 0;
    for(int y=0;y<8;y++) {
        for(int x=0;x<8;x++) {
            if(tab[x][y] == (unsigned)playerId)
                score++;
        }
    }
    return score;
}

// Retourne le nombre de pions sur le plateau
int CBoard::getNbrPions() {
    int nbrpions = 0;
    for(int y=0;y<8;y++) {
        for(int x=0;x<8;x++) {
            if(tab[x][y] != 0)
                nbrpions++;
        }
    }
    return nbrpions;
}

// Retourne le chiffre du joueur dans un tour de jeu
unsigned int CBoard::getplayerTour(){
    return playerTour;
}

//  Modifie le chiffre du joueur dans un tour de jeu
void CBoard::setplayerTour(int playertour){
    playerTour = playertour;
}

// Range la table
void CBoard::clearBoard(int nbrP1, int nbrP2) {
	if(!tabClear) {
		int pionsP1 = GetScore(nbrP1);
		int pionsP2 = GetScore(nbrP2);
		for(int y=0;y<8;y++) {
			for(int x=0;x<8;x++) {
				if(pionsP1 == 0)
				{
					tab[x][y] = nbrP2;
					pionsP2--;
				} else {
					pionsP1--;
					tab[x][y] = nbrP1;					
				}
			}
		}

		tabClear = true;
	}
}
