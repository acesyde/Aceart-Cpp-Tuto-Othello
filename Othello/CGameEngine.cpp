#include "CGameEngine.h"

// Constructeur 
CGameEngine::CGameEngine()
{
    maTable = new CBoard();
    InitGameEngine();
    InitPlayer();
    InitViewManager();
}

// destructeur
CGameEngine::~CGameEngine()
{
    delete maTable;
    delete humanPlayer;
    delete iaPlayer;
	delete managerView;
	delete Input;
    delete App;
}

// Initialisation du moteur de jeux
void CGameEngine::InitGameEngine() {
    myFont.LoadFromFile("img/police.ttf",50);
    App = new sf::RenderWindow(sf::VideoMode(624,624),"Othello",sf::Style::Close);
    App->SetFramerateLimit(10);
    //App->ShowMouseCursor(false);
    Input = &App->GetInput();
}

// Initialisation des joueurs
void CGameEngine::InitPlayer() {
    humanPlayer = new CJoueur("Joueur 1","img/black.png",1);
    iaPlayer = new CIA("IA","img/white.png",2);
}

// Initialisation du manageur de vue
void CGameEngine::InitViewManager() {
    managerView = new CViewManager(*App);
    App->SetView(managerView->toggleMenu());
}

/*
	Fonction : CenterText
	Description : Centrer un texte
	- Passage de la largeur d'un texte en parametre
*/
float CGameEngine::CenterText(float textWidth) {
    return managerView->getMenuCenter().x-textWidth/2;
}

// Dessin des menus
void CGameEngine::DrawMenu() {
    sf::String gameName("OTHELLO",myFont,50);
    float positionY = (App->GetHeight()/2)-gameName.GetRect().GetHeight();
    gameName.SetPosition(CenterText(gameName.GetRect().GetWidth()),positionY);
    App->Draw(gameName);

    sf::String caution("Press Escape to play",sf::Font::GetDefaultFont(),20);
    caution.SetPosition(CenterText(caution.GetRect().GetWidth()),gameName.GetPosition().y+60);
    App->Draw(caution);

    sf::String scoreText("S : Show Score",sf::Font::GetDefaultFont(),15);
    scoreText.SetPosition(CenterText(scoreText.GetRect().GetWidth()),caution.GetPosition().y+40);
    App->Draw(scoreText);

    sf::String pauseText("P : Toggle Pause",sf::Font::GetDefaultFont(),15);
    pauseText.SetPosition(CenterText(pauseText.GetRect().GetWidth()),scoreText.GetPosition().y+20);
    App->Draw(pauseText);

    sf::String newGame("N : New Game",sf::Font::GetDefaultFont(),15);
    newGame.SetPosition(CenterText(newGame.GetRect().GetWidth()),pauseText.GetPosition().y+20);
    App->Draw(newGame);

    sf::String copyright("Mercier Pierre - Bouvot Alexis",sf::Font::GetDefaultFont(),10);
    float positionX = App->GetWidth()*2-copyright.GetRect().GetWidth();
    copyright.SetPosition(positionX,App->GetHeight()-10);
    App->Draw(copyright);
}

// Captures d'écrans
void CGameEngine::takeScreenShot() {
    sf::Image Screen = App->Capture();
    Screen.SaveToFile("screenshot.jpg");
}

// Boucle du jeux pour l'affichage du plateau
bool CGameEngine::GameLoop() {
    while(App->IsOpened()) {

        unsigned int MouseX = Input->GetMouseX();
        unsigned int MouseY = Input->GetMouseY();

        while(App->GetEvent(Event)) {
            if(Event.Type == sf::Event::Closed)
                return false;
            if(Event.Type == sf::Event::KeyPressed) {
                if(Event.Key.Code == sf::Key::Escape)
                    App->SetView(managerView->toggleMenu());
                if(Event.Key.Code == sf::Key::N)
                    maTable->InitGame();
                if(Event.Key.Code == sf::Key::S)
                    maTable->toggleScore();
                if(Event.Key.Code == sf::Key::P)
                    maTable->togglePause();
                if(Event.Key.Code == sf::Key::F1)
                    takeScreenShot();
            }

            if(Event.Type == sf::Event::MouseButtonPressed) {
                if(Event.MouseButton.Button == sf::Mouse::Left && managerView->getState()) {
                    if(maTable->setJeton(MouseX,MouseY,*humanPlayer,*iaPlayer)){

                    }

                }
            }
            if( maTable->getplayerTour() == iaPlayer->getPlayerId() ){

                if (LancerIA() == true){
                }else{
                    cout << "Je ne peut plus jouer" << endl;
                    maTable->setplayerTour(1);
                }
            }
        }

        App->Clear(sf::Color(52,101,164));

        maTable->DrawBoard(*App,*humanPlayer,*iaPlayer);

        if(!managerView->getState()) {
            DrawMenu();
        }

        if(!maTable->getFin() && !maTable->getPause() && managerView->getState()) {
                    maTable->showJeton(MouseX,MouseY,*App,*humanPlayer,*iaPlayer);
        }

        App->Display();
    }

    return App->IsOpened();
}

//Boucle pour le parcours du plateau par l'Intelligence artificielle
bool CGameEngine::LancerIA(){
     for(int x=0 ; x<8 ; x++){
        for(int y=0 ; y<8 ; y++){
            if(iaPlayer->VerifMax(x,y) == true){
                int Xia = iaPlayer->getmaxX()*PIONW;
                int Yia = iaPlayer->getmaxY()*PIONH;
                if(maTable->setJeton(Xia,Yia,*humanPlayer,*iaPlayer) == true){
                    return true;
                }
            }
        }

    }
    for(int x=0 ; x<8 ; x++){
            for(int y=0 ; y<8 ; y++){
                int Xia = x*PIONW;
                int Yia = y*PIONH;
                if(maTable->setJeton(Xia,Yia,*humanPlayer,*iaPlayer) == true){
                    return true;
                }

            }
    }
    return false;
    }
